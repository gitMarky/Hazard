

func IsProjectileTarget()
{
	return !Random(3);
}


// TODO: damage stuff
/*
func OnDmg(int iDmg, int iType)
{
	if (iType == DMG_Fire)
	{
		return -100;
	}
}

func OnHit(int iDmg, int iType, object pFrom)
{
	if (iType == DMG_Fire)
	{
		Incinerate();
	}
}


func Damage()
{
	// TODO: splinter
	//if (Random(2))
	//	CastObjects(SLNT, 1, 50, RandomX(-18, 18), RandomX(-5, 1));
	Sound("WoodHit*");
	// TODO: break
	if (Inside(GetDamage(), 14, 19))
	{
		CastObjects(SLNT, 1, 45, RandomX(-18, 18), RandomX(-5, 1));
		CastObjects(SLNT, 1, 45, RandomX(-18, 18), RandomX(-5, 1));
		Sound("CrateCrack");
		RemoveObject();
	}
}
*/

func Initialize()
{
	SetAction("Exist");
}


func CheckVertex()
{
	var dir = GetDir() * 2 - 1;
	SetVertex(0, 0, 4 * dir);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 20;
local BurnTo = CHAB;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Exist = {
	Prototype = Action,
	Name = "Exist",
	Directions = 2,
	FlipDir = 1,
	Delay = 5,
	X = 0,
	Y = 0,
	Wdt = 10,
	Hgt = 15,
	NextAction = "Exist",
	EndCall = "CheckVertex",
},

};
