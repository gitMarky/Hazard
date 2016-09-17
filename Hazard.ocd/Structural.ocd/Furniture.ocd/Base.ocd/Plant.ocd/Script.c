local broken;

func Initialize()
{
	var random = Random(PlantCount());
	SetAction(Format("Plant%d", random + 1));
}

func Damage()
{
	if (broken)	return;
	broken = true;

	SetGraphics("Broken");
	SetRDir(RandomX(-10, 10));
	SetSpeed(RandomX(-10, 10), -20);
	
	var fade_time = 250;
	var pot =
	{
		Prototype = Particles_WoodChip(),
		OnCollision = PC_Stop(),
		Size = 5,
	};
	
	CreateParticle("HalfPot", -2, 0, PV_Random(-10, -15), -2, fade_time, pot, 1);
	CreateParticle("HalfPot", +2, 0, PV_Random(+10, +15), -2, fade_time, pot, 1);

	// lacks a sound :'(
	FadeOut(250, true);
}


func PlantCount()
{
	return 2;
}

// Can be hit by projectiles
func IsProjectileTarget(id def)
{
	if (broken) return false;
	if (def->~NoDecoDamage()) return false;
	return Random(2);
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
Plant1 = {
	Prototype = Action,
	Name = "Plant1",
	Length = 1,
	Delay = 1,
	X = 0,
	Y = 5,
	Wdt = 15,
	Hgt = 17,
	OffX = -5,
	OffY = -17,
	FacetBase = 1,
	NextAction = "Plant1",
	EndCall = "FadeOut",
},

Plant2 = {
	Prototype = Action,
	Name = "Plant2",
	Length = 1,
	Delay = 1,
	X = 15,
	Y = 11,
	Wdt = 39,
	Hgt = 11,
	OffX = -16,
	OffY = -11,
	FacetBase = 1,
	NextAction = "Plant2",
},

};
