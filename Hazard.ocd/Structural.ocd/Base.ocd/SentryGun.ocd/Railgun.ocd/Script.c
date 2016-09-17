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
		
		ammo_id = Ammo_Energy,
		ammo_usage = 1,
		ammo_rate = 100,
		ammo_load = 100,

		delay_reload = 60,
		delay_recover = 125,

		mode = 			WEAPON_FM_Auto,
		
		projectile_id = Projectile_RailgunBeam,
		projectile_range = 500,
		projectile_speed = 8,
		projectile_distance = 22,
		projectile_offset_y = -3,

		damage = 6,
	};
}


public func FireSound(object user, proplist firemode)
{
	Sound("Weapon::Motegun::RailGunShot");
}

public func OnFireProjectile(object user, object projectile, proplist firemode)
{
		projectile->LaserColor(RGBa(255, 255, 255, 190));
		projectile->LaserWidth(13);
		projectile->LaserLifetime(30);
		projectile->HitScan();
}

public func FireEffect(object user, int angle, proplist firemode)
{
	// nothing!
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
