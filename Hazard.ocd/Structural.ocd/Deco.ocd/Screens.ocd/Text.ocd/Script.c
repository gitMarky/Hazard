
func Initialize()
{
	SetAction("Animate");
	SetClrModulation(RGB(0, 255, 0));

	AddFrame();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Animate = {
	Prototype = Action,
	Name = "Animate",
	Procedure = DFA_NONE,
	Length = 21,
	Delay = 2,
	X = 0,
	Y = 0,
	Wdt = 40,
	Hgt = 20,
	NextAction = "Animate",
},

};
