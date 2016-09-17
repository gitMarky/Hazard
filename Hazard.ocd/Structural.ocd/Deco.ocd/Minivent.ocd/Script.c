
func Initialize()
{
	SetAction("Turn");
}

local Name = "$Name$";
local ActMap = {

	Turn = {
		Prototype = Action,
		Name = "Turn",
		Length = 10,
		Delay = 2,
		NextAction = "Turn",
		X = 0,
		Y = 0,
		Wdt = 64,
		Hgt = 64,
	},
	
	RevTurn = {
		Prototype = Action,
		Name = "RevTurn",
		Length = 10,
		Delay = 2,
		Reverse = 1,
		NextAction = "RevTurn",
		X = 0,
		Y = 0,
		Wdt = 64,
		Hgt = 64,
	},
};
