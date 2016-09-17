
func Initialize()
{
	SetAction("Animate");
	SetClrModulation(RGB(0, 255, 0));

	AddFrame();
	SetLightRange(75, 30);
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
	Length = 32,
	Delay = 3,
	X = 0,
	Y = 0,
	Wdt = 40,
	Hgt = 40,
	NextAction = "Animate",
},

};
