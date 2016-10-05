#include Weapon_Base

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local carry_mode =  CARRY_Blunderbuss;

public func GetCarryTransform()
{
	return Trans_Mul(Trans_Rotate(90, 1, 0, 0), Trans_Translate(-3000, 1500, 0));
}


public func Initialize()
{
	_inherited(...);
	firemode_standard = FiremodeStandard();
	firemode_cluster = FiremodeCluster();
	ChangeFiremode(firemode_standard);
}

func Definition(id def)
{
	def.PictureTransformation = Trans_Mul(Trans_Rotate(230, 0, 1, 0), Trans_Rotate(-15, 0, 0, 1), Trans_Rotate(10, 1, 0, 0), Trans_Translate(-2500, 1000, -1000));
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Fire modes

local firemode_standard;
func FiremodeStandard()
{
	return {
		Prototype = 	firemode_default,
		name = 			"$Standard$",
		ammo_id = 		Ammo_Standard,
		ammo_load = 	30,
		ammo_usage = 	6,

		delay_reload = 	80,
		delay_recover = 30,
		
		projectile_id = Projectile_Bullet,
		projectile_number = 15,
		projectile_speed = 	[250, 350],
		projectile_range = [80, 230],
		projectile_spread = Projectile_Deviation(7, 1),
		projectile_offset_y = -5,
		projectile_distance = 12,

		damage = 		32,
	};
}

local firemode_cluster;
func FiremodeCluster()
{
	return {
		Prototype = 	firemode_default,
		name = 			"$Cluster$",
		ammo_id = 		Ammo_Grenade,
		ammo_load = 	2,
		ammo_usage = 	1,

		delay_reload = 	80,
		delay_recover = 70,

		condition = 	this.HasWeaponPartUpgrade,

		projectile_id = Projectile_Cluster,
		projectile_number = 6,
		projectile_speed = 	[250, 350],
		projectile_range = [80, 230],
		projectile_spread = Projectile_Deviation(7, 1),
		projectile_offset_y = -5,
		projectile_distance = 12,

		damage = 		16,
	};
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Effects


public func FireSound(object user, proplist firemode)
{
	Sound("Weapon::Pumpgun::PumpgunFire");
}


public func OnFireProjectile(object user, object projectile, proplist firemode)
{
	if (firemode == firemode_standard)
	{
		projectile->Trail(3, 400);
	}
	else if (firemode == firemode_cluster)
	{
	}
}


public func FireEffect(object user, int angle, proplist firemode)
{
	// muzzle flash
	var x = +Sin(angle, firemode.projectile_distance);
	var y = -Cos(angle, firemode.projectile_distance) + firemode.projectile_offset_y;

	EffectMuzzleFlash(user, x, y, angle, RandomX(40, 60), false, true);

	// casing
	for (var i = 0; i< firemode.projectile_number / 3; i++)
	{
		x = +Sin(angle, firemode.projectile_distance / 2);
		y = -Cos(angle, firemode.projectile_distance / 2) + firemode.projectile_offset_y;

		CreateCartridgeEffect("Cartridge_Pistol", 2, x, y, user->GetXDir() + Sin(-angle, RandomX(15, 20)), user->GetYDir() - RandomX(15, 30));
	}
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Upgrades


public func IsUpgradeable(id upgrade)
{
	if (HasUpgrade(upgrade)) return false;

	return upgrade == Upgrade_WeaponPart;
}

public func GetUpgradeDescription(id upgrade)
{
	if (upgrade == Upgrade_WeaponPart)
	{
		return "$UpgradeToWeaponPart$";
	}
}

public func OnUpgrade(id upgrade)
{
	var clonk = Contained();
	if(upgrade == Upgrade_WeaponPart)
	{
		ChangeFiremode(firemode_cluster);
		if (clonk) clonk->~HelpMessage("$UpgradedToWeaponPart$", clonk);
	}
}


public func OnDowngrade(id upgrade)
{
	if(upgrade == Upgrade_WeaponPart)
	{
    	ChangeFiremode(firemode_standard);
	}
}


public func OnReload()
{
	Sound("Weapon::Pumpgun::PumpgunLoad");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = 1;
