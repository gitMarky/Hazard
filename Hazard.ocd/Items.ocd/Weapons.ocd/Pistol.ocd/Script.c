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
	return Trans_Mul(Trans_Rotate(90, 1, 0, 0), Trans_Translate(-2500, 800, 0), Trans_Scale(800, 800, 800));
}


public func Initialize()
{
	_inherited(...);
	this.MeshTransformation = Trans_Scale(800, 800, 800);
	firemode_primary_standard =  FiremodePrimaryStandard();
	firemode_primary_laser =     FiremodePrimaryLaser();
	firemode_secondary_grenade = FiremodeSecondaryGrenade();
	firemode_secondary_slime =   FiremodeSecondarySlime();
	ChangeFiremode(firemode_primary_standard);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Fire modes


local firemode_primary_standard;
func FiremodePrimaryStandard()
{
	return 
	{
		Prototype = firemode_default, 
		name = 				"$Standard$",
		icon = 				nil,
		condition = 		this.HasNoLaserUpgrade,
		
		ammo_id = 			Ammo_Standard,
		ammo_load =         12,
	
		delay_reload =		80,
		delay_recover = 	20,
	
		damage = 			10,
	
		// TODO
		projectile_id = 	Projectile_Bullet,
		projectile_speed = 	250,
		projectile_range =  450,
		projectile_spread = Projectile_Deviation(1, 1),

		projectile_distance = 10,
		projectile_offset_y = -6,
	};
}

local firemode_primary_laser;
func FiremodePrimaryLaser()
{
	return
	{
		Prototype = firemode_default, 
		name = 				"$Laser$",
		icon = 				nil,
		condition = 		this.HasLaserUpgrade,
		
		ammo_id = 			Ammo_Energy,
		ammo_load =         10,
	
		delay_reload =		100,
		delay_recover = 	16,
	
		damage = 			18,
	
		// TODO
		projectile_id = 	Projectile_LaserBeam,
		projectile_speed = 	500,
		projectile_range = 300,

		projectile_distance = 10,
		projectile_offset_y = -6,
	};
}

local firemode_secondary_grenade;
func FiremodeSecondaryGrenade()
{
	return 
	{
		Prototype = firemode_default, 
		name = 				"$GrenadeLauncher$",
		icon = 				nil,
		condition = 		this.HasNoSlimeUpgrade,
		
		ammo_id = 			Ammo_Grenade,
		ammo_load =         1,
	
		delay_reload =		80,
	
		damage = 			30,
	
		// TODO
		projectile_id = 	Grenade_Normal,
		projectile_speed = 	50,
		projectile_range = PROJECTILE_Range_Infinite,

		projectile_distance = 10,
		projectile_offset_y = -6,
	};
}

local firemode_secondary_slime;
func FiremodeSecondarySlime()
{ 
	return
	{
		Prototype = firemode_default, 
		name = 				"$Slime$",
		icon = 				nil,
		condition = 		this.HasSlimeUpgrade,
		
		ammo_id = 			Ammo_Standard,
	
		delay_reload =		80,
		delay_recover = 	20,
	
		damage = 			28,
	
		// TODO
		projectile_id = 	Projectile_Slime,
		projectile_speed = 	50,
		projectile_range =  PROJECTILE_Range_Infinite,

		projectile_distance = 10,
		projectile_offset_y = -6,
	};
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Effects


public func FireSound(object user, proplist firemode)
{
	if (firemode == firemode_primary_standard)
	{
		Sound("Weapon::Pistol::PistolShot");
	}
	else if (firemode == firemode_primary_laser)
	{
		Sound("Weapon::Pistol::LaserShot");
	}
	else if (firemode == firemode_secondary_grenade)
	{
		Sound("Weapon::Grenade::GrenadeFire");
	}
	else if (firemode == firemode_secondary_slime)
	{
		Sound("Weapon::Slime::SlimeShot?");
	}
}

public func OnFireProjectile(object user, object projectile, proplist firemode)
{
	if (firemode == firemode_primary_standard)
	{
		projectile->Trail(2, 150);
	}
	else if (firemode == firemode_primary_laser)
	{
		projectile->HitScan();
	}
}

public func FireEffect(object user, int angle, proplist firemode)
{
	if (firemode == firemode_primary_standard)
	{
		// muzzle flash
		var x = +Sin(angle, firemode.projectile_distance);
		var y = -Cos(angle, firemode.projectile_distance) + firemode.projectile_offset_y;

		EffectMuzzleFlash(user, x, y, angle, 10, false, true);
		
		// casing
		x = +Sin(angle, firemode.projectile_distance / 2);
		y = -Cos(angle, firemode.projectile_distance / 2) + firemode.projectile_offset_y;

		CreateCartridgeEffect("Cartridge_Pistol", 2, x, y, user->GetXDir() + Sin(-angle, 5), user->GetYDir() - RandomX(15, 20));
	}
	else if (firemode == firemode_primary_laser)
	{
		EffectMuzzleFlash(user, x, y, angle, 10, false, true, RGB(255, 32, 0));
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Upgrades

public func IsUpgradeable(id upgrade)
{
	if (HasUpgrade(upgrade)) return false;

	return upgrade == Upgrade_Laser || upgrade == Upgrade_Slime;
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
}

public func OnUpgrade(id upgrade)
{
	var clonk = Contained();
	if(upgrade == Upgrade_Laser)
	{
		ChangeFiremode(firemode_primary_laser);
		if (clonk) clonk->~HelpMessage("$UpgradedToLaser$", clonk);
	}
  	else if(upgrade == Upgrade_Slime)
  	{
		ChangeFiremode(firemode_secondary_slime);
		if (clonk) clonk->~HelpMessage("$UpgradedToSlime$", clonk);
	}
}

public func OnDowngrade(id upgrade)
{
	if(upgrade == Upgrade_Laser)
	{
    	ChangeFiremode(firemode_primary_standard);
	}
	else if(upgrade == Upgrade_Slime)
	{
    	ChangeFiremode(firemode_secondary_grenade);
	}
}
