
local smashed;

func IsProjectileTarget(object projectile)
{
	if (projectile->GetID() == Projectile_Missile) return false;
	if (smashed) return false;
	
	return !Random(3);
}

func Damage()
{
	if (!smashed)
	{
		smashed = true;
		Sound("Hits::Materials::Glass::GlassShatter");
	//for (var i = 0; i < 10; i++)
	//	CastParticles
	//	(
	//		"SplinterGlass",
	//		1,
	//		35,
	//		RandomX(-20, 20),
	//		-5,
	//		20,
	//		20,
	//		RGBa(255, 255, 255, 0),
	//		RGBa(255, 255, 255, 0)
	//	);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
