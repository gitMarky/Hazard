#include Weapon_Base

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";


public func GetCarryMode(object user) {    if (is_selected) return CARRY_Hand; }
public func GetCarrySpecial(object user) { if (is_selected) return "pos_hand2"; }
public func GetCarryBone() { return "Grip"; }
public func GetCarryTransform()
{
	return Trans_Mul(Trans_Rotate(90, 1, 0, 0), Trans_Translate(-2500, 600, 0), Trans_Rotate(10, 0, 0, 1));
}


public func Initialize()
{
	_inherited(...);
	firemode_railgun =  FiremodeRailgun();
	firemode_emp =     FiremodeEmp();
	ChangeFiremode(firemode_railgun);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Fire modes

//RAILGUN!!!!!
local firemode_railgun;
func FiremodeRailgun()
{
	return 
	{
		Prototype = firemode_default,
		name = 		"$Railgun$",

		ammo_id = 		Ammo_Energy,
		ammo_load = 		30,
		ammo_usage = 		30,

		delay_reload = 		130,
		delay_recover = 	130,

		damage = 		240,
		
		projectile_id = Projectile_RailgunBeam,
		projectile_range = 700,
		projectile_speed = 8,
		projectile_offset_y = -5,
		projectile_distance = 13,
	};
}

local firemode_emp;
func FiremodeEmp()
{
	return 
	{
		Prototype = firemode_default,
		name = 		"$Shockwave$",

		ammo_id = 		Ammo_Energy,
		ammo_load = 		20,
		ammo_usage = 		20,

		delay_reload = 		75,

		damage = 		90,

		projectile_id = Projectile_EmpBall,
		projectile_range = 450,
		projectile_speed = 50,
		projectile_offset_y = -5,
		projectile_distance = 13,
	};
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Effects

public func OnReload() // TODO: Callback does not exist yet
{
    Sound("Weapon::Motegun::MoteGunLoad");
    Sound("Weapon::Motegun::EMPLoad");
}

public func FireSound(object user, proplist firemode)
{
	if (firemode == firemode_railgun)
	{
		Sound("Weapon::Motegun::RailGunShot");
	}
	else if (firemode == firemode_emp)
	{
		Sound("Weapon::Motegun::EMPShot");
	}
}

public func OnFireProjectile(object user, object projectile, proplist firemode)
{
	if (firemode == firemode_railgun)
	{
		projectile->LaserColor(RGBa(255, 255, 255, 190));
		projectile->HitScan();
	}
}

public func FireEffect(object user, int angle, proplist firemode)
{
	// muzzle flash
	var x = +Sin(angle, firemode.projectile_distance);
	var y = -Cos(angle, firemode.projectile_distance) + firemode.projectile_offset_y;

	if (firemode == firemode_railgun)
	{
		EffectMuzzleFlash(user, x, y, angle, 300, false, true, RGBa(64, 64, 255, 255));
	}
	else if (firemode == firemode_emp)
	{
		EffectMuzzleFlash(user, x, y, angle, 50, false, true, RGBa(40, 40, 255, 255));
	}
}

