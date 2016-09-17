#include Library_Projectile

local exploded, nospeed;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// behaviour

private func OnLaunch()
{
	SetAction("TravelBallistic");
}

func Hit()
{
	Detonate();
}

func HitObject()
{
	Detonate();
}


func Destruct()
{
	Detonate();
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
	Explode(damage);
}



func OnTraveling ()
{
	// it is lying around? destroy!
	if(!GetXDir() && !GetYDir())
	{
		if (!nospeed)
		{
			nospeed = true;
		}
		else
		{
			Detonate();
		}
	}
	else
	{
		nospeed = false;
	}

	CreateParticle("Smoke2", 0, 0, PV_Random(-15, 15), -5, PV_Random(30, 50),
	{
		Prototype = Particles_Smoke(),
		Size = PV_Random(8, 16),
		R = 100, G = 100, B = 100,
		Alpha = PV_Linear(195, 0),
	}, 1);
}
