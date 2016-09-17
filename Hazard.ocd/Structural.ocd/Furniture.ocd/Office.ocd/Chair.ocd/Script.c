func IsProjectileTarget()
{
	return Random(5);
}

func Damage()
{
	CreateSparksEffect(5, RGB(255, 255, 220));
}

func Initialize()
{
	SetAction("Exist");
	SetPhase(Random(6));
}

func CheckVertex()
{
	var dir = GetDir() * 2 - 1;
	SetVertex(0, 0, 4 * dir);
}

/* Serialisierung */

func Serialize(array extra)
{
	extra[GetLength(extra)] = Format("SetPhase(%d)", GetPhase());
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
Exist = {
	Prototype = Action,
	Name = "Exist",
	Length = 6,
	X = 0,
	Y = 0,
	Wdt = 10,
	Hgt = 15,
	NextAction = "Exist",
	EndCall = "CheckVertex",
},
};
