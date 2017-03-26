/* ----------------------------- Support Drone ----------------------------- */
// Newton: scripted for CR Hazard 2.1

#include Library_Turret
#include Library_HazardEquipment

local guarded_clonk;		// the clonk to follow. Can be null if the drone should be autonomous
local target_x, target_y;	// target position where to go
local previous_xdir;		// previous X speed. Used for thruster effect
local is_following;			// whether the drone follows the clonk
local is_autonomous;		// whether the drone has a guarded_clonk at all.
local destroyed;

func TurretMaxRotLeft(){	return 90;}
func TurretMaxRotRight(){	return 270;}
func GetWeaponX(){			return GetX();}
func GetWeaponY(){			return GetY() + 7;}


func Initialize()
{
	_inherited(...);

	lib_turret.aim_angle = lib_turret.target_angle = 160;
	SetAction("Idle");
}

/**
 Adds the drone to a clonk, with the selected weapon
 */
func ArmToClonk(object clonk, object weapon)
{
	if (!clonk || !weapon)
	{
		FatalError(Format("You have to provide a clonk (%v) and a weapon (%v)", clonk, weapon));
	}

	guarded_clonk = clonk;
	is_following = true;
	GetArmed(nil, weapon);
}

/**
 Arm with weapon, without protecting a clonk.
 The drone will use its own ammo storage then.
 If it is empty, it is empty.
 */
func Arm(object weapon)
{
	if (!weapon)
	{
		FatalError("You have to provide a weapon, got nil.");
	}

	if (!is_following) is_autonomous = true;

	weapon->Exit();
	weapon->Enter(this);

	SetCategory(C4D_Vehicle);
	SetAction("Fly");
	lib_turret.weapon = weapon;
	CreateEffect(IntGuard, 1, 2);
	return true;
}

/**
 Switch following the clonk (if any) on or off
 */
func FollowClonk(bool do_follow)
{
	is_following = do_follow;
}

/**
 Set position at which the drone should go. While following a clonk, this 
 value will be re-set every few frames.
 */
func SetGuardPosition(int x, int y)
{
	target_x = x;
	target_y = y;
}

/**
 Gets the clonk that is guarded.
 */
func GetGuardedClonk()
{
	return guarded_clonk;
}

/* ------------- Damage ------------ */

func OnDmg(int damage, int type)
{
// TODO
//	if (type == DMG_Melee) 			 return -30;
//	else if (type == DMG_Projectile) return +20;
//	else if (type == DMG_Fire)		 return +30;
//	else if (type == DMG_Explosion)	 return -10;
//	else if (type == DMG_Energy)	 return -40;
//	else if (type == DMG_Bio)		 return +50;
}

func Damage()
{
	if (GetDamage() < MaxDamage()) return;
	if (!destroyed)
	{
		destroyed = true;
		TurnOff();
		Explode(20);
	}
}

/** Using the drone */

func ControlUse(object user, int x, int y)
{
	return Activate(user);
}


func Activate(object user)
{
	//if (!(user->~CanUse(GetID())))
	//	return true;
	
	// only one drone per clonk
	var drone;
	for (drone in FindObjects(Find_Func("IsDrone"), Find_Action("Fly"), Find_Owner(user->GetOwner()))) 
	{
		if (drone->GetGuardedClonk() == user)
		{
			user->InfoMessage("$JustOneDrone$", user);
			Sound("UI::Error", nil, nil, user->GetOwner() + 1);
			return true;
		}
	}
	
	if (EMPShocked())
	{
		user->InfoMessage("$Damaged$", user);
			Sound("UI::Error", nil, nil, user->GetOwner() + 1);
		return true;
	}
	
	guarded_clonk = user;
	is_following = true;
	
	user->CreateMenu(GetID(), this, 0, "$NoWeap$");
	for (var weapon in FindObjects(Find_Container(user), Find_Func("IsHazardWeapon")))
	{
		user->AddMenuItem("$ArmWith$", "GetArmed", weapon->GetID(), 0, weapon);
	}
	
	return true;
}

func GetArmed(id item, object weapon)
{
	if (!Arm(weapon)) return false;
	if (guarded_clonk) guarded_clonk->HelpMessage("$ArmedWith$", guarded_clonk, weapon->GetName());
	return true;
}

local IntGuard = new Effect
{
	Start = func(int temp)
	{
		if (temp) return;
		this.Target->StartFxGuard();
	},
	
	Stop = func()
	{
		this.Target->StopFxGuard();
	},
	
	Timer = func(int time)
	{
		return this.Target->TimerFxGuard(time);
	},
};

func StartFxGuard()
{
	Exit();
	
	Log("Start FxGuard");
	
	// look for ammo in the weapon, otherwise reload.
	var ammoid = lib_turret.weapon->GetFiremode().ammo_id;
	var ammoload = lib_turret.weapon->GetFiremode().ammo_load;

	if (lib_turret.weapon->~GetAmmo(ammoid) < ammoload)
		lib_turret.weapon->Reload();

	if (guarded_clonk)
	{
		SetController(guarded_clonk->GetController());
		SetOwner(guarded_clonk->GetOwner());
		target_x = guarded_clonk->GetX();
		target_y = guarded_clonk->GetY();
	}
	else
	{
		target_x = GetX();
		target_y = GetY();
	}
}

func StopFxGuard()
{
	SetAction("Idle");
	SetCategory(C4D_Object);
	
	if (lib_turret.weapon)
	{
		lib_turret.weapon->Exit();
	}
	lib_turret.weapon = nil;
	guarded_clonk = nil;
	lib_turret.target = nil;
	target_x = target_y = previous_xdir = 0;
	is_autonomous = is_following = false;
	lib_turret.aim_angle = lib_turret.target_angle = 160;
}

func TimerFxGuard(int time)
{
	if (!lib_turret.weapon) return FX_Execute_Kill;
	
	var xDiffDir = GetXDir() - previous_xdir;
	var thrustStrength = Min(Abs(xDiffDir) * 10, 50);
	var thrustX = xDiffDir / Max(1, Abs(xDiffDir));
	if (thrustX)
	{
		CreateParticle("MuzzleFlashDesaturated", -10 * thrustX, -3, -thrustX * 10, 0, Min(Abs(xDiffDir) * 2, 30),
		{
			Prototype = Particles_MuzzleFlash(),
			Size = PV_Linear(thrustStrength, 0),
			R = 64, G = 128, B = 255,
			Alpha = PV_Linear(200, 0),
			Rotation = Angle(thrustX, 0, 0, 0),
		});
	}

	CreateParticle("Magic", PV_Random(-3, 3), 5, 0, PV_Random(2, 5), 20, 
	{
		Prototype = Particles_Dust(),
		Size = PV_Random(22, 28),
		R = 128, G = 196, B = 255,
		Alpha = PV_Linear(20, 0),
		BlitMode = GFX_BLIT_Additive,
	});
	
	previous_xdir = GetXDir();
	
	// adjust aim angle
	TurretRotateToTarget(4);
	
	// other stuff only every 6th frame
	if (time % 6) return FX_OK;
	
	if (lib_turret.weapon->IsReloading() && time % 30 == 0)
	{
		CreateLEDEffect(RGB(255, 0, 0), 0, 0, 8, 20);
	}

	// does the clonk still live? :o
	if (!is_autonomous && (!guarded_clonk || !guarded_clonk->GetAlive()))
	{
		TurnOff();
		return FX_Execute_Kill;
	}
	
	HandleMovement(time);
	HandleFiring();	
}

func HandleMovement(int time)
{
	if (is_following && guarded_clonk)
	{
		target_x = guarded_clonk->GetX();
		target_y = guarded_clonk->GetY();
	}
	
	// beam to user if the distance is too large
	if (Distance(GetX(), GetY(), target_x, target_y) > GetBeamToClonkDistance())
	{
		lib_turret.target = nil;
		Beam(this, nil, target_x, target_y);
		return 0;
	}
	
	// d
	var x = target_x;
	var y = target_y;
	var yoffset = GetFlightHeight();
	for (var i = 0; i < yoffset; ++i)
	{
		if (GBackSolid(AbsX(x), AbsY(y - i)))
			break;
	}
	y = y - i + 25;
	
	if (!GetCommand() || time % 60 == 0)
	{
		SetCommand("MoveTo", nil, x, y);
	}
}

func HandleFiring()
{
	// acquire target
	lib_turret.target = AcquireTarget();
	
	if (GetTarget())
	{
		lib_turret.target_angle = Angle(GetX(), GetY(), GetTarget()->GetX(), GetTarget()->GetY());
		var halfAimDelta = Abs(Normalize(lib_turret.target_angle - lib_turret.aim_angle, 180)) / 2;
		
		var targetDistance = Distance(GetX(), GetY(), GetTarget()->GetX(), GetTarget()->GetY());
		var targetSize = Distance(0, 0, GetTarget()->GetDefHeight(), GetTarget()->GetDefWidth());
		
		if (1000 * targetSize / 2 >= targetDistance * Sin(halfAimDelta, 1000))
		{
			StartFiring();
		}
	}
	else
	{
		StopFiring();
	}
}

func WayFree(object enemy)
{
	// test whether the path to the enemy is free of friends.
	if (FindObject(
		Find_OnLine(0, 0, enemy->GetX() - GetX(), enemy->GetY() - GetY()),
		Find_OCF(OCF_CrewMember),
		Find_Not(Find_Hostile(GetOwner()))
	))
		return false;
	
	return true;
}

func AcquireTarget()
{
	var range = TurretSearchDistance();// TODO: Min(TurretSearchDistance(), lib_turret.weapon->GetBotData(BOT_Range));
	var enemy;
	for (enemy in FindProjectileTargets(range, guarded_clonk ?? this, this)) 
	{
		if (WayFree(enemy))
		{
			return enemy;
		}
	}
}

func TurnOff()
{
	if (GetEffect("Guard", this))
		RemoveEffect("Guard", this);
}

func GetAmmoSource(id ammo)
{
	if (guarded_clonk)
	{
		return AMMO_Source_Container;
	}
	else
	{
		return AMMO_Source_Local;
	}
}

func GetAmmoContainer()
{
	return guarded_clonk ?? this;
}


func EMPShock()
{
	TurnOff();
	EMPShockEffect(15 * 35);
	return true;
}

func RejectEntrance()
{
	return !!GetEffect("Guard", this);
}

func ReadyToFire()
{
	return !!GetEffect("Guard", this);
}

func IsProjectileTarget()
{
	return !!GetEffect("Guard", this);
}

func MaxDamage()
{
	return 80;
}

func IsDrone()
{
	return true;
}
func IsEquipment()
{
	return true;
}
func IsMachine()
{
	return true;
}

func IgnoreFriendlyFire()
{
	return true;
}

func GetArenaRemoveTime()
{
	return 300;
}
func GetBeamToClonkDistance()
{
	return 400;
}
func GetFlightHeight()
{
	return 60;
}

// KI-Behandlung
// TODO:
//func AI_Inventory(object clonk)
//{
//	
//	//Checken, ob der Clonk nicht schon eine hat. :Ooo
//	var drone;
//	
//	// Kann Ding nicht benutzen...
//	if (!(clonk->~CanUse(GetID())))
//		return false;
//	// Nur eine
//	for (var drone in FindObjects(Find_Func("IsDrone"), Find_Action("Fly"))) 
//		if (clonk->GetOwner() == drone->GetOwner())
//			if (drone->GetGuardedClonk() == clonk)
//				return false;
//	// Nicht, wenn kaputt
//	if (EMPShocked())
//		return false;
//	// Drohne ist zulässig. Nur einsetzen, wenn der Clonk mehr als 1 Waffe hat
//	if (clonk->CustomContentsCount("IsWeapon") < 2)
//		return true;
//	// Waffen für Drohne ok? (FM_Aim und so)
//	var wpn = clonk->GetRandomDroneWeapon();
//	if (!wpn)
//		return true;
//	// Waffe nehmen (verzögert)
//	ScheduleCall(this, "ArmToClonk", 1, 0, clonk, wpn);
//	return true;
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = true;
local BorderBound = 7;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Fly = {
	Prototype = Action,
	Name = "Fly",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 1,
	X = 0,
	Y = 0,
	Wdt = 20,
	Hgt = 18,
	Speed = 200,
	Accel = 16,
	Decel = 16,
	NextAction = "Fly",
},

Idle = {
	Prototype = Action,
	Name = "Idle",
	Procedure = DFA_NONE,
	Length = 1,
	X = 0,
	Y = 0,
	Wdt = 20,
	Hgt = 18,
	NextAction = "Idle",
},

};
