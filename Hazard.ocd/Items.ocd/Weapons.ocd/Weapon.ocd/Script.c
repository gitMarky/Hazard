#include Library_Weapon
#include Library_UpgradeableObject
#include Plugin_Weapon_FiremodeByInteraction
#include Plugin_Weapon_ReloadFromAmmoSource

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Basics and status

local Collectible = true;

func Hit()
{
	Sound("Hits::GeneralHit?");
}

public func GetAmmoSource(id ammo) // takes ammo from whom?
{
	return AMMO_Source_Local;
}

public func GetAmmoContainer() // relevant only for AMMO_Source_Container
{
	return Contained();
}

public func GetAmmoReloadContainer() // reload from this container
{
	return Contained();
}

public func IsHazardWeapon()
{
    return true;
}

local carry_mode = CARRY_Hand;

public func GetCarryMode(object clonk, bool idle, bool nohand)
{
	if (idle || nohand || !is_selected)
	{
		return CARRY_None;
	}
	return carry_mode;
}
public func GetCarrySpecial(object user) { if (is_selected) return "pos_hand2"; }
public func GetCarryBone() { return "Grip"; }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Firemodes

local firemode_default = 
{
	name = 				"Standard", // string - menu caption
	icon = 				nil, // id - menu icon
	condition = 		nil, // string - callback for a condition
	
	ammo_id = Ammo_Standard,
	ammo_usage =          1, // int - this many units of ammo
	ammo_rate =           1, // int - per this many shots fired

	delay_charge  =       0, // int, frames - time that the button must be held before the shot is fired
	delay_recover =      10, // int, frames - time between consecutive shots
	delay_cooldown =      0, // int, frames - time of cooldown after the last shot is fired
	delay_reload =	    100, // int, frames - time to reload

	mode = WEAPON_FM_Single,

	damage =              0, 
	damage_type = 		nil,	

	projectile_id = 	nil,
	projectile_speed = 	100,
	projectile_range =  600,
	projectile_distance = 10,
	projectile_offset_y = -6,
	projectile_number =    1,
	projectile_spread = nil, // default inaccuracy of a single projectile

	spread = nil,			  // inaccuracy from prolonged firing

	burst = 0, // number of projectiles fired in a burst
	
	auto_reload = true,
	anim_load_name = "MusketLoadArms",
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Upgrades

private func HasLaserUpgrade()
{
	return HasUpgrade(Upgrade_Laser);
}

private func HasNoLaserUpgrade(){ return !HasLaserUpgrade();}


private func HasSlimeUpgrade()
{
	return HasUpgrade(Upgrade_Slime);
}

private func HasNoSlimeUpgrade(){ return !HasSlimeUpgrade();}


private func HasWeaponPartUpgrade()
{
	return HasUpgrade(Upgrade_WeaponPart);
}

private func HasNoWeaponPartUpgrade(){ return !HasWeaponPartUpgrade();}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Reloading

func NeedsReload(object user, proplist firemode)
{
	return !HasAmmo(firemode);
}

public func OnFinishReload(object user, int x, int y, proplist firemode)
{
	_inherited(user, x, y, firemode, ...);
}

public func OnStartReload(object user, int x, int y, proplist firemode)
{
	this->~OnReload();
	_inherited(user, x, y, firemode, ...);
}

public func OnCancelReload(object user, int x, int y, proplist firemode, bool requested_by_user)
{
	_inherited(user, x, y, firemode, requested_by_user, ...);
}

public func OnProgressReload(object user, int x, int y, proplist firemode, int current_percent, int change_percent)
{
	_inherited(user, x, y, firemode, current_percent, change_percent, ...);
}
