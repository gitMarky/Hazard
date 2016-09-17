
static const LIFTPLATE_MODE_Vertical = 1;
static const LIFTPLATE_MODE_Horizontal = 2;

/* local definitions */

local liftplate;

func Definition(id def)
{
	def.MeshTransformation = Trans_Translate(0, 15000, 0);
	def.PictureTransformation = Trans_Mul(Trans_Rotate(20, 0, 1, 0),
										  Trans_Rotate(-20, 1, 0, 0),
										  Trans_Rotate(-20, 0, 0, 1));
}

/* Initialisierung */

func Initialize()
{
	liftplate = 
	{
		Mode = LIFTPLATE_MODE_Vertical,
		UpperBound = nil,
		LowerBound = nil,
		LightL = nil,
		LightR = nil,
		Limited = false,
		WaitY = nil,
		WaitY = nil,
	};

//	lLight = AddLightCone(1000, RGBa(255, 255, 220, 20), this);
//	rLight = AddLightCone(1000, RGBa(255, 255, 220, 20), this);
//	
//	lLight->ChangeSizeXY(700, 500);
//	rLight->ChangeSizeXY(700, 500);
//	lLight->ChangeOffset(-11, -1);
//	rLight->ChangeOffset(+11, -1);
//	lLight->ChangeR(-130);
//	rLight->ChangeR(+130);

	SetAction("Travel");
	UpdateTransferZone();
}


/* Limits */

func SetLimits(int upper, int lower)
{
	if (upper) liftplate.UpperBound = upper;
	if (lower) liftplate.LowerBound = lower;
	liftplate.Limited = true;
}

func SetAutoLimits()
{
	liftplate.Limited = true;
	UpdateTransferZone();
}

/* Control */

func ControlCommand(string command, object target, int x, int y)
{
	if (command == "MoveTo")
	{
		// vertical movement
		if (Vertical() && Inside(x - GetX(), -16, +16))
		{
			if (y < GetY()) return SetComDir(COMD_Up);
			if (y > GetY())	return SetComDir(COMD_Down);
		}
		// horizontal movement
		if (Horizontal() && Inside(x - GetY(), -16, +16))
		{
			if (x < GetX()) return SetComDir(COMD_Left);
			if (x > GetX()) return SetComDir(COMD_Right);
		}
	}
	// skip other commands
}

public func ControlStop(object clonk, int control)
{
	if (control == CON_Up && GetYDir() <= 0)
	{
		Stop();
	}
	else if (control == CON_Down && GetYDir() >= 0)
	{
		Stop();
	}

	return true;
}


func CommandComDir(int comdir)
{
	Log("Called control update");

	// remove horizontal Comdir component
	if (!Horizontal())
	{
		if (ComDirLike(comdir, COMD_Right)) comdir = ComDirTransform(comdir, COMD_Left);
		if (ComDirLike(comdir, COMD_Left)) 	comdir = ComDirTransform(comdir, COMD_Right);
	}
	
	// remove vertical ComDir component
	if (!Vertical())
	{
		if (ComDirLike(comdir, COMD_Up)) comdir = ComDirTransform(comdir, COMD_Down);
		if (ComDirLike(comdir, COMD_Down)) comdir = ComDirTransform(comdir, COMD_Up);
	}
	
	if (comdir != GetComDir()) ConfirmSound();

	// stop without input
	if (comdir == COMD_Stop) return Stop();
	
	// clear X/Y-Dir if necessary
	if (!ComDirLike(comdir, COMD_Right) && !ComDirLike(comdir, COMD_Left)) SetXDir(0);
	if (!ComDirLike(comdir, COMD_Up) && !ComDirLike(comdir, COMD_Down)) SetYDir(0);
	
	// go!
	SetComDir(comdir);
	SetAction("Travel");
	return true;
}

func ControlUp(object caller)
{
	if (!Vertical()) return Stop();

	if (!ComDirLike(GetComDir(), COMD_Up))
	{
		ConfirmSound();
		SetComDir(COMD_Up);
		SetXDir(0);
		SetAction("Travel");
		return true;
	}
}

func ControlDown(object caller)
{
	if (!Vertical()) return Stop();

	if (!ComDirLike(GetComDir(), COMD_Down))
	{
		ConfirmSound();
		SetComDir(COMD_Down);
		SetXDir(0);
		SetAction("Travel");
		return true;
	}
}

func ControlLeft(object caller)
{
	if (!Horizontal()) return false;

	if (!ComDirLike(GetComDir(), COMD_Left))
	{
		ConfirmSound();
		SetComDir(COMD_Left);
		SetYDir(0);
		SetAction("Travel");
		return true;
	}
}

func ControlRight(object caller)
{
	if (!Horizontal()) return false;

	if (!ComDirLike(GetComDir(), COMD_Right))
	{
		ConfirmSound();
		SetComDir(COMD_Right);
		SetYDir(0);
		SetAction("Travel");
		return true;
	}
}

func ContMoveLeft(object caller)
{
	caller->SetComDir(COMD_Left);
}
func ContMoveRight(object caller)
{
	caller->SetComDir(COMD_Right);
}

// Send elevator to the clicked position.
public func ControlUseStart(object clonk, int x, int y)
{
	MoveTo(GetX() + x, GetY() + y);
	// Do not trigger a UseStop-callback.
	return false;
}

/* Contact */

func ContactTop()
{
	if (!Vertical()) return Stop();
	Wait(COMD_Down);
	return true;
}

func ContactBottom()
{
	UnstuckClonks();
	
	if (!Vertical()) return Stop();
	if (Horizontal() && Vertical()) return Stop();
	Wait(COMD_Up);
	return true;
}

func ContactLeft()
{
	if (!Horizontal()) return Stop();
	if (Horizontal() && Vertical()) return Stop();
	Wait(COMD_Right);
	return true;
}

func ContactRight()
{
	if (!Horizontal()) return Stop();
	if (Horizontal() && Vertical()) return Stop();
	Wait(COMD_Left);
	return true;
}

/* Configuration */

func EnableHorizontal()
{
	liftplate.Mode = liftplate.Mode & LIFTPLATE_MODE_Horizontal;
	UpdateTransferZone();
}

func DisableHorizontal()
{
	liftplate.Mode = LIFTPLATE_MODE_Vertical;
	UpdateTransferZone();
}

func EnableVertical()
{
	liftplate.Mode = liftplate.Mode & LIFTPLATE_MODE_Vertical;
	UpdateTransferZone();
}

func DisableVertical()
{
	liftplate.Mode = LIFTPLATE_MODE_Horizontal;
	UpdateTransferZone();
}

func Horizontal()
{
	return liftplate.Mode & LIFTPLATE_MODE_Horizontal;
}

func Vertical()
{
	return liftplate.Mode & LIFTPLATE_MODE_Vertical;
}

func SetYTop(int new_top)
{
	return liftplate.UpperBound = new_top;
}
  
func YTop()
{
	return liftplate.UpperBound;
}

func SetYBottom(int new_bottom)
{
	return liftplate.LowerBound = new_bottom;
}
  
func YBottom()
{
	return liftplate.LowerBound;
}

/* Commands */

func Stop()
{
	SetAction("Travel");
	SetComDir(COMD_Stop);
	SetSpeed();
	return true;
}

func Wait(int com_dir)
{
	Stop();
	SetAction("Wait"); // Wait calls ResumeTravel

	liftplate.WaitComDir = com_dir;
	return true;
}

func ResumeTravel()	// EndCall of action Wait
{
	SetAction("Travel");
	SetComDir(liftplate.WaitComDir);
	return true;
}

func Automatic() // EndCall of action Travel
{
	// passengers override the automatic movement
	if (Passenger()) return false;
	// move to a waiting user
	if (SpeedToVertical()) return true;
	// begin autonomous movement
	return SelfTravel();
}

func SelfTravel()
{
	// travels by itself only if stopped
	if (GetComDir() != COMD_Stop) return false;
	// begin autonomous movement according to allowed directions
	if (LIFTPLATE_MODE_Horizontal == liftplate.Mode) SetComDir(COMD_Left);
	if (LIFTPLATE_MODE_Vertical == liftplate.Mode) SetComDir(COMD_Up);
	if ((LIFTPLATE_MODE_Vertical + LIFTPLATE_MODE_Horizontal) == liftplate.Mode) SetComDir(COMD_Down);
	return true;
}

func SpeedToVertical()
{
	if (liftplate.Mode != LIFTPLATE_MODE_Vertical) return false;

	var wait_for;
	var upper_distance = liftplate.UpperBound - 20 - GetY();
	var lower_distance = liftplate.LowerBound + 20 - GetY();

	for (wait_for in FindObjects (
		Find_InRect(-50, upper_distance, 100, -upper_distance + lower_distance),
		Find_OCF(OCF_CrewMember),
		Find_NoContainer())) 
	{
		if (wait_for->GetComDir() != COMD_Stop)
			continue;

		MoveTo(nil, wait_for->GetY() + wait_for->GetBottom() - 5);
		return true;
	}

	return false;
}


func MoveTo(int x, int y)
{
	x = x ?? GetX();
	y = y ?? GetY();

	if (Vertical())
	{
		liftplate.WaitY = BoundBy(y, liftplate.LowerBound, liftplate.UpperBound - 10);
		SetAction("SpeedToY");
	}
	else if (Horizontal())
	{
		liftplate.WaitX = x;
		SetAction("SpeedToX");
	}
}


/* Action */

func CheckVerticalBoundaries()  // PhaseCall of Travel
{
	if (GetY() < YTop() - 10)
	{
		SetPosition(GetX(), YTop() - 10);
		ContactTop();
	}
	if (YBottom() && GetY() > YBottom())
	{
		SetPosition(GetX(), YBottom());
		ContactBottom();
	}
	return true;
}

func SpeedToY()	// StartCall of SpeedToY
{
	SetYDir(BoundBy(liftplate.WaitY - GetY(), -50, 50));
	if (Inside(liftplate.WaitY - GetY(), -1, +1))
	{
		SetPosition(GetX(), liftplate.WaitY);
		Stop();
	}
	return true;
}

func SpeedToX()	// StartCall of SpeedToX
{
	SetYDir(0);
	SetXDir(BoundBy(liftplate.WaitX - GetX(), -50, +50));
	if (Inside(liftplate.WaitX - GetX(), -1, +1)) Stop();
	return true;
}

func UnstuckClonks()
{
	// looks for passengers in the SolidMask and moves them to the top of the plate
	for (var passenger in FindObjects(Find_InRect(-25, -2, 50, 20), Find_NoContainer()))
		if (passenger->Stuck())
			passenger->SetPosition(passenger->GetX(), GetY());
}

/* Status */

func Passenger()
{
	return FindObject(Find_InRect(-24, -13, 48, 16), Find_OCF(OCF_CrewMember), Find_NoContainer());
}

func IsLift(){ return true;}

/* Transfer */

func UpdateTransferZone()
{
	// only for vertical lift plates
	if (liftplate.Mode != LIFTPLATE_MODE_Vertical) return SetTransferZone();
	
	// save limits
	if (!liftplate.Limited) DetermineLimits();
	
	// set transfer zone
	SetTransferZone(-25, AbsY(YTop()), 50, YBottom() - YTop() + 10);
	return true;
}

func DetermineLimits()
{
	// determine upper bound
	var y1, y2;
	while (GetY() + y1 > 5 && !GBackSolid(0, y1)) y1 -= 5;
	// determine lower bound
	while (GetY() + y2 + 15 < LandscapeHeight() - 5 && !GBackSolid(0, y2 + 15)) y2 += 5;
	
	liftplate.UpperBound = GetY() + y1;
	liftplate.LowerBound = GetY() + y2;
}

func ControlTransfer(object user, int x, int y)
{
	// passage at the lower end of the tunnel: do not wait
	if ((Abs(user->GetY() - liftplate.LowerBound) <= 10)
     && (Abs(y - liftplate.LowerBound) <= 10))
			return false;
	
	// target position
	// limit position
	y = Max(y, liftplate.UpperBound);

	// elevator and passenger at target position: stop, nothing to do
	// or: elevator at position where the passenger is waiting
	if (Abs(y - GetY()) <= 5 && Passenger())
	{
		Stop();
		return false;
	}
	
	// elevator did not reach passenger yet: wait
	if (Abs(GetY() - user->GetY()) > 20)
	{
		return true;
	}
	
	// grab elevator only at the middle of the platform
	if (Abs(GetX() - user->GetX()) > 15)
	{
		user->AddCommand("MoveTo", nil, GetX(), user->GetY(), nil, 15);
		return true;
	}
	
	// grab elevator
	if (user->GetAction() != "Push" || user->GetActionTarget() != this)
	{
		user->AddCommand("Grab", this);
		return true;
	}
	
	// move to target position
	if (y < GetY()) SetComDir(COMD_Up);
	else SetComDir(COMD_Down);

	return true;
}

func ConfirmSound()
{
	Sound("UI::Click");
}

/* Serialisierung */

func Serialize(array extra) // TODO: save object
{
	extra[GetLength(extra)] = Format("SetYTop(%d)", liftplate.UpperBound);
	if (liftplate.Mode == 1)
		extra[GetLength(extra)] = "DisableVertical()";
	if (liftplate.Mode == 2)
		extra[GetLength(extra)] = "EnableHorizontal()";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local ContactCalls = true;
local Touchable = 1;

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
	Speed = 200,
	Accel = 10,
	NextAction = "Travel",
	EndCall = "Automatic",
	PhaseCall = "CheckVerticalBoundaries",
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

SpeedToX = {
	Prototype = Action,
	Name = "SpeedToX",
	Procedure = DFA_NONE,
	Length = 1,
	Delay = 1,
	FacetBase = 1,
	NextAction = "SpeedToX",
	StartCall = "SpeedToX",
},

};
