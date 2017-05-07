#include Library_AmmoManager

local lib_turret;

func TurretMaxRotLeft(){	return 110;}
func TurretMaxRotRight(){	return 250;}
func TurretSearchDistance(){	return 250;}

func GetWeapon(){	return lib_turret.weapon;}
func AimAngle(){	return lib_turret.aim_angle;}
func TargetAngle(){	return lib_turret.target_angle;}
func GetTarget(){	return lib_turret.target;}

func GetWeaponX(){ return GetX();}
func GetWeaponY(){ return GetY();}


func Initialize()
{
	_inherited(...);

	lib_turret = 
	{
		weapon = nil,
		aim_angle = 180,
		target_angle = 180,
		aim_dir = 0,
		target = nil,
	};

	SetGraphics(nil, GetID(), 1, GFXOV_MODE_ExtraGraphics);
	// add weapon at overlay 3, in case we have weapons with 2 layers?
	SetGraphics(nil, GetID(), 3, GFXOV_MODE_ExtraGraphics);
	CreateEffect(IntShowWeapon, 50, 1);
}


func FindTarget()
{
	var aim_at = nil;
	var targets = FindProjectileTargets(TurretSearchDistance());
	var possible_targets = [];
	for (aim_at in targets) 
	{
		if (!IsValidTarget(aim_at))
			continue;
		
		// calculate angle
		lib_turret.target_angle = Angle(GetWeaponX(), GetWeaponY(), aim_at->GetX(), aim_at->GetY());
		lib_turret.target_angle = Normalize(lib_turret.target_angle, 0);

		if (lib_turret.target_angle < TurretMaxRotLeft() || lib_turret.target_angle > TurretMaxRotRight())
			continue;
		
		PushBack(possible_targets, aim_at);
	}
	
	if (!aim_at)
	{
		StopFiring();
	}

	return GetMostValuableTarget(possible_targets);
}

func StartFiring()
{
	if (!IsFiring())
	{
		CreateEffect(IntShoot, 1, 1);
	}
}

func StopFiring()
{
	var fx = IsFiring();
	if (fx)
	{
		RemoveEffect(nil, this, fx);
	}
}

func IsFiring()
{
	return GetEffect("IntShoot", this);
}

func IsValidTarget(object target)
{
	if (!target) return false;
	if (target == this) return false;
	if (target->Contained()) return false;
  
	if (!(target->~IsProjectileTarget()) && !(target->GetOCF() & OCF_Alive)) return false;  
	
	if (GetOwner() != NO_OWNER)
	if (target->GetOwner() == GetOwner() || !Hostile(target->GetOwner(), GetOwner()))
		return false;
	
	return true;
}

local IntShoot = new Effect{
	Timer = func()
	{
		var weapon = Target->GetWeapon();
		if (weapon)
		{
			var radius = 1000;
			var angle = Target->AimAngle();
			var x = +Sin(angle, radius);
			var y = -Cos(angle, radius);
			weapon->ControlUseHolding(Target, x, y);
		}
	},
};

func SetAimPosition(int angle)
{
	// do nothing!
}

local IntShowWeapon = new Effect
{
	Timer = func()
	{
		Target->ShowWeapon();
	},
};

func ShowWeapon()
{
	var overlay = 1;
	if (GetWeapon())
	{
		SetGraphics(nil, nil, overlay, GFXOV_MODE_Object, nil, nil, GetWeapon());
	
		var angle = AimAngle();
		var xoff_turret = 0;
		var yoff_turret = 1000 * (GetWeaponY() - GetY());
		var xoff_weapon = GetWeapon()->~GetSentryGunOffsetX();
		var yoff_weapon = GetWeapon()->~GetSentryGunOffsetY();
	
		SetObjDrawTransform(1000, 0, xoff_turret + Sin(angle, xoff_weapon) - Cos(angle, yoff_weapon),
		                    1000, 0, yoff_turret + Sin(angle, yoff_weapon) - Cos(angle, xoff_weapon), overlay);

		GetWeapon()->SetR(angle + 90);
	}
	else
	{
		SetGraphics(nil, GetID(), overlay, GFXOV_MODE_Base);
	}
}

func TurretRotateToTarget(int speed)
{
	var change = BoundBy(lib_turret.target_angle - lib_turret.aim_angle, -speed, speed);
	lib_turret.aim_angle = BoundBy(lib_turret.aim_angle + change, TurretMaxRotLeft() + 1, TurretMaxRotRight() - 1); // prevent leaving the target zone, because this causes a delay now
}
