local smashed;

func Initialize()
{
	SetAction("Full");
	SetDir(Random(2));
}

func Damage()
{
	if (GetDamage() > 25 && !smashed)
	{
		Sound("Hits::Materials::Glass::GlassShatter");
		SetAction("Break");
		for (var i = -15; i < 20; i += 2)
		{
			//if (Random(2))
			//	CastParticles
			//	(
			//		"SplinterGlass",
			//		2,
			//		35,
			//		RandomX(-10, 10),
			//		i,
			//		20,
			//		20,
			//		RGBa(255, 255, 255, 0),
			//		RGBa(255, 255, 255, 0)
			//	);
			//if (Random(2))
			//	CastParticles
			//	(
			//		"SplinterGlass",
			//		2,
			//		35,
			//		RandomX(-10, 10),
			//		i,
			//		20,
			//		20,
			//		RGBa(255, 255, 255, 0),
			//		RGBa(255, 255, 255, 0)
			//	);
			if (!Random(5)) CastPXS("DuroLava", 5 + Random(5), 20, 0, 0);
		}

		smashed = true;
	}
}

func IsProjectileTarget(object projectile)
{
	if (smashed) return false;
	if (projectile->~NoDecoDamage()) return false;
	return !Random(20);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Full = {
	Prototype = Action,
	Name = "Full",
	Directions = 2,
	FlipDir = 1,
	Length = 1,
	X = 0,
	Y = 0,
	Wdt = 22,
	Hgt = 45,
	NextAction = "Hold",
},

Empty = {
	Prototype = Action,
	Name = "Empty",
	Directions = 2,
	FlipDir = 1,
	Length = 1,
	X = 22,
	Y = 0,
	Wdt = 22,
	Hgt = 45,
	NextAction = "Hold",
},

Break = {
	Prototype = Action,
	Name = "Break",
	Directions = 2,
	FlipDir = 1,
	Length = 1,
	Delay = 1,
	X = 44,
	Y = 0,
	Wdt = 22,
	Hgt = 45,
	NextAction = "Hold",
	NoOtherAction = 1,
	ObjectDisabled = 1,
},

};
