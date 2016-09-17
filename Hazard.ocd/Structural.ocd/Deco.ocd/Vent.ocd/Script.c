
func Initialize()
{
	SetAction("Turn");
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
Turn = {
	Prototype = Action,
	Name = "Turn",
	Length = 20,
	Delay = 1,
	X = 64,
	Y = 0,
	Wdt = 128,
	Hgt = 128,
	NextAction = "Turn",
	Sound = "Structural::VentLoop",
},

RevTurn = {
	Prototype = Action,
	Name = "RevTurn",
	Length = 20,
	Reverse = 1,
	Delay = 1,
	X = 64,
	Y = 0,
	Wdt = 128,
	Hgt = 128,
	NextAction = "RevTurn",
	Sound = "Structural::VentLoop",
},

};
