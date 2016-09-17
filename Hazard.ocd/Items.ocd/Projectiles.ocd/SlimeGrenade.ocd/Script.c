#include Grenade_Normal

func OnLaunched()
{
	_inherited(...);
	AddAlienFlareEffect(300);
}

func Hit()
{
	Detonate();
}


func OnDetonation()
{
	for (var i = RandomX(7, 11); i > 0; i--)
	{
		var dist = 2;
		var launch_angle = Random(360);
		var x = 0, y = 0;
		for (var tries = 0; tries < 5; ++tries)
		{
			x = +Sin(launch_angle, dist);
			y = -Cos(launch_angle, dist);
			
			if (!GBackSolid(x,y)) break;

			launch_angle = Random(360);
		}


		var glob = CreateObject(Projectile_Slime, x, y, GetOwner());

		glob->Shooter(user)
            ->Weapon(this.weapon_ID)
            ->DamageAmount(this.damage)
 	        ->DamageType(this.damage_type)
		    ->Velocity(50)
            ->Range(PROJECTILE_Range_Infinite);

		glob->Launch(launch_angle);
	}

	CreateParticle("Slime", 0, 0, PV_Random(-20, 20), PV_Random(-10, 10), 25,
	{
		Prototype = Particles_WoodChip(),
		R = PV_Linear(0, 20),
		G = PV_Linear(240, 255),
		B = PV_Linear(0, 20),
		Alpha = PV_Linear(245, 180),
		Size = PV_Random(2, 4),
		BlitMode = GFX_BLIT_Additive, 
	}, 25);
	CreateParticle("FireSparkHazard", 0, 0, PV_Random(-10, 10), PV_Random(-5, 5), PV_Random(15, 40),
	{
		Prototype = Particles_Glimmer(),
		R = PV_Linear(120, 160),
		G = PV_Linear(240, 255),
		B = PV_Linear(0, 20),
		Alpha = PV_Linear(245, 180),
		Size = PV_Random(3, 7)
	}, 30);

	Sound("Weapon::Slime::SlimeHit");
	Sound("Weapon::Grenade::Poff");
	RemoveObject();
}

private func HandleTrail()
{
	// no effect, we have a slime trail after all
}


func ExplodeDelay()
{
	return 180;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
