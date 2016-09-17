func Initialize()
{
	SetAction("Open");
	SetDir(Random(2));
}

local ActMap = {
Open = {
	Prototype = Action,
	Name = "Open",
	Procedure = DFA_NONE,
	Directions = 2,
	Delay = 0,
	X = 0,
	Y = 0,
	Wdt = 21,
	Hgt = 30,
	NextAction = "Hold",
},

};
