#include Library_Weapon
#include Library_UpgradeableObject
#include Plugin_Weapon_FiremodeByInteraction
#include Plugin_Weapon_FiremodeByToggle
#include Plugin_Weapon_ReloadFromAmmoSource

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Basics and status

local Collectible = true;

public func HasInteractionMenu() { return Contained() != nil && GetLength(GetFiremodes()) > 1; }

func Hit()
{
	Sound("Hits::GeneralHit?");
}

public func GetAmmoSource(ammo) // takes ammo from whom?
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

func IsUserReadyToUse(object user)
{
	return user->HasHandAction(false, // needs only one hand
					           false, // ???
							   false); // must not grab landscape
}

func IsWeaponReadyToUse(object user)
{
	var other_weapons = FindObjects(Find_Container(user), Find_Exclude(this), Find_Func("IsHazardWeapon"));
	
	var can_use = _inherited(user, ...);

	for (var weapon in other_weapons)
	{
		can_use = can_use && weapon->~IsReadyToFire();
	}

	return can_use;
}

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


public func ChangeFiremode(firemode)
{
	if (GetFiremode())
	{
		RemoveAmmo();
	}

	_inherited(firemode);

	if (Contained())
	{
		StartReload(Contained(), nil, nil, true);
	}	
}


public func OnSelectFiremode(proplist firemode)
{
	if (Contained())
	{
		InfoMessage(firemode.name, Contained());
	}
}

public func GetGUIFiremodeActiveColor(){ return GUI_COLOR_TEXT;}
public func GetGUIFiremodeInactiveColor(){ return "dddddd";}

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

public func RemoveAmmo()
{
	if (GetAmmoReloadContainer() && GetAmmoReloadContainer()->~IsAmmoManager())
	{
		var firemode = GetFiremode();
		var ammo = GetAmmo(firemode);
		DoAmmo(firemode.ammo_id, -ammo);
		GetAmmoReloadContainer()->DoAmmo(firemode.ammo_id, ammo);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Cooldown

public func NeedsRecovery(object user, proplist firemode)
{
	return NeedsReload(user, firemode);
}

public func OnFinishCooldown(object user, proplist firemode)
{
	if (NeedsReload(user, firemode))
	{
		StartReload(user, nil, nil, true);
	}
}

public func OnSkipCooldown(object user, proplist firemode)
{
	if (NeedsReload(user, firemode))
	{
		StartReload(user, nil, nil, true);
	}
}
