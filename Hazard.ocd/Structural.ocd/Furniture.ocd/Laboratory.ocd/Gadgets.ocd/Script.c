local damaged;

func Initialize()
{
	Set(Random(GetActions()) + 1);
}

func Set(int i)
{
	i = BoundBy(i, 1, GetActions());
	Call(Format("Gadget%d", i));
}

func GetActions(){return 3;}

/* Settings for each gadget */

func Gadget1()
{
	SetAction("Gadget1");
	SetVertexXY(0, -4, 7);
	SetVertexXY(1, 4, 7);
}

func Gadget2()
{
	SetAction("Gadget2");
	SetVertexXY(0, -9, 9);
	SetVertexXY(1, 9, 9);
}

func Gadget3()
{
	SetAction("Gadget3");
	SetVertexXY(0, -9, 8);
	SetVertexXY(1, 9, 8);
}

/* Hit? */

func IsProjectileTarget(object projectile)
{
	return !(projectile->~NoDecoDamage());
}

func Damage(int amount)
{
	if (damaged) return;
	damaged = true;

	// lots of glass!
	// TODO: CastParticles("SplinterGlass", 5 + Random(5), 50, 0, 0, 20, 25, RGBa(255, 255, 255), RGBa(255, 255, 255));
	// liquids
	if (GetAction() != "Gadget3")
	{
		if (Random(2)) CastPXS("Acid", 5 + Random(10), 50);
		if (Random(2)) CastPXS("DuroLava", 5 + Random(10), 50);
	}
	// Smoke
	CreateSmokeTrail(RandomX(15, 20), Random(360), 0, 0, nil, true);
	CreateSmokeTrail(RandomX(15, 20), Random(360), 0, 0, nil, true);
	// Sound
	Sound("Hits::Materials::Glass::GlassShatter");
	// explode 
	if (Random(2))
	{
		Explode(5 + Random(5));
	}
	else
	{
		RemoveObject();
	}
}


// TODO: save object
/*func Serialize(array extra)
{
	extra[GetLength(extra)] = Format("Set(%s)", GetAction());
}*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Gadget1 = {
	Prototype = Action,
	Name = "Gadget1",
	Procedure = DFA_NONE,
	Directions = 1,
	Length = 9,
	Delay = 2,
	X = 0,
	Y = 0,
	Wdt = 9,
	Hgt = 15,
	NextAction = "Gadget1",
},

Gadget2 = {
	Prototype = Action,
	Name = "Gadget2",
	Length = 1,
	X = 0,
	Y = 15,
	Wdt = 11,
	Hgt = 18,
	NextAction = "Gadget2",
},

Gadget3 = {
	Prototype = Action,
	Name = "Gadget3",
	Length = 1,
	X = 14,
	Y = 15,
	Wdt = 10,
	Hgt = 17,
	NextAction = "Gadget3",
},

};
