#include Weapon_Base

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";


public func GetCarryMode(object user) {    return CARRY_Musket; }
public func GetCarrySpecial(object user) { if (is_selected) return "pos_hand2"; }
public func GetCarryBone() { return "Grip"; }
public func GetCarryTransform()
{
	return Trans_Mul(Trans_Rotate(90, 1, 0, 0), Trans_Rotate(5, 0, 0, 1), Trans_Translate(-2500, 500, 0));
}

public func Initialize()
{
	_inherited(...);
	firemode_standard = FiremodeStandard();
	firemode_homing =  FiremodeHoming();
	firemode_remote = FiremodeRemote();
	ChangeFiremode(firemode_standard);
}

func Definition(id def)
{
	def.PictureTransformation = Trans_Mul(Trans_Rotate(235, 0, 1, 0), Trans_Rotate(30, 0, 0, 1), Trans_Translate(-2000, 0, -1000));
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Fire modes

local firemode_standard;
func FiremodeStandard()
{
	return 
	{
		Prototype = 	firemode_default,
		name = 			"$Missile$",
		icon = 			Projectile_Missile,
		condition = 	this.HasNoLaserUpgrade,

		ammo_id = 		Ammo_Missile,
		ammo_load = 	1,

		delay_reload = 	160,
		delay_recover = 160, // TODO: switch back to 1 once we have ammo restrictions
		
		projectile_id = Projectile_Missile,
		projectile_range = PROJECTILE_Range_Infinite,
		projectile_speed = 200,
		projectile_offset_y = -7,

		damage = 		40,
	};
}

local firemode_homing;
func FiremodeHoming()
{
	return 
	{
		Prototype = 		firemode_default,
		name = 				"$HMissile$",
		icon = 				Projectile_MissileHoming,
		condition = 		this.HasLaserUpgrade,

		ammo_id = 			Ammo_Missile,
		ammo_load = 		1,

		delay_reload = 		160,
		delay_recover = 160, // TODO: switch back to 1 once we have ammo restrictions

		projectile_id = Projectile_MissileHoming,
		projectile_range = PROJECTILE_Range_Infinite,
		projectile_speed = 200,
		projectile_offset_y = -7,

		damage = 		37,
	};
}

local firemode_remote;
func FiremodeRemote()
{
	return 
	{
		Prototype = firemode_default,
		name = 				"$RCMissile$",
		icon = 				Projectile_MissileRemote,
		condition = 		this.HasWeaponPartUpgrade,

		ammo_id = 			Ammo_Missile,
		ammo_load = 		1,

		delay_reload = 		160,
		delay_recover = 160, // TODO: switch back to 1 once we have ammo restrictions

		projectile_id = Projectile_MissileRemote,
		projectile_range = PROJECTILE_Range_Infinite,
		projectile_speed = 200,
		projectile_offset_y = -7,

		damage = 		37,
	};
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Effects


public func FireSound(object user, proplist firemode)
{
	Sound("Weapon::Bazooka::Rocket");
}

public func OnFireProjectile(object user, object projectile, proplist firemode)
{
}

public func FireEffect(object user, int angle, proplist firemode)
{
		// muzzle flash, the coordinates are inverted here, because the effect should be at the rear of the bazooka
		var x = +Sin(angle, firemode.projectile_distance);
		var y = -Cos(angle, firemode.projectile_distance) + firemode.projectile_offset_y;

		var xdir = -x;
		var ydir = -y;

		CreateParticle("Thrust", x, y, xdir/4, ydir/4, 16,
		{
			Prototype = Particles_Thrust(),
			R = PV_KeyFrames(0, 0, 255, 500, 100, 1000, 50),
			G = PV_KeyFrames(0, 0, 200, 500,  40, 1000, 20),
			B = PV_KeyFrames(0, 0, 200, 500,  40, 1000, 20),
		});

		for (var i = 0; i < 20; ++i)
		{
			var radius = RandomX(-10, 10);
			CreateParticle("Smoke2", x + Sin(angle, radius), y - Cos(angle, radius), PV_Random(0, xdir), PV_Random(0, ydir), PV_Random(30, 40),
			{
				Prototype = Particles_Thrust(),
				Size = PV_Random(16, 28),
				R = PV_KeyFrames(0, 0, 220, 500,  90, 1000, 45),
				G = PV_KeyFrames(0, 0, 200, 500,  80, 1000, 40),
				B = PV_KeyFrames(0, 0, 180, 500,  70, 1000, 35),
			}, 1);
		}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Upgrades

public func IsUpgradeable(id upgrade)
{
	if (HasUpgrade(upgrade)) return false;

	return upgrade == Upgrade_Laser || upgrade == Upgrade_WeaponPart;
}

public func GetUpgradeDescription(id upgrade)
{
	if (upgrade == Upgrade_Laser)
	{
		return "$UpgradeToLaser$";
	}
	else if (upgrade == Upgrade_WeaponPart)
	{
		return "$UpgradeToWeaponPart$";
	}
}

public func OnUpgrade(id upgrade)
{
	var clonk = Contained();
	if(upgrade == Upgrade_Laser)
	{
		ChangeFiremode(firemode_homing);
		if (clonk) clonk->~HelpMessage("$UpgradedToLaser$", clonk);
	}
	else if (upgrade == Upgrade_WeaponPart)
	{
		ChangeFiremode(firemode_remote);
		if (clonk) clonk->~HelpMessage("$UpgradedToWeaponPart$", clonk);
	}
}

public func OnDowngrade(id upgrade)
{
	if(upgrade == Upgrade_Laser)
	{
    	ChangeFiremode(firemode_standard);
	}
	else if (upgrade == Upgrade_WeaponPart)
	{
		if (HasLaserUpgrade())
		{
			ChangeFiremode(firemode_homing);
		}
		else
		{
			ChangeFiremode(firemode_standard);
		}
	}
}


public func OnReload() // TODO: no callback yet
{
	Sound("Weapon::Bazooka::RocketLoad");
}

