
func Initialize()
{
	SetAction("Black");
	AddFrame();
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
Black = {
	Prototype = Action,
	Name = "Black",
	Delay = 30,
	FacetBase = 1,
	NextAction = "Krsl",
},

Krsl = {
	Prototype = Action,
	Name = "Krsl",
	Length = 3,
	Delay = 5,
	X = 30,
	Y = 0,
	Wdt = 30,
	Hgt = 25,
	NextAction = "KrslB",
},

KrslB = {
	Prototype = Action,
	Name = "KrslB",
	Length = 3,
	Reverse = 1,
	Delay = 5,
	X = 30,
	Y = 0,
	Wdt = 30,
	Hgt = 25,
	NextAction = "Drink",
},

Drink = {
	Prototype = Action,
	Name = "Drink",
	Length = 5,
	Delay = 15,
	X = 0,
	Y = 25,
	Wdt = 30,
	Hgt = 25,
	NextAction = "Super",
},

Super = {
	Prototype = Action,
	Name = "Super",
	Delay = 50,
	X = 0,
	Y = 50,
	Wdt = 30,
	Hgt = 25,
	NextAction = "SuperBlink1",
},

SuperBlink1 = {
	Prototype = Action,
	Name = "SuperBlink1",
	Length = 2,
	Delay = 5,
	X = 0,
	Y = 50,
	Wdt = 30,
	Hgt = 25,
	NextAction = "SuperBlink2",
},

SuperBlink2 = {
	Prototype = Action,
	Name = "SuperBlink2",
	Length = 2,
	Delay = 5,
	X = 0,
	Y = 50,
	Wdt = 30,
	Hgt = 25,
	NextAction = "SuperBlink3",
},

SuperBlink3 = {
	Prototype = Action,
	Name = "SuperBlink3",
	Length = 2,
	Delay = 5,
	X = 0,
	Y = 50,
	Wdt = 30,
	Hgt = 25,
	NextAction = "Krsl2",
},

Krsl2 = {
	Prototype = Action,
	Name = "Krsl2",
	Length = 3,
	Delay = 5,
	X = 30,
	Y = 0,
	Wdt = 30,
	Hgt = 25,
	NextAction = "KrslB2",
},

KrslB2 = {
	Prototype = Action,
	Name = "KrslB2",
	Length = 3,
	Reverse = 1,
	Delay = 5,
	X = 30,
	Y = 0,
	Wdt = 30,
	Hgt = 25,
	NextAction = "Black",
},

};
