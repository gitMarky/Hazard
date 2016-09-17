// TODO: implement some kind of switch library, as proposed in the forum

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// switch

local lib_switch;

func UnlockSwitch()
{
	lib_switch.locked = false;
	return this;
}

func LockSwitch(bool unlock)
{
	lib_switch.locked = true;
	return this;
}

func IsSwitchLocked()
{
	return lib_switch.locked;
}

func SetSwitchTarget(object target)
{
	lib_switch.target = target;
}


func Initialize()
{
	lib_switch =
	{
		locked = false,
		target = nil
	};
	SetAction("Switch");
}

func OperateSwitch(object user)
{
	if (IsSwitchLocked())
	{
		user->~PlaySoundDoubt();
		return false;
	}
	else
	{
		SetPhase((GetPhase() + 1) % 2);
		if (lib_switch.target) lib_switch.target->~Access();
		Sound("Structural::Controls::Switch", 0, 0, 80);
		return true;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// interaction

func IsInteractable(object user){	return true;}


// Adapt appearance in the interaction bar.
public func GetInteractionMetaInfo(object clonk)
{
	var info;
	if (lib_switch.target) info = lib_switch.target->~GetInteractionMetaInfo(this); 
	return info ?? { Description = "$OperateSwitch$", IconName = nil, IconID = SWTH };
}

// Called on player interaction.
public func Interact(object user)
{
	if (!IsInteractable(user)) return true;
	return OperateSwitch(user);
}


func Serialize(array extra) //TODO: implemenet saving properly
{
//	if (target)
//		extra[GetLength(extra)] = ["Set(Object(%d))", target];
//	if (locked)
//		extra[GetLength(extra)] = "Lock()";
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Switch = {
	Prototype = Action,
	Name = "Switch",
	Procedure = DFA_NONE,
	Length = 2,
	X = 0,
	Y = 0,
	Wdt = 18,
	Hgt = 12,
},

};
