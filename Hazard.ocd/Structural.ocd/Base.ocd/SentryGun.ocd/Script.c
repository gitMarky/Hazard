local exploded;
local sentry_gun;

local Name = "$Name$";

// external properties
func IsMachine(){	return true;}
func IsProjectileTarget(){	return true;}
func IsThreat(){	return sentry_gun.is_active;}

// internal properties
func MaxRotLeft(){	return 110;}
func MaxRotRight(){	return 250;}
func MaxDamage(){	return 100;}
func SearchDistance(){	return 250;}

func GetWeapon(){	return sentry_gun.weapon;}
func AimAngle(){	return sentry_gun.aim_angle;}
func GetTarget(){	return sentry_gun.target;}

func GetWeaponX(){ return GetX();}
func GetWeaponY(){ return GetY() - 3;}

// configuration
func TurnOn(){	sentry_gun.is_active = true; return this;}
func TurnOff(){	sentry_gun.is_active = false; StopFiring(); StopMoveSound(); return this;}

func Arm(id weapon)
{
	if (!weapon) FatalError("You must provide a weapon ID!");
	if (!(weapon->~IsSentryGunCompatible())) FatalError(Format("Weapon %i cannot be attached to a sentry gun!", weapon));
	
	// arm with said weapon
	sentry_gun.aim_angle = 180;
	sentry_gun.aim_dir = -1 + Random(2) * 2;

	var mount = CreateObject(weapon, 0, 0, GetOwner());
	mount->Enter(this);
	mount.Controller = this;
	sentry_gun.weapon = mount;

	Reload();
	mount->~OnArmSentryGun(this); // give the weapon, e.g. an object with mesh graphics, a chance to change its shape and transformation
	return this;
}

// stuff

func Initialize()
{
	sentry_gun = 
	{
		weapon = nil,
		aim_angle = 180,
		old_angle = 180,
		target_angle = 180,
		aim_dir = 0,
		is_active = false,
		target = nil,
	};

	FitToTop();
	// add weapon at overlay 3, in case we have weapons with 2 layers?
	SetGraphics(nil, GetID(), 3, 5, nil, nil, this);
	CreateEffect(IntShowWeapon, 50, 1);
	CreateEffect(IntActivity, 100, 1);
}


func FitToTop()
{
	// fit the weapon mount to the ceiling
	SetPosition(GetX(), GetY() + GetObjHeight() / 2);
	var i = 0;
	while (++i < GetObjHeight() && !Stuck())
	{
		MovePosition(0, -1);
	}
	MovePosition(0, -1);
}

local IntActivity = new Effect
{
	Timer = func (int time)
	{
		Target->Activity(time);
	}
};

func Activity(int time)
{	
	if (!GetWeapon()) return;
	if (EMPShocked()) return;
	if (!sentry_gun.is_active) return;

	// scan the area every 5 frames, or aim at target	
	ScanArea(time);
	
	/* look for targets */

	if (!GetTarget())
	{
		StopFiring();
		sentry_gun.target = FindTarget();
	}
	else
	{
		sentry_gun.target_angle = Angle(GetWeaponX(), GetWeaponY(), GetTarget()->GetX(), GetTarget()->GetY());
		
		// fire at target?
		if (Abs(sentry_gun.aim_angle - sentry_gun.target_angle) < 15)
		{
			StartFiring();
		}
		else
		{
			StopFiring();
		}
		
		// forget target?
		if (!IsValidTarget(GetTarget()))
		{
			sentry_gun.target = nil;
		}
		else if (!PathFree(GetWeaponX(), GetWeaponY(), GetTarget()->GetX(), GetTarget()->GetY()))
		{
			sentry_gun.target = nil;
		}
		else if (ObjectDistance(GetTarget(), this) > SearchDistance())
		{
			sentry_gun.target = nil;
		}
	}
}

func ScanArea(int time)
{
	sentry_gun.motion_delay = Max(0, sentry_gun.motion_delay - 1);
	if (sentry_gun.motion_delay) return StopMoveSound();

	if (time % 5 == 0)
	{
		// too far left
		if (sentry_gun.aim_angle <= MaxRotLeft())
		{
			// go back
			sentry_gun.aim_dir = 1;
			sentry_gun.target_angle = MaxRotRight();
			sentry_gun.target = nil;
			sentry_gun.motion_delay = 100;
		}
		else if (sentry_gun.aim_angle >= MaxRotRight())
		{
			// go back
			sentry_gun.aim_dir = -1;
			sentry_gun.target_angle = MaxRotLeft();
			sentry_gun.motion_delay = 100;
			sentry_gun.target = nil;
		}
		if (!GetTarget())
		{
			sentry_gun.aim_angle += sentry_gun.aim_dir;
		}
	}
	
	// aim at target
	if (GetTarget())
	{
		StartMoveSound(30);
		sentry_gun.aim_angle += BoundBy(sentry_gun.target_angle - sentry_gun.aim_angle, -2, 2);
		sentry_gun.aim_angle = BoundBy(sentry_gun.aim_angle, MaxRotLeft() + 1, MaxRotRight() - 1); // prevent leaving the target zone, because this causes a delay now
		
		// flash fast, without sound
		if ((time % 25) == 0) RedDot();
	}
	else
	{
		StartMoveSound(5);
		// flash slowly, with bip sound
		if ((time % 40) == 0)
		{
			RedDot();
			Bip();	
		}
	}
}

func FindTarget()
{
	var aim_at = nil;
	var targets = FindProjectileTargets(SearchDistance());
	var possible_targets = [];
	for (aim_at in targets) 
	{
		if (!IsValidTarget(aim_at))
			continue;
		
		// calculate angle
		sentry_gun.target_angle = Angle(GetWeaponX(), GetWeaponY(), aim_at->GetX(), aim_at->GetY());
		sentry_gun.target_angle = Normalize(sentry_gun.target_angle, 0);

		if (sentry_gun.target_angle < MaxRotLeft() || sentry_gun.target_angle > MaxRotRight())
			continue;
		
		PushBack(possible_targets, aim_at);
	}
	
	if (!aim_at)
	{
		StopFiring();
	}

	return GetMostValuableTarget(possible_targets);
}

func Reload() // TODO:
{
//	// Munitionsart
//	var AmmoID = GetWeapon()->~GetFMData(FM_AmmoID);
//	// Erzeugen
//	Local(0, CreateContents(AmmoID)) = GetWeapon()->~GetFMData(FM_AmmoLoad);
//	// Waffe soll nachladen
//	GetWeapon()->~Reloaded(this);
//	GetWeapon()->~Recharge();
	StopFiring();
	//StartMoveSound();
}


func Damage()
{
	if (GetDamage() > MaxDamage() && !exploded)
	{
		exploded = true;
		Explode(20);
	}
}

func EMPShock()
{
	EMPShockEffect(20 * 35);
	
	StopFiring();
	return true;
}

/* Console control */ // TODO

func ConsoleControl(int i)
{
	if (i == 1)
	{
		if (sentry_gun.is_active)
			return "$TurnOff$";
		else
			return "$TurnOn$";
	}
	if (i == 2 && EMPShocked())
		return "$Repair$";
}

func ConsoleControlled(int i)
{
	if (i == 1)
	{
		if (sentry_gun.is_active)
			sentry_gun.is_active = 0;
		else
		{
			sentry_gun.is_active = 1;
		}
	}
	if (i == 3)
	{
		// do nothing temporarily
	}
}


/* Save scenario object */ // TODO

func Serialize(array extra)
{
//	extra[GetLength(extra)] = Format("SetTeam(%d)", GetTeam());
//	if (sentry_gun.is_active)
//		extra[GetLength(extra)] = "TurnOn()";
//	if (sentry_gun.weapon)
//	{
//		extra[GetLength(extra)] = Format("Arm(%i)", GetID(sentry_gun.weapon));
//		extra[GetLength(extra)] = Format("LocalN(\"sentry_gun.aim_angle\")=%d", sentry_gun.aim_angle);
//		extra[GetLength(extra)] = Format("LocalN(\"sentry_gun.aim_dir\")=%d", sentry_gun.aim_dir);
//	}
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
		var xoff_weapon = GetWeapon()->GetSentryGunOffsetX();
		var yoff_weapon = GetWeapon()->GetSentryGunOffsetY();
	
		SetObjDrawTransform(1000, 0, xoff_turret + Sin(angle, xoff_weapon) - Cos(angle, yoff_weapon),
		                    1000, 0, yoff_turret + Sin(angle, yoff_weapon) - Cos(angle, xoff_weapon), overlay);

		GetWeapon()->SetR(angle + 90);
	}
	else
	{
		SetGraphics(nil, GetID(), overlay);
	}
}

// effects
func RedDot()
{
	CreateLEDEffect(RGB(255, 0, 0), -2, -5, 8, 20);
}

func Bip()
{
	Sound("Weapon::Bip", false, 20);
}

func StartMoveSound(int volume)
{
	Sound("Weapon::Minigun::MiniTurn", false, volume, nil, +1);
}

func StopMoveSound()
{
	Sound("Weapon::Minigun::MiniTurn", false, nil, nil, -1);
}

