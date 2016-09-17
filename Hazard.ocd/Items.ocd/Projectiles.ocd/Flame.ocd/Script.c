#include Library_Projectile

local slimy;
local hits;


private func OnLaunch()
{
	SetAction("Travel");
	
	SetLightRange(40, 30);
	var color;
	if (!slimy)
	{
		color = FIRE_LIGHT_COLOR;
	}
	else
	{
		color = FIRE_Green;
	}
	SetLightColor(color);	
}

func Slime()
{
	slimy = true;
	return this;
}


func OnTravelling()
{
	if (InLiquid())
	{
		// Blubberblubber
		for (var i = 0; i < 5; ++i)
		{
			Bubble(RandomX(-5, +5), RandomX(-5, 5));
		}
		RemoveObject();
		return;
	}
	
	if (!Random(4) && GetActTime() > GetLifetime() / 4)
	{
		SetYDir(GetYDir() + RandomX(-4, 2));
	}
	
	if (slimy)
	{
		CastSlimeEffects(GetActTime());
	}
	else
	{
		CastFireEffects(GetActTime());
	}
}


func GetWeaknessFactor()
{
	return Max(100 - hits * 20, 0);
}

func GetDamageAmount()
{
	return GetWeaknessFactor() * _inherited(...) / 100;
}


func OnHitObject(object target, proplist fx_hitcheck)
{
	var color;
	if (!slimy)
	{
		color = FIRE_Red;
	}
	else
	{
		color = FIRE_Green;
	}
	
	hits++;
	
	if (target && (target->GetOCF() & OCF_Inflammable))
	{
		// incinerate inflammables, but not living things
		if (target->GetOCF() & OCF_Alive)
		{
			// TODO: AddFireEffect(pObj, 50, color, 1);
		}
		else
		{
			target->Incinerate();
		}
	}
}

func FireSize()
{
	return Min(180, 20 + GetActTime() * 6) / 7;
}


func CastFireEffects(int time)
{
	var maxtime = GetLifetime();
	var angle = Angle(0, 0, GetXDir(), GetYDir());
	var speed = Distance(0, 0, GetXDir(), GetYDir());

	var ntime = 20 * time / maxtime;

	var size = FireSize();

	var xoff = RandomX(-2, 5) + ntime / 2;
	var yoff = RandomX(-ntime, ntime);

	var xdir = +Cos(angle, yoff) - Sin(angle, xoff);
	var ydir = +Sin(angle, yoff) + Cos(angle, xoff);

	for (var i = 0; i < 3; i++)
	{
		var x = Sin(angle, +10 - 2 * i);
		var y = RandomX(-size, size) / 4;
		
		var alpha = 255 - BoundBy(180 - speed / 4 - time / 2, 0, 255);
		
		CreateParticle("Fire", x, y, xdir, ydir, PV_Random(20, 30),
		{
			Prototype = Particle_SharpFlame(),
			Size = size,
			Alpha = PV_Linear(alpha, 0),
		}, 1);
	}
}

func CastSlimeEffects(int time)
{
	var maxtime = GetLifetime();
	var dir = (GetXDir() > 0) * 2 - 1;
	var angle = Angle(0, 0, GetXDir(), GetYDir());

	var size = FireSize();

	var ntime = 30 * time / maxtime;

	var xoff = RandomX(-2, 5);
	var yoff = RandomX(-ntime, ntime) / 2;

	var xdir = +Cos(angle, yoff) - Sin(angle, xoff);
	var ydir = +Sin(angle, yoff) + Cos(angle, xoff);

	for (var i = 0; i < 3; i++)
	{
		var x = (+10 - 2 * i) * dir;
		var y = RandomX(-size, size) / 4;
		
		var alpha = 255 - BoundBy(ntime, 0, 255);
		
		CreateParticle("MagicFire", x, y, xdir, ydir, 15,
		{
			Prototype = Particle_SharpFlame(),
			R = PV_Linear(50, 0),
			G = PV_Linear(155, 10),
			B = 0,
			Alpha = PV_Linear(alpha, 0),
			Size = size,
		}, 1);
	}
}

func Hit()
{
	RemoveObject();
}

func NoWarp()
{
	return true;
}

func Particle_SharpFlame()
{
	return
	{
		R = 255,
		G = PV_KeyFrames(0, 0, 255, 666, 0, 627, 0),
		B = 0,
		Rotation = PV_Random(-5, 5),
		Phase = PV_Random(0, 4),
		OnCollision = 0,
		BlitMode = GFX_BLIT_Additive
	};

}
