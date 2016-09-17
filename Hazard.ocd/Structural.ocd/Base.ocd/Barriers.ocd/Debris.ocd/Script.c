
func SetDir(int dir)
{
	dir = BoundBy(dir, 0, 1);
	SetAction("Exist");
	SetPhase(dir);
	SetSolidMask(50 * dir, 0, 50, 30, 0, 0);
}


func Serialize(array extra) // TODO: implement saving object properly
{
	extra[GetLength(extra)] = Format("SetDir(%d)", GetDir());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Exist = {
	Prototype = Action,
	Name = "Exist",
	Length = 2,
	Delay = 0,
	X = 0,
	Y = 0,
	Wdt = 50,
	Hgt = 30,
	OffX = 0,
	OffY = 0,
	NextAction = "Exist",
},

};
