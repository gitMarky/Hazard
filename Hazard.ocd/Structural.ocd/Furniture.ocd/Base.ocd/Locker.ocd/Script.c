#include Chest

local locked;

private func Open()
{
	if (is_open) return;
	if (locked)
	{
		Sound("Structures::HingeCreak??");
	}
	is_open = true;	
	SetAction("OpenDoor");
	Sound("Structures::Chest::Open");
}

private func Close()
{
	if (!is_open) return;
	is_open = false;
	SetAction("CloseDoor");
	PlayAnimation("Close", 5, Anim_Linear(0, 0, GetAnimationLength("Close"), 15, ANIM_Hold));
	Sound("Structures::Chest::Close");
}


func Damage(int change)
{
	is_open = true;
	if (GetAction() != "Open") SetAction("Open");
	AddEffect("Opening", this, 50, 1, this, nil, Abs(change));
}

func FxOpeningStart(object target, proplist fx, int temp, int speed)
{
	fx.speed = speed;
	fx.phase = 1;
}

func FxOpeningTimer(object target, proplist fx, int timer)
{
	var max_speed = 15;
	var max_phase = 5;
	// delayed opening?
	if (fx.speed < max_speed && timer % (max_speed - fx.speed)) return;

	// set action phase
	var phase = target->GetPhase();
	phase += Max(1, fx.speed / max_speed) * fx.phase;
	if (phase > max_phase)
	{
		fx.phase = -1;
		phase = max_phase - phase % max_phase;
	}
	if (phase < 0)
	{
		fx.phase = 1;
		phase = phase % max_phase;
	}
	target->SetPhase(phase);

	// get slower
	fx.speed -= 1;
	if (fx.speed <= 0) return FX_Execute_Kill;
}

func Hit(){	Sound("Objects::Clonk");}
func IsCraneGrabable(){	return true;}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Open = {
	Prototype = Action,
	Name = "Open",
	Length = 6,
	X = 0,
	Y = 30,
	Wdt = 25,
	Hgt = 30,
	OffX = 0,
	OffY = 0,
},

OpenDoor = {
	Prototype = Action,
	Name = "OpenDoor",
	Length = 6,
	X = 0,
	Y = 30,
	Wdt = 25,
	Hgt = 30,
	OffX = 0,
	OffY = 0,
	Delay = 4,
	NextAction = "Hold"
},

CloseDoor = {
	Prototype = Action,
	Name = "CloseDoor",
	Length = 6,
	X = 0,
	Y = 30,
	Wdt = 25,
	Hgt = 30,
	OffX = 0,
	OffY = 0,
	Delay = 2,
	NextAction = "Idle",
	Reverse = 1
},
};
