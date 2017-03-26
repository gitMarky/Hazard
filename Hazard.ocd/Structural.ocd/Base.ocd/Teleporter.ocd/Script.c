
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local current_target;
local is_private;

func Initialize()
{
	SetAction("Activated");
	is_private = false;

	SetLightColor(LIGHT_COLOR_TELEPORT);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// interaction

func IsInteractable()
{
	return IsActivated();
}


// Adapt appearance in the interaction bar.
func GetInteractionMetaInfo(object clonk)
{
	return { Description = "$BeamMeUp$" , IconName = nil, IconID = TELE, Selected = true };
}


func Interact(object clonk)
{
	if (!IsActivated())
	{
		clonk->InfoMessage("$Inactive$", this);
		return false;
	}

	CheckBeam(clonk);
	return true;
}

func CheckBeam(object clonk)
{
	// there is a target?
	if (!current_target)
	{
		Sound("UI::Error");
		if (clonk) clonk->InfoMessage("$NoTarget$", this);
		return;
	}
	// target not active?
	if (!(current_target->IsActivated()))
	{
		Sound("UI::Error");
		if (clonk) clonk->InfoMessage("$TargetInactive$", this);
		return;
	}
	BeamObjects();
}


func BeamObjects()
{
	for (var item in FindObjects (
			Find_InRect(-11, -13, 22, 43),
			Find_NoContainer(),
			Find_Not(Find_Category(C4D_Structure | C4D_StaticBack | C4D_Vehicle)),
			Find_Exclude(this))) 
	{
		Beam(item, current_target);
	}

	SetAction("Beam");
}

global func Beam(object item, object target, int x, int y)
{
	if (item)
	{
		AddEffect("Beam", item, 180, 1, nil, TELE, target, x, y);
	}
}


func Activity()
{
	// please put effects in here
	// kk!
	var x, y, xdir, ydir;
	for (var i = -7; i < 9; i += 3)
	{
		x = Cos(GetR() + 90 + i, 23);
		y = Sin(GetR() + 90 + i, 23);
		xdir = -x / 3;
		ydir = -y / 3;
		CreateParticle("Magic", x, y, xdir, ydir, 40,
		{
			Prototype = Particles_Magic(),
			R = 152, B = 209, G = 210,
			Size = 10,
		});
	}
}


func CreateBeamSpark(int x, int y, int width, int height)
{
	x = RandomX(x - width / 2, x + width / 2);
	y = RandomX(y - height / 2, y + height / 2);
	
	CreateParticle("ElectroSpark", x, y, 0, -2, 10,
	{
		Prototype = Particles_ElectroSpark1(),
		R = 188, G = 127, B = 220,
		Alpha = PV_Linear(200, 0),
		Size = 20,
	});
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// transportation

func FxBeamEffect(string name, object target)
{
	if (name == "Beam") return -1;
}

func FxBeamStart(object target, proplist fx, int temp, beamTo, x, y)
{
	if (temp) return;
	
	fx.colorMod = target->GetClrModulation();
	fx.beamTarget = beamTo;
	if (beamTo)
	{
		x = beamTo->GetX();
		y = beamTo->GetY() + target->GetObjHeight() / 2;
	}
	fx.beamToX = x; // [opt] x-Position to beam to (if object = nil)
	fx.beamToY = y; // [opt] y-Position to beam to (if object = nil)
	// TODO Sound("DeEnergize");
	target->SetCommand("None");
}

func FxBeamStop(object target, proplist fx, int reason, bool temp)
{
	if (temp || reason)
		return;

	// move and restore previous state
	target->SetPosition(fx.beamToX, fx.beamToY);
	target->SetClrModulation(fx.colorMod);
}

func FxBeamTimer(object target, proplist fx, int time)
{
	// fade out
	var newVisibility = GetRGBaValue(target->GetClrModulation(), RGBA_ALPHA) - 5;
	target->SetClrModulation(SetRGBaValue(target->GetClrModulation(), newVisibility));
	
	// apparently the target is gone
	if (newVisibility < 25)	return FX_Execute_Kill;

	var beamToX = fx.beamToX;
	var beamToY = fx.beamToY;
	
	// particle stuff
	for (var i = 0; i < Sqrt(time); ++i)
	{
		var width = target->GetObjWidth();
		var height = target->GetObjHeight();
		CreateBeamSpark(AbsX(target->GetX()), AbsY(target->GetY()), width, height);
		CreateBeamSpark(AbsX(beamToX), AbsY(beamToY), width, height);
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// choosing a target

func MenuSetTarget(id icon, object target)
{
	SetTarget(target);
}


func SetTarget(object target)
{
	if (target->GetID() != TELE)
	{
		FatalError(Format("The target has to be a teleporter with ID %i", TELE));
	}

	current_target = target;
	return true;
}


func SearchTargets(object clonk)
{
	// we need someone to use the console
	if (!clonk) return;
	// TODO: Replace this with GUI menu
	// create the menu
	CreateMenu(HSGN, clonk);
	
	var teleporters = FindObjects
	(
		Find_ID(TELE),
		Find_Exclude(this),
		Find_Not(Find_Func("IsPrivateTeleporter")),
		Find_Not(Find_Hostile(GetOwner()))
	);
	for (var teleporter in teleporters) 
	{
		clonk->AddMenuItem("$ChooseTarget$", "MenuSetTarget", GetID(), 0, teleporter);
	}
	// menu update effect
	AddEffect("TeleMenu", clonk, 101, 5, this, nil, teleporters);
}

// effect that displays the choosable teleporters
func FxTeleMenuStart(object target, proplist fx, int temp, array targets)
{
	if (temp) return;
	fx.targets = targets;
}

func FxTeleMenuTimer(object target, proplist fx)
{
	// menu gone?
	if (target->GetMenu() != HSGN) return FX_Execute_Kill;

	var i = target->GetMenuSelection();
	SetPlrView(target->GetOwner(), fx.targets[i]);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TODO: console interaction (may be removed/changed to the current system)

func ConsoleControl(int i)
{
	if (i == 1)
	{
		return "$BeamMeUp$";
	}
	else if (i == 2)
	{
		if (GetAction() == "Deactivate")
			return "$TurnOn$";
		else
			return "$TurnOff$";
	}
	else if (i == 3)
	{
		return "$SearchTarget$";
	}
}

func ConsoleControlled(int i, int clonkNum, int consoleNum)
{
	var clonk = Object(clonkNum);
	
	if (i == 1)
	{
		CheckBeam(clonk);
	}
	else if (i == 2)
	{
		if (GetAction() == "Deactivate")
			Activate();
		else
			Deactivate();
	}
	else if (i == 3 && clonk)
	{
		SearchTargets(clonk);
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// status

func IsActivated()
{
	return GetAction() == "Activated";
}

func Activate()
{
	SetAction("Activate");
	AddLightAmbience(100);
}

func Deactivate()
{
	SetAction("Deactivate");
	RemoveLight();
}

func IsPrivateTeleporter()
{
	return is_private;
}

func SetPrivateTeleporter(bool private)
{
	is_private = private;
}

func SaveScenarioObject(proplist props)
{
	if (!_inherited(props, ...)) return false;

	if (current_target) props->AddCall("SetTarget", this, "SetTarget", current_target);
	if (IsActivated()) props->AddCall("Activate", this, "Activate");
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Activate = {
	Prototype = Action,
	Name = "Activate",
	Procedure = DFA_NONE,
	Directions = 1,
	Length = 8,
	Reverse = 1,
	Delay = 4,
	X = 0,
	Y = 0,
	Wdt = 50,
	Hgt = 52,
	NextAction = "Activated",
},

Activated = {
	Prototype = Action,
	Name = "Activated",
	Procedure = DFA_NONE,
	Directions = 1,
	Length = 1,
	Delay = 25,
	X = 0,
	Y = 52,
	Wdt = 50,
	Hgt = 52,
	NextAction = "Activated",
	StartCall = "Activity",
},

Deactivate = {
	Prototype = Action,
	Name = "Deactivate",
	Procedure = DFA_NONE,
	Directions = 1,
	Length = 8,
	Delay = 4,
	X = 0,
	Y = 0,
	Wdt = 50,
	Hgt = 52,
	NextAction = "Hold",
},

Beam = {
	Prototype = Action,
	Name = "Beam",
	Procedure = DFA_NONE,
	Directions = 1,
	Length = 10,
	Delay = 4,
	X = 0,
	Y = 52,
	Wdt = 50,
	Hgt = 52,
	NextAction = "DeBeam",
},

DeBeam = {
	Prototype = Action,
	Name = "DeBeam",
	Procedure = DFA_NONE,
	Directions = 1,
	Length = 10,
	Reverse = 1,
	Delay = 4,
	X = 0,
	Y = 52,
	Wdt = 50,
	Hgt = 52,
	NextAction = "Activated",
},

};
