#include Library_Turret

local exploded;
local sentry_gun;

local Name = "$Name$";

// external properties
func IsMachine(){	return true;}
func IsProjectileTarget(){	return true;}
func IsThreat(){	return sentry_gun.is_active;}

// internal properties
func TurretMaxRotLeft(){	return 110;}
func TurretMaxRotRight(){	return 250;}
func TurretSearchDistance(){	return 250;}

func MaxDamage(){	return 100;}

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
	lib_turret.aim_angle = 180;
	lib_turret.aim_dir = -1 + Random(2) * 2;

	var mount = CreateObject(weapon, 0, 0, GetOwner());
	mount->Enter(this);
	mount.Controller = this;
	lib_turret.weapon = mount;

	Reload();
	mount->~OnArmSentryGun(this); // give the weapon, e.g. an object with mesh graphics, a chance to change its shape and transformation
	return this;
}

// stuff

func Initialize()
{
	sentry_gun = 
	{
		is_active = false,
	};

	FitToTop();
	
	_inherited(...);
	
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
		lib_turret.target = FindTarget();
	}
	else
	{
		lib_turret.target_angle = Angle(GetWeaponX(), GetWeaponY(), GetTarget()->GetX(), GetTarget()->GetY());
		
		// fire at target?
		if (Abs(lib_turret.aim_angle - lib_turret.target_angle) < 15)
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
			lib_turret.target = nil;
		}
		else if (!PathFree(GetWeaponX(), GetWeaponY(), GetTarget()->GetX(), GetTarget()->GetY()))
		{
			lib_turret.target = nil;
		}
		else if (ObjectDistance(GetTarget(), this) > TurretSearchDistance())
		{
			lib_turret.target = nil;
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
		if (lib_turret.aim_angle <= TurretMaxRotLeft())
		{
			// go back
			lib_turret.aim_dir = 1;
			lib_turret.target_angle = TurretMaxRotRight();
			lib_turret.target = nil;
			sentry_gun.motion_delay = 100;
		}
		else if (lib_turret.aim_angle >= TurretMaxRotRight())
		{
			// go back
			lib_turret.aim_dir = -1;
			lib_turret.target_angle = TurretMaxRotLeft();
			sentry_gun.motion_delay = 100;
			lib_turret.target = nil;
		}
		if (!GetTarget())
		{
			lib_turret.aim_angle += lib_turret.aim_dir;
		}
	}
	
	// aim at target
	if (GetTarget())
	{
		StartMoveSound(30);
		TurretRotateToTarget(2);
		
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
	if (EMPShocked())
	{
		return false;
	}
	else
	{
		EMPShockEffect(20 * 35);
		
		StopFiring();
		return true;
	}
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
//	if (lib_turret.weapon)
//	{
//		extra[GetLength(extra)] = Format("Arm(%i)", GetID(lib_turret.weapon));
//		extra[GetLength(extra)] = Format("LocalN(\"lib_turret.aim_angle\")=%d", lib_turret.aim_angle);
//		extra[GetLength(extra)] = Format("LocalN(\"lib_turret.aim_dir\")=%d", lib_turret.aim_dir);
//	}
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

