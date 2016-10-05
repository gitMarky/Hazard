#include Weapon_Base

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local carry_mode =  CARRY_Blunderbuss;

public func GetCarryTransform()
{
	return Trans_Mul(Trans_Rotate(90, 1, 0, 0), Trans_Translate(-2000, 500), Trans_Scale(1000, 1200, 1200));
}


public func Initialize()
{
	_inherited(...);
	this.MeshTransformation = Trans_Scale(1000, 1200, 1200);
	firemode_standard =  FiremodeStandard();
	firemode_laser =     FiremodeLaser();
	ChangeFiremode(firemode_standard);
}

func Definition(id def)
{
	def.PictureTransformation = Trans_Mul(Trans_Rotate(205, 0, 1, 0), Trans_Rotate(35, 0, 0, 1), Trans_Rotate(-15, 1, 0, 0), Trans_Translate(-1000, 0, 0));
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Fire modes


local firemode_standard;
func FiremodeStandard()
{
	return {
		Prototype = firemode_default,
		name = 				"$Standard$",
		ammo_id = 			Ammo_Energy,
		ammo_load = 		20,

		delay_reload = 		140,
		delay_recover = 	8,

		ammo_usage = 		1,
		ammo_rate = 		1,
		mode = 				WEAPON_FM_Auto,
		
		projectile_id = 	Projectile_Energy,
		projectile_speed = 	180,
		projectile_range = 	400,
		projectile_spread = Projectile_Deviation(2, 1),
		projectile_distance = 12,

		condition = 		this.HasNoLaserUpgrade,

		damage = 			9,
	};
}

local firemode_laser;
func FiremodeLaser()
{
	return {
		Prototype = 		firemode_default,
		name = 				"$Laser$",
		ammo_id = 			Ammo_Energy,
		ammo_load = 		25,

		delay_reload = 		100,
		delay_recover = 	12,

		ammo_usage = 		1,
		ammo_rate = 		2,
		mode = 				WEAPON_FM_Auto,
		
		projectile_id = 	Projectile_LaserBeam,
		projectile_speed = 	250,
		projectile_range =  250,
		projectile_distance = 12,

		condition = 		this.HasLaserUpgrade,

		damage = 			12,
	};
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Effects


public func FireSound(object user, proplist firemode)
{
	if (firemode == firemode_standard)
	{
		Sound("Weapon::Energy::EnergyRifle");
	}
	else if (firemode == firemode_laser)
	{
		Sound("Weapon::Pistol::LaserShot");
	}
}

public func OnFireProjectile(object user, object projectile, proplist firemode)
{
	if (firemode == firemode_standard)
	{
		projectile->Trail(8, 40);
	}
	else if (firemode == firemode_laser)
	{
		projectile->LaserWidth(7);
		projectile->LaserLifetime(15);
		projectile->LaserColor(RGB(50, 100, 255));
		projectile->HitScan();
	}
}

public func FireEffect(object user, int angle, proplist firemode)
{
	var x = +Sin(angle, firemode.projectile_distance);
	var y = -Cos(angle, firemode.projectile_distance) + firemode.projectile_offset_y;

	if (firemode == firemode_standard)
	{
		EffectMuzzleFlash(user, x, y, angle, 40, false, true, RGB(96, 64, 255), "MuzzleFlashDesaturated");
	}
	else if (firemode == firemode_laser)
	{
		EffectMuzzleFlash(user, x, y, angle, 10, false, true, RGB(50, 100, 255), "MuzzleFlashDesaturated");
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Upgrades

public func IsUpgradeable(id upgrade)
{
	if (HasUpgrade(upgrade)) return false;

	return upgrade == Upgrade_Laser;
}

public func GetUpgradeDescription(id upgrade)
{
	if (upgrade == Upgrade_Laser)
	{
		return "$UpgradeToLaser$";
	}
}

public func OnUpgrade(id upgrade)
{
	var clonk = Contained();
	if(upgrade == Upgrade_Laser)
	{
		ChangeFiremode(firemode_laser);
		if (clonk) clonk->~HelpMessage("$UpgradedToLaser$", clonk);
	}
}

public func OnDowngrade(id upgrade)
{
	if(upgrade == Upgrade_Laser)
	{
    	ChangeFiremode(firemode_standard);
	}
}

public func OnReload()
{
	Sound("Weapon::Energy::EnergyRifleLoad");
}
