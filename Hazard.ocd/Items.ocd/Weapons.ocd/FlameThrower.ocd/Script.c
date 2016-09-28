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
	return Trans_Mul(Trans_Rotate(90, 1, 0, 0), Trans_Translate(-2500, 1000, 0));
}


public func Initialize()
{
	_inherited(...);
	firemode_standard =  FiremodeStandard();
	firemode_standard2 =  FiremodeStandard2();
	firemode_slime =  FiremodeSlime();
	firemode_slime2 =  FiremodeSlime2();
	ChangeFiremode(firemode_standard);
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
		name = 			"$FlameThrower$",
		condition = 	this.HasNoWeaponPartUpgrade,

		ammo_id = 		Ammo_Gasoline,
		ammo_load = 	50,

		delay_reload = 	60,
		delay_recover = 5,
		delay_cooldown = 5,
		
		mode = 			WEAPON_FM_Auto,

		projectile_id = Projectile_Flame,
		projectile_speed = 35,
		projectile_range = PROJECTILE_Range_Infinite,

		damage = 		22,
	};
}


local firemode_slime;
func FiremodeSlime()
{
	return 
	{
		Prototype = firemode_default,
		name = 			"$SlimeThrower$",
		ammo_id = 		Ammo_Gasoline,
		ammo_load = 	50,

		delay_reload = 	60,
		delay_recover = 5,
		delay_cooldown = 5,

		mode = 		WEAPON_FM_Auto,  

		condition = 	this.HasSlimeButNoWeaponUpgrade,

		projectile_id = Projectile_Flame,
		projectile_speed = 35,
		projectile_range = PROJECTILE_Range_Infinite,

		damage = 		29,
	};
}


local firemode_standard2;
func FiremodeStandard2()
{
	return 
	{
		Prototype = FiremodeStandard(),

		name = 			"$FlameThrower$",
		delay_recover =	3,
		condition = 	this.HasWeaponPartUpgrade,

		projectile_id = Projectile_FlameBall,
		projectile_speed = 75,
		projectile_spread = Projectile_Deviation(3, 1),
	};
}


local firemode_slime2;
func FiremodeSlime2()
{
	return 
	{
		Prototype = FiremodeSlime(),
		name = 			"$SlimeThrower$",
		delay_recover = 3,
		condition = 	this.HasSlimeAndWeaponUpgrade,

		projectile_id = Projectile_FlameBall,
		projectile_speed = 75,
		projectile_spread = Projectile_Deviation(6, 1),
	};
}


public func OnFireProjectile(object user, object projectile, proplist firemode)
{
	// TODO: aim fire modes up by 15degree if it shoods flameball
	if (firemode == firemode_slime || firemode == firemode_slime2)
	{
		projectile->Slime();
	}
	
	if (firemode == firemode_slime2 || firemode == firemode_standard2)
	{
		projectile->Lifetime(75);
	}
	else
	{
		projectile->Lifetime(50);
	}
}


public func FireSound(object user, proplist firemode)
{
	if (firemode == firemode_slime || firemode == firemode_slime2)
	{
		Sound("Weapon::FlameThrower::Flamer", nil, nil, nil, 1);
	}
	else
	{
		Sound("Weapon::FlameThrower::BioFlamer", nil, nil, nil, 1);
	}
}

public func OnStartCooldown(object user, proplist firemode)
{
		Sound("Weapon::FlameThrower::Flamer", nil, nil, nil, -1);
		Sound("Weapon::FlameThrower::BioFlamer", nil, nil, nil, -1);
}

func OnReload()
{
	Sound("Weapon::FlameThrower::FlamerLoad");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Upgrades

public func IsUpgradeable(id upgrade)
{
	if (HasUpgrade(upgrade)) return false;

	return upgrade == Upgrade_WeaponPart || upgrade == Upgrade_Slime;
}

public func GetUpgradeDescription(id upgrade)
{
	if (upgrade == Upgrade_Slime)
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
	if(upgrade == Upgrade_WeaponPart)
	{
		if (HasUpgrade(Upgrade_Slime))
		{
			ChangeFiremode(firemode_slime2);
		}
		else
		{
			ChangeFiremode(firemode_standard2);
		}
		if (clonk) clonk->~HelpMessage("$UpgradedToWeaponPart$", clonk);
	}
  	else if(upgrade == Upgrade_Slime)
  	{
  		if (HasUpgrade(Upgrade_WeaponPart))
  		{
  			ChangeFiremode(firemode_slime2);
  		}
  		else
  		{
  			ChangeFiremode(firemode_slime);
  		}
		if (clonk) clonk->~HelpMessage("$UpgradedToSlime$", clonk);
	}
}


public func OnDowngrade(id upgrade)
{
	if(upgrade == Upgrade_WeaponPart)
	{
		if (HasUpgrade(Upgrade_Slime))
		{
   		 	ChangeFiremode(firemode_slime);
		}
		else
		{
			ChangeFiremode(firemode_standard);
		}
	}
	else if(upgrade == Upgrade_Slime)
	{
		if (HasUpgrade(Upgrade_WeaponPart))
		{
			ChangeFiremode(firemode_standard2);
		}
		else
		{
    		ChangeFiremode(firemode_standard);
    	}
	}
}

