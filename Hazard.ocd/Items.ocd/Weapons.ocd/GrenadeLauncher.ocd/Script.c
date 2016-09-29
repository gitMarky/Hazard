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
	return Trans_Mul(Trans_Rotate(90, 1, 0, 0), Trans_Translate(-2200, 600));
}

public func Initialize()
{
	_inherited(...);
	firemode_standard = FiremodeStandard();
	firemode_fragmentation =  FiremodeFragmentation();
	firemode_napalm = FiremodeNapalm();
	firemode_slime = FiremodeSlime();
	firemode_emp = FiremodeEMP();
	firemode_laser = FiremodeLaser();
	ChangeFiremode(firemode_standard);
}

func Definition(id def)
{
	def.PictureTransformation = Trans_Mul(Trans_Rotate(230, 0, 1, 0), Trans_Rotate(-15, 0, 0, 1), Trans_Rotate(10, 1, 0, 0), Trans_Translate(0, 0, -2000));
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Fire modes

local firemode_standard;
public func FiremodeStandard()
{
	return 
	{
		Prototype = firemode_default, 
		name = "$Grenade$",
		icon = Grenade_Normal,

		ammo_id = Ammo_Grenade,
		ammo_load = 6,
		
		delay_reload = 160,
		delay_recover = 90,

		projectile_id = Grenade_Normal,
		projectile_speed = 90,
		projectile_range = PROJECTILE_Range_Infinite,
		projectile_spread = Projectile_Deviation(5, 1),

		damage = 30,
		condition = this.HasNoWeaponPartUpgrade,
	};
}


local firemode_fragmentation;
public func FiremodeFragmentation()
{
	return 
	{
		Prototype = firemode_default,
		name = "$FragGrenade$",
		icon = Grenade_Cluster,

		ammo_id = Ammo_Grenade,
		ammo_load = 8,
		ammo_usage = 2,
		delay_reload = 170,
		delay_recover = 90,

		projectile_id = Grenade_Cluster,
		projectile_speed = 70,
		projectile_range = PROJECTILE_Range_Infinite,
		projectile_spread = Projectile_Deviation(5, 1),

		damage = 14,
		condition = this.HasWeaponPartUpgrade,
	};
}


local firemode_napalm;
public func FiremodeNapalm()
{
	return 
	{
		Prototype = firemode_default, 
		name = "$Napalm$",
		icon = Grenade_Napalm,

		ammo_id = Ammo_Gasoline,
		ammo_load = 60,
		ammo_usage = 20,
		delay_reload = 180,
		delay_recover = 60,

		projectile_id = Grenade_Napalm,
		projectile_speed = 80,
		projectile_range = PROJECTILE_Range_Infinite,
		projectile_spread = Projectile_Deviation(5, 1),

		damage = 20,
		condition = this.HasWeaponPartUpgrade,
	};
}


local firemode_slime;
public func FiremodeSlime()
{
	return 
	{
		Prototype = firemode_default, 
		name = "$Slime$",
		icon = Grenade_Slime,

		ammo_id = Ammo_Grenade,
		ammo_load = 2,
		
		delay_reload = 180,
		delay_recover = 90,
		
		projectile_id = Grenade_Slime,
		projectile_speed = 100,
		projectile_range = PROJECTILE_Range_Infinite,
		projectile_spread = Projectile_Deviation(5, 1),

		damage = 8,
		condition = this.HasSlimeUpgrade,
	};
}


local firemode_emp;
public func FiremodeEMP()
{
	return 
	{
		Prototype = firemode_default, 
		name = "$EMP$",
		icon = Grenade_EMP,

		ammo_id = Ammo_Energy,
		ammo_load = 30,
		ammo_usage = 30,
		delay_reload = 60,
		
		projectile_id = Grenade_EMP,
		projectile_speed = 80,
		projectile_range = PROJECTILE_Range_Infinite,
		projectile_spread = Projectile_Deviation(5, 1),

		damage = 200,
		condition = this.HasLaserUpgrade,
	};
}


local firemode_laser;
public func FiremodeLaser()
{
	return 
	{
		Prototype = firemode_default, 
		name = "$Laser$",
		icon = Grenade_Laser,

		ammo_id = Ammo_Energy,
		ammo_load = 45,
		ammo_usage = 15,
		delay_reload = 180,
		delay_recover = 100,

		projectile_id = Grenade_Laser,
		projectile_speed = 80,
		projectile_range = PROJECTILE_Range_Infinite,
		projectile_spread = Projectile_Deviation(5, 1),

		damage = 50,
		condition = this.HasLaserUpgrade,
	};
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Effects


public func OnFireProjectile(object user, object projectile, proplist firemode)
{
	if (firemode == firemode_standard)
	{
	}
}


public func FireSound(object user, proplist firemode)
{
	Sound("Weapon::Grenade::GrenadeFire");
}


public func FireEffect(object user, int angle, proplist firemode)
{
	var x = +Sin(angle, firemode.projectile_distance);
	var y = -Cos(angle, firemode.projectile_distance) + firemode.projectile_offset_y;
	
	var user_xdir = user->GetXDir();
	var user_ydir = user->GetYDir();
	
	var xdir = +Sin(angle, firemode.projectile_speed) / 4;
	var ydir = -Cos(angle, firemode.projectile_speed) / 4;
	
	CreateParticle("Smoke2", PV_Random(x - 5, x + 5), PV_Random(y - 5, y + 5), PV_Random(user_xdir, user_xdir + xdir), PV_Random(user_ydir, user_ydir + ydir), PV_Random(15, 25),
	{
		Prototype = Particles_ThrustColored(200, 200, 200),
		Size = PV_Random(8, 14),
	}, 20);

	CreateParticle("Thrust", x, y, user_xdir, user_ydir, PV_Random(20, 30),
	{
		Prototype = Particles_ThrustColored(255, 200, 200),
		Size = 12,
	});

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Upgrades

public func IsUpgradeable(id upgrade)
{
	if (HasUpgrade(upgrade)) return false;

	return upgrade == Upgrade_Laser || upgrade == Upgrade_Slime || upgrade == Upgrade_WeaponPart;
}

public func GetUpgradeDescription(id upgrade)
{
	if (upgrade == Upgrade_Laser)
	{
		return "$UpgradeToLaser$";
	}
	else if (upgrade == Upgrade_Slime)
	{
		return "$UpgradeToSlime$";
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
		ChangeFiremode(firemode_laser);
		if (clonk) clonk->~HelpMessage("$UpgradedToLaser$", clonk);
	}
  	else if(upgrade == Upgrade_Slime)
  	{
		ChangeFiremode(firemode_slime);
		if (clonk) clonk->~HelpMessage("$UpgradedToSlime$", clonk);
	}
	else if (upgrade == Upgrade_WeaponPart)
	{
		ChangeFiremode(firemode_fragmentation);
		if (clonk) clonk->~HelpMessage("$UpgradedToWeaponPart$", clonk);
	}
}

public func OnDowngrade(id upgrade)
{
	if(upgrade == Upgrade_Laser || upgrade == Upgrade_Slime || upgrade == Upgrade_WeaponPart)
	{
    	ChangeFiremode(firemode_standard);
	}
}


// Soundeffekte

public func OnReload() // TODO
{
  Sound("GrenadeLoad");
}
