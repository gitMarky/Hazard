#include Weapon_Base

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local carry_mode =  CARRY_Blunderbuss;

local is_running;

public func GetCarryTransform()
{
	return Trans_Mul(Trans_Rotate(90, 1, 0, 0), Trans_Translate(-3000, 1000, 500));
}

public func Initialize()
{
	_inherited(...);
	is_running = false;
	firemode_standard = FiremodeStandard();
	ChangeFiremode(firemode_standard);
}

func Definition(id def)
{
	def.PictureTransformation = Trans_Mul(Trans_Rotate(230, 0, 1, 0), Trans_Rotate(20, 0, 0, 1), Trans_Rotate(-10, 1, 0, 0), Trans_Translate(0, -1500, -2000));
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
		name = 			"$Saw$",
		ammo_id = 		Ammo_Gasoline,
		ammo_load = 	20,

		delay_reload = 	120,
		delay_recover = 4,
		delay_cooldown = 19,

		ammo_usage = 		1,
		ammo_rate = 		10,
		mode = 		WEAPON_FM_Auto,

		projectile_id = Projectile_Invisible,
		projectile_range = 15,
		projectile_speed = 15,

		damage = 		10,
	};
}


public func OnFireProjectile(object user, object projectile, proplist firemode)
{
	projectile.OnHitObject = this.ChainsawOnHitObject;
	projectile.OnHitLandscape = this.ChainsawOnHitLandscape;
	projectile->HitScan();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Walking speed adjustments

func WalkNormal(object user)
{
	// TODO
}

func WalkSlow(object user)
{
	// TODO
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Sound effects

public func FireSound(object user, proplist firemode)
{
	if (!is_running)
	{
		is_running = true;
		Sound("Weapon::Chainsaw::chainsaw_start");
		WalkSlow(user);
		ScheduleCall(this, this.ChainsawSound, 19);
	}
}

func ChainsawSound()
{
	if (is_running)
	{
		Sound("Weapon::Chainsaw::chainsaw", nil, nil, nil, 1);
	}
}

public func OnStartCooldown(object user, proplist firemode)
{
	Sound("Weapon::Chainsaw::chainsaw", nil, nil, nil, -1);
	if (is_running)
	{
		is_running = false;
		Sound("Weapon::Chainsaw::chainsaw_stop");
		WalkNormal(user);
	}
}

public func OnSelect()
{
	Sound("Weapon::Chainsaw::chainsaw_idle", nil, nil, nil, 1);
}

public func OnDeselect()
{
	Sound("Weapon::Chainsaw::chainsaw_idle", nil, nil, nil,-1);
}

protected func Departure()
{
	_inherited(...);
	OnDeselect();
}

public func OnReload()
{
	Sound("Weapon::Flamethrower::FlamerLoad");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Projectile stuff, these are local overloads for the function in the actual projectile

func ChainsawOnHitObject(object target)
{
	// cheap twitching effect placed on the victim..
	target ->~ SetAction("Jump");
	
	var xdir = GetX() - this->~GetShooter()->GetX(); xdir *= 2;
	var ydir = GetY() - this->~GetShooter()->GetY(); ydir *= 2;

	CreateImpactEffect(4, 0, 0, "SmokeDirty",
	{
		Prototype = Particles_Glimmer(),
		R = 255,
		G = PV_Random(100, 155),
		B = PV_Random(0, 220),
		Alpha = PV_Linear(128, 0),
		Size = PV_Random(2, 4),
		BlitMode = 0,
	});
}

func ChainsawOnHitLandscape()
{
	var xdir = GetX() - this->~GetShooter()->GetX(); xdir *= 2;
	var ydir = GetY() - this->~GetShooter()->GetY(); ydir *= 2;

	CreateImpactEffect(10, -xdir / 10, -ydir / 10);
}
