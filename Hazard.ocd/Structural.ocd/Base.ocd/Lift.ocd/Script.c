/*-- Lift --*/


// Lokale Variable: Feuerfarbe :')
local UpperY, LowerY, WaitComDir, WaitY;
local rgb;

func Initialize()
{
	AddEffect("Sparks", this, 1, 4, this);
	rgb = RGB(40 + Random(120), 40 + Random(120), 40 + Random(120));
	SetAction("Travel");
	UpdateTransferZone();
	return 1;
}

func FxSparksTimer(target, number, time)
{
	// Funken! :D
	CreateParticle ("PSpark", 0, -20, PV_Random(-1, 1), PV_Random(-1, 1) - GetYDir() / 4, 50 + Random(80), rgb);
	CreateParticle ("PSpark", 0, +20, PV_Random(-1, 1), PV_Random(-1, 1) - GetYDir() / 4, 50 + Random(80), rgb);
}

func FlareUp()
{
	for (var i = 3; i > 0; --i)
		CreateParticle("PSpark", 0, -20, RandomX(-4, 4), RandomX(-2, -4), 130 + Random(80), rgb, this, true);
}

func FlareDown()
{
	for (var i = 3; i > 0; --i)
		CreateParticle("PSpark", 0, +20, RandomX(-4, 4), RandomX(2, 4), 130 + Random(80), rgb, this, true);
}

/* Steuerung */

func ControlCommand(string command, object target, int x, int y)
{
	// Bewegungskommando vertikal
	if (command == "MoveTo")
	{
		if (Inside(x - GetX(), -16, +16))
		{
			if (y < GetY())
				return SetComDir(COMD_Up);
			if (y > GetY())
				return SetComDir(COMD_Down);
		}
	}
	// Andere Kommandos nicht auswerten
}

func ControlUpdate(object caller, int comdir, bool dig, bool throw)
{
	// Remove horizontal Comdir component
	if (ComDirLike(comdir, COMD_Right))
		comdir = ComDirTransform(comdir, COMD_Left);
	if (ComDirLike(comdir, COMD_Left))
		comdir = ComDirTransform(comdir, COMD_Right);
	
	if (comdir != GetComDir())
		Sound("Click");
	
	// Clear X/Y-Dir
	SetXDir(0);
	if (!ComDirLike(comdir, COMD_Up) && !ComDirLike(comdir, COMD_Down))
		SetYDir(0);
	
	// Ab geth.
	SetComDir(comdir);
	SetAction("Travel");
	return 1;
}

func ControlUp(object caller)
{
	if (!GetPlrCoreJumpAndRunControl(caller->GetController()))
	{
		Sound("Click");
		SetComDir(COMD_Up);
		SetXDir(0);
		SetAction("Travel");
	}
	return 1;
}

func ControlDownSingle(object caller)
{
	if (!GetPlrCoreJumpAndRunControl(caller->GetController()))
	{
		Sound("Click");
		SetComDir(COMD_Down);
		SetXDir(0);
		SetAction("Travel");
	}
	return 1;
}

func ControlLeft(object caller)
{
	if (!GetPlrCoreJumpAndRunControl(caller->GetController()))
	{
		Sound("Click");
		SetComDir(COMD_Stop);
		SetYDir(0);
		SetAction("Travel");
	}
	return 1;
}

func ControlRight(object caller)
{
	if (!GetPlrCoreJumpAndRunControl(caller->GetController()))
	{
		Sound("Click");
		SetComDir(COMD_Stop);
		SetYDir(0);
		SetAction("Travel");
	}
	return 1;
}

// Without HorizontalFix=1, these should prevent that the lift moves horizontally,
// but they do not. They still move after having pressed double left/right and
// waiting a few frames.
/*public func ControlLeftSingle (object caller) {
  [|Method=None]
  return(1);
}

public func ControlLeftDouble (object caller) {
  [|Method=None]
  return(1);
}

public func ControlRightSingle (object caller) {
  [|Method=None]
  return(1);
}

public func ControlRightDouble (object caller) {
  [|Method=None]
  return(1);
}*/

func ControlLeftReleased(object caller)
{
	[|Method=None]
	return 1;
}

/* Kontakt */

func ContactTop()
{
	Wait(COMD_Down);
	return 1;
}

func ContactBottom()
{
	UnstuckClonks();
	Wait(COMD_Up);
	return 1;
}

func ContactLeft()
{
	Stop();
	return 1;
}

func ContactRight()
{
	Stop();
	return 1;
}

func SetYTop(int iNewTop)
{
	return UpperY = iNewTop;
}
  
func YTop()
{
	return UpperY;
}

/* Kommandos */

func Stop()
{
	SetAction("Travel");
	SetComDir(COMD_Stop);
	SetSpeed();
	return 1;
}

func Wait(int iComDir)
{
	Stop();
	// Aktion Wait ruft als EndCall ResumeTravel auf
	SetAction("Wait");
	
	WaitComDir = iComDir;
	return 1;
}

func ResumeTravel()
{
	// EndCall von Aktion Wait
	SetAction("Travel");
	SetComDir(WaitComDir);
	return 1;
}

func Automatic()
{
	// EndCall von Aktion Travel
	// Keine Automatik, wenn ein Clonk mitf�hrt
	if (Passenger())
		return 0;
	// Zu einem wartenden Clonk hinfahren
	if (SpeedToVertical())
		return 1;
	// Eigenstaendige Bewegung beginnen
	if (SelfTravel())
		return 1;
	return 0;
}

func SelfTravel()
{
	// Nur wenn angehalten
	if (GetComDir() != COMD_Stop)
		return 0;
	// Eigenstaendige Bewegung je nach zugelassener Richtung beginnen
	SetComDir(COMD_Up);
	return 1;
}

func SpeedToVertical()
{
	var WaitClonk;
	if (!(WaitClonk = FindObject(Find_InRect(-50, -1000, 100, 2000), Find_OCF(OCF_CrewMember), Find_NoContainer())))
		return;
	if (Inside(WaitClonk->GetX(), GetX() - 12, GetX() + 12))
		if (Inside(WaitClonk->GetY(), GetY() - 40, GetY() - 20))
			return;
	if (GetComDir(WaitClonk) != COMD_Stop)
		return;
	if (!Inside(GetY(WaitClonk), UpperY - 50, LowerY + 50))
		return;
	SetAction("SpeedToY");
	WaitY = Max(GetY(WaitClonk), YTop() - 10);
	return 1;
}

/* Aktion */

func CheckYTop()
{
	// PhaseCall von Travel
	if (GetY() > YTop() - 10)
		return 0;
	SetPosition(GetX(), YTop() - 10);
	ContactTop();
	return 1;
}

func SpeedToY()
{
	// StartCall von SpeedToY
	SetYDir(BoundBy(WaitY - GetY(), -50, 50));
	if (Inside(WaitY - GetY(), -4, +2))
		return Stop();
	if (GetYDir() < 0)
		FlareDown();
	else
		FlareUp();
	return 1;
}

func UnstuckClonks()
{
	// Sucht Clonks in der SolidMask und setzt sie auf die Platte
	var pClonk;
	for (pClonk in FindObjects(Find_InRect(-25, 0, 50, 25), Find_OCF(OCF_CrewMember),Find_NoContainer(), pClonk))
		if (Stuck(pClonk))
			SetPosition(GetX(pClonk), GetY(), pClonk);
}

/* Status */

func Passenger()
{
	return FindObject(Find_InRect(-24, -13, 48, 16), Find_OCF(OCF_CrewMember), Find_NoContainer());
}

/* Transfer */

func UpdateTransferZone()
{
	// Obergrenze ermitteln
	var y1 = -20, y2 = +20;
	while (GetY() + y1 > 5 && !GBackSolid(0, y1))
		y1 -= 5;
	// Untergrenze ermitteln
	while (GetY() + y2 < LandscapeHeight() - 5 && !GBackSolid(0, y2 + 15))
		y2 += 5;
	// Transferzone setzen
	SetTransferZone(-23, y1, 48, y2 - y1 + 10);
	// Ober- und Untergrenze speichern
	UpperY = GetY() + y1;
	LowerY = GetY() + y2;
	return 1;
}

func ControlTransfer(object pObj, int iX, int iY)
{
	// Durchgang am Boden des Fahrstuhlschachts: nicht warten
	if (Inside(GetY(pObj) - LowerY, -10, +10))
		if (Inside(iY - LowerY, -10, +10))
			return;
	
	// Zielposition
	// Maximale Obergrenze
	iY = Max(iY, UpperY);
	
	// Fahrstuhl mit Clonk an Zielposition: anhalten, erledigt
	if (Inside(iY - GetY(), -5, +5))
		if (Passenger())
		{
			Stop();
			return 0;
		}
	
	// Fahrstuhl noch nicht beim Clonk: warten
	if (!Inside(GetY() - GetY(pObj) - 15, +15))
		return 1;
	
	// Fahrstuhl nur in der Mitte anfassen
	if (!Inside(GetX() - GetX(pObj), -15, +15))
		return AddCommand(pObj, "MoveTo", this, 0, 0, 0, 15);
	
	// Fahrstuhl anfassen
	if (GetAction(pObj) != "Push" || GetActionTarget(0, pObj) != this)
		return AddCommand(pObj, "Grab", this);
	
	// Fahrstuhl zur Zielposition steuern
	if (iY < GetY())
		return SetComDir(COMD_Up);
	return SetComDir(COMD_Down);
}

/* Serialisierung */

func Serialize(array extra)
{
	extra[GetLength(extra)] = Format("SetYTop(%d)", UpperY);
	extra[GetLength(extra)] = Format("LocalN(\"rgb\")=%d", rgb);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BorderBound = 7;
local ContactCalls = 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Travel = {
	Prototype = Action,
	Name = "Travel",
	Procedure = DFA_FLOAT,
	Length = 7,
	Delay = 5,
	FacetBase = 1,
	NextAction = "Travel",
	EndCall = "Automatic",
	PhaseCall = "CheckYTop",
},

Wait = {
	Prototype = Action,
	Name = "Wait",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 70,
	FacetBase = 1,
	NextAction = "Travel",
	EndCall = "ResumeTravel",
},

SpeedToY = {
	Prototype = Action,
	Name = "SpeedToY",
	Procedure = DFA_NONE,
	Length = 1,
	Delay = 3,
	FacetBase = 1,
	NextAction = "SpeedToY",
	StartCall = "SpeedToY",
},

};
