local smashed;

func IsProjectileTarget(object projectile)
{
	if (projectile->~NoDecoDamage()) return false;
	return !smashed && !Random(3);
}

func Damage()
{
	// already broken?
	if (smashed) return;
	smashed = true;

	// break!
	Sound("Hits::Materials::Glass::GlassShatter");
	/*
	for (var i = 0; i < 10; i++)
		CastParticles
		(
			"SplinterGlass",
			1,
			35,
			RandomX(-20, 20),
			-5,
			20,
			20,
			RGBa(255, 255, 255, 0),
			RGBa(255, 255, 255, 0)
		);
	*/
	// remove surface
	SetSolidMask();
}

func IsCraneGrabable(){	return true;}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
