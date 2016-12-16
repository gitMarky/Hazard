#include Library_HazardEquipment

local launched;
local last_user;

func ControlUse(object user, int x, int y)
{
	return Activate(user);
}

//Someone set up us the bomb
func Activate(object user)
{
	SetOwner(user->GetController());
	if (!PathFree(GetX(), GetY(), GetX(), 0))
	{
		user->InfoMessage("$RecievingBlocked$", user);
		return true;
	}
	Exit();
	
	//Oh, we get Signal
	Sound("Item::Morse");
	
	//All your base..
	last_user = user;
	launched = true;
	this.Collectible = false;

	this.Visibility = (VIS_Allies + VIS_Owner);
	SetAction("Waiting");
	SetDir(user->GetDir());

	ScheduleCall(this, this.CallSupport, 50);
	return true;
}

//..are belong to us
func CallSupport()
{
	Sound("Item::Siren", true);
	ScheduleCall(this, this.Boom, 20);
}

//You are on the way to destruction
func Boom()
{
	var bomb_delay = 30, bomb_amount = 15;
	ScheduleCall(this, this.LaunchBomb, bomb_delay, bomb_amount);
	FadeOut(bomb_delay * bomb_amount + 5, true);
}

func LaunchBomb()
{
	var dir = GetDir() * 2 - 1;
	CreateObject(Projectile_AirstrikeBomb, RandomX(-100, 100) - 100 * dir, AbsY(20), GetOwner())
		->Shooter(last_user)
	  	->Weapon(this)
		->DamageAmount(30)
        // TODO: ->DamageType(firemode.damage_type)
		->Range(PROJECTILE_Range_Infinite)
		->Launch(0, nil);
}

func RejectEntrance()
{
	return launched;
}

// TODO:
func AI_Inventory(object user)
{
	// use only if possible
	if (!PathFree(GetX(), GetY(), GetX(), 0)) return false;
	// use with delay
	ScheduleCall(this, this.Activate, 1, 0, user);
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = true;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Waiting = {
	Prototype = Action,
	Name = "Waiting",
	Directions = 2,
	FlipDir = 1,
	Length = 1,
	Delay = 0,
	FacetBase = 1,
},

};
