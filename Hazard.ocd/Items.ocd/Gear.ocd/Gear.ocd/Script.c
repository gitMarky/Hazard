

// actually, only the first four are used...
static const GEAR_Armor  = 1;
static const GEAR_Shield = 2;
static const GEAR_Light = 3;
static const GEAR_Backpack = 4;
static const GEAR_Boots = 5; // unused
static const GEAR_Helmet = 6; // unused
// ...feel free to add some

/* Status */

func IsHazardGear()
{
	return true;
}

/* Buckle */

protected func ControlUse(object user, int x, int y)
{
	return ActivateGear(user);
}


func ActivateGear(object user)
{
	// Can the clonk use this?
	if (!(user->~CanUse(GetID()))) return false;

	// Clonk doesn't already use gear of that type 
	if (user->~HasGear(this->GetGearType()))
	{
		user->InfoMessage("$AlreadyWears$", user, GetName(user));
		return false;
	}

	// Buckle
	if (user->~EquipGear(this)) GearBuckle(user);
	return true;
}


func GearBuckle(object user)
{
	// Message for newbies
	user->HelpMessage("$Buckled$", user, GetName());
	// Hide, but do not delete the gear
	Exit();
	SetCategory(C4D_StaticBack);
	SetPosition(1, 1);
	this.Visibility = VIS_None;
	
	// Callback
	this->GearEffect(user);
}

func GearUnbuckle(object user)
{
	// Message for newbies
	user->HelpMessage("$Unbuckled$", user, GetName());
	// Return to the user
	SetPosition(user->GetX(), user->GetY());
	SetCategory(C4D_Object);
	this.Visibility = VIS_All;
	
	this->GearEffectReset(user);
}

/* Callbacks */

func GearEffect(object user)
{
}

func GearEffectReset(object user)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = 1;
