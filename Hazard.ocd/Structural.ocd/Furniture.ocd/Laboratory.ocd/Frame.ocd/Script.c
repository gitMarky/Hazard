local look;

func Initialize()
{
	Set(Random(5) + 1);
}

func Set(int i)
{
	look = BoundBy(i, 1, 5);
	SetAction(Format("Exist%d", look));
}

func Damage()
{
	if (look != 1)
	{
		SetAction("Exist1");
		//for (var i = 5; i < 17; i += 2)
		//{
			//if (Random(2))
			//	CastParticles
			//	(
			//		"SplinterGlass",
			//		2,
			//		35,
			//		i,
			//		RandomX(17, 13),
			//		20,
			//		20,
			//		RGBa(255, 255, 255, 0),
			//		RGBa(255, 255, 255, 0)
			//	);
		//}
		Sound("Hits::Materials::Glass::GlassShatter");
		
		look = 1;
	}
}

func IsBulletTarget(object projectile)
{
	if (projectile->~NoDecoDamage()) return;
	return look != 1 && !Random(40);
}

/* Serialisierung */

func Serialize(array extra) // TODO: save object correctly
{
	extra[GetLength(extra)] = Format("Set(%d)", look);
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
Exist1 = {
	Prototype = Action,
	Name = "Exist1",
	Procedure = DFA_NONE,
	Directions = 1,
	Length = 1,
	FacetBase = 1,
	NextAction = "Hold",
},

Exist2 = {
	Prototype = Action,
	Name = "Exist2",
	Procedure = DFA_NONE,
	Directions = 1,
	Length = 1,
	X = 25,
	Y = 7,
	Wdt = 7,
	Hgt = 6,
	OffX = 5,
	OffY = 6,
	FacetBase = 1,
	NextAction = "Hold",
},

Exist3 = {
	Prototype = Action,
	Name = "Exist3",
	Procedure = DFA_NONE,
	Directions = 1,
	Length = 1,
	X = 34,
	Y = 6,
	Wdt = 9,
	Hgt = 7,
	OffX = 10,
	OffY = 6,
	FacetBase = 1,
	NextAction = "Hold",
},

Exist4 = {
	Prototype = Action,
	Name = "Exist4",
	Procedure = DFA_NONE,
	Directions = 1,
	Length = 1,
	X = 45,
	Y = 7,
	Wdt = 7,
	Hgt = 7,
	OffX = 13,
	OffY = 6,
	FacetBase = 1,
	NextAction = "Hold",
},

Exist5 = {
	Prototype = Action,
	Name = "Exist5",
	Procedure = DFA_NONE,
	Directions = 1,
	Length = 1,
	X = 25,
	Y = 6,
	Wdt = 17,
	Hgt = 7,
	OffX = 5,
	OffY = 6,
	FacetBase = 1,
	NextAction = "Hold",
},

Exist6 = {
	Prototype = Action,
	Name = "Exist6",
	Procedure = DFA_NONE,
	Directions = 1,
	Length = 1,
	X = 33,
	Y = 6,
	Wdt = 17,
	Hgt = 7,
	OffX = 7,
	OffY = 6,
	FacetBase = 1,
	NextAction = "Hold",
},

};
