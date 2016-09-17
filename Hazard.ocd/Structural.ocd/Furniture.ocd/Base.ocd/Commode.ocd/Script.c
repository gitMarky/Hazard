
local action;

func Initialize()
{
	action = Random(2) + 1;
	SetAction(Format("Exist%d", action));
	SetDir(Random(2));
}

/*
func OnHit(int iDmg, int iType, object pFrom)
{
	if (GetDamage() > MaxDamage())
	{
		SetAction(Format("Broken%d", iAction));
		return true;
	}
}

func OnDmg(int iDmg, int iType)
{
	if (iType == DMG_Explosion)
		return 0;
	else
		return 100;
}

func MaxDamage()
{
	return 30;
}

func CanBeRecycled()
{
	return 2;
}
*/

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
	Directions = 1,
	Length = 1,
	X = 0,
	Y = 0,
	Wdt = 16,
	Hgt = 15,
	NextAction = "Hold",
},

Exist2 = {
	Prototype = Action,
	Name = "Exist2",
	Directions = 1,
	Length = 1,
	X = 30,
	Y = 0,
	Wdt = 16,
	Hgt = 15,
	NextAction = "Hold",
},

Broken1 = {
	Prototype = Action,
	Name = "Broken1",
	Directions = 1,
	Length = 1,
	X = 15,
	Y = 0,
	Wdt = 16,
	Hgt = 15,
	NextAction = "Hold",
	NoOtherAction = 1,
	ObjectDisabled = 1,
},

Broken2 = {
	Prototype = Action,
	Name = "Broken2",
	Directions = 1,
	Length = 1,
	X = 45,
	Y = 0,
	Wdt = 16,
	Hgt = 15,
	NextAction = "Hold",
	NoOtherAction = 1,
	ObjectDisabled = 1,
},

};
