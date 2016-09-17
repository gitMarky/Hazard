#include Weapon_Base

func IsHazardWeapon(){	return false;}
local Collectible = false;

public func Initialize()
{
	_inherited(...);
	firemode_standard =  FiremodeStandard();
	ChangeFiremode(firemode_standard);
}

func IsSentryGunCompatible(){	return true;}
func GetSentryGunOffsetX(){ return 7000;}
func GetSentryGunOffsetY(){ return 0;}
func OnArmSentryGun(object sentry_gun)
{
	// do nothing
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Fire modes

local firemode_standard;
func FiremodeStandard()
{
	return 
	{
		Prototype = firemode_default,
		ammo_id = Ammo_Standard,
		ammo_load = 500,
		
		delay_reload = 6,
		delay_recover = 6,
		delay_cooldown = 1,

		ammo_usage = 	1,
		ammo_rate = 	2,
		mode = 			WEAPON_FM_Auto,
		
		projectile_id = Projectile_Bullet,
		projectile_speed = 300,
		projectile_range = 600,
		projectile_distance = 22,
		projectile_offset_y = -3,
		
		damage = 4, // was: 44, really that high??
	};
}


public func OnFireProjectile(object user, object projectile, proplist firemode)
{
	projectile->Trail(3, 100);
	projectile->Sound("Weapon::SentryGun::MGFire");
}


public func FireEffect(object user, int angle, proplist firemode)
{
	// muzzle flash
	var x = +Sin(angle, firemode.projectile_distance);
	var y = -Cos(angle, firemode.projectile_distance) + firemode.projectile_offset_y;

	EffectMuzzleFlash(user, x, y, angle, 20, false, true);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
RackAttach = {
	Prototype = Action,
	Name = "RackAttach",
	Procedure = DFA_ATTACH,
	Directions = 1,
	Length = 1,
	FacetBase = 1,
	NextAction = "RackAttach",
},
};
