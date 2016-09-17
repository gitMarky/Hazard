#include Library_Projectile

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// behaviour

private func OnLaunch()
{
	exploded = false;
	SetAction("TravelBallistic");
	AddEffect("Grenade", this, 1, 1, this);
	
	rotation_by_rdir = true;
	SetR(RandomX(-180, 180));
	SetRDir(RandomX(-10, 10) * 10);
}


func Hit()
{
	Bounce();
}


func Bounce()
{
	var x, y;
	var rdir = GetRDir();
	var mirror_rdir = false;
	
	// contact at the sides?
	if (GetContact(-1) & CNAT_Right)
	{
		x = -(Abs(GetXDir() / 4) + Random(3));
		mirror_rdir = true;
	}
	else if (GetContact(-1) & CNAT_Left)
	{
		x = Abs(GetXDir() / 4) + Random(3);
		mirror_rdir = true;
	}
	else
	{
		x = GetXDir() / 2;
	}
	
	// contact above and below
	if (GetContact(-1) & CNAT_Top)
	{
		y = Abs(GetYDir() / 3);
	}
	else if (GetContact(-1) & CNAT_Bottom)
	{
		y = -(Max(Abs(GetYDir() / 4), Abs(GetXDir()) / 4) + Random(3));
	}
	else
	{
		y = GetYDir() / 2;
	}

	// adjust velocity
	SetXDir(x);
	SetYDir(y);
	
	var rdir_factor = Sign(GetRDir());
	if (mirror_rdir) rdir_factor *= -1;
	SetRDir(rdir_factor * RandomX(Abs(rdir) / 2, Abs(rdir)));
	
	if (Abs(x) < 5 && Abs(y) < 5) SetRDir();

	// nice effects
	Sound("Weapon::Grenade::GrenadeHit?");
}


func Detonate()
{
	RemoveEffect("Grenade", this, nil, true);

	if (!exploded)
	{
		exploded = true;
		OnDetonation();
	}
}

func OnDetonation()
{
	BlastObjects(damage / 4);
	Explode(damage);
}

func ExplodeDelay()
{
	return 110;
}

private func HandleTrail()
{
	var speed = Abs(GetXDir()) + Abs(GetYDir());
	var alpha = Min(205, 105 + speed);
	var lifetime_base = speed / 2;
	
	CreateParticle("Smoke",
	               -GetXDir() / 6, -GetYDir() / 6,
	                PV_Random(-15, 15), -5,
	               PV_Random(10, 20),
	               {
		               Prototype = Particles_Thrust(),
		               Size = PV_Linear((lifetime_base + 20) / 10, (lifetime_base + 60) / 10),
		               R = 100, G = 100, B = 100, Alpha = alpha
	               });
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// callbacks


func HitObject()
{
	Detonate();
}


func Destruct()
{
	Detonate();
}


func IsProjectileTarget()
{
	return !exploded;
}

func NoDecoDamage()
{
	return true;
}

func FxGrenadeTimer(object target, proplist fx, int time)
{
	if (time > ExplodeDelay())
	{
		Detonate();
		return FX_Execute_Kill;
	}
	
	HandleTrail();
}


func FxGrenadeDamage()
{
//	Detonate();
}


func IsBouncy(){ return true; } // gets launched by jump pad

// TODO
func OnDmg(int iDmg, int iType)
{
//	if (iType == DMG_Bio)
//		return 100;
//	if (iType == DMG_Fire)
//		return 100;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local ContactCalls = true;
local exploded;
