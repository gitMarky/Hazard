
local blink_counter, credits_counter;

func Initialize()
{
	Start();
	AddFrame();
}

func Start()
{
	SetAction("LoadPlanet");
	blink_counter = 0;
	credits_counter = 0;
}

func BlinkPlanet()
{
	if (++blink_counter > 2)
	{
    	blink_counter = 0;
    	SetAction("LoadEurope");
	}
}

func BlinkEurope()
{
	if (++blink_counter > 2)
	{
	    blink_counter = 0;
    	SetAction("LoadMidEurope");
	}
}

func Credits()
{
	  if (credits_counter == 0) SetAction("Matthi");
	  if (credits_counter == 1) SetAction("Newton");
	  if (credits_counter == 2) SetAction("Boni");
	  if (credits_counter == 3) SetAction("Clonko");
	  if (credits_counter == 4) SetAction("Raven");
	  
	  if (credits_counter == 5) Start();
	  else        ++credits_counter;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
LoadPlanet = {
	Prototype = Action,
	Name = "LoadPlanet",
	Procedure = DFA_NONE,
	Length = 9,
	Delay = 4,
	X = 0,
	Y = 0,
	Wdt = 60,
	Hgt = 40,
	NextAction = "Planet",
},

Planet = {
	Prototype = Action,
	Name = "Planet",
	Procedure = DFA_NONE,
	Length = 1,
	Delay = 100,
	X = 480,
	Y = 0,
	Wdt = 60,
	Hgt = 40,
	NextAction = "BlinkPlanet",
},

BlinkPlanet = {
	Prototype = Action,
	Name = "BlinkPlanet",
	Procedure = DFA_NONE,
	Length = 2,
	Delay = 15,
	X = 480,
	Y = 0,
	Wdt = 60,
	Hgt = 40,
	NextAction = "BlinkPlanet",
	EndCall = "BlinkPlanet",
},

LoadEurope = {
	Prototype = Action,
	Name = "LoadEurope",
	Procedure = DFA_NONE,
	Length = 9,
	Delay = 4,
	X = 0,
	Y = 40,
	Wdt = 60,
	Hgt = 40,
	NextAction = "Europe",
},

Europe = {
	Prototype = Action,
	Name = "Europe",
	Procedure = DFA_NONE,
	Length = 1,
	Delay = 100,
	X = 480,
	Y = 40,
	Wdt = 60,
	Hgt = 40,
	NextAction = "BlinkEurope",
},

BlinkEurope = {
	Prototype = Action,
	Name = "BlinkEurope",
	Procedure = DFA_NONE,
	Length = 2,
	Delay = 15,
	X = 480,
	Y = 40,
	Wdt = 60,
	Hgt = 40,
	NextAction = "BlinkEurope",
	EndCall = "BlinkEurope",
},

LoadMidEurope = {
	Prototype = Action,
	Name = "LoadMidEurope",
	Procedure = DFA_NONE,
	Length = 9,
	Delay = 4,
	X = 0,
	Y = 80,
	Wdt = 60,
	Hgt = 40,
	NextAction = "MidEurope",
},

MidEurope = {
	Prototype = Action,
	Name = "MidEurope",
	Procedure = DFA_NONE,
	Length = 1,
	Delay = 20,
	X = 480,
	Y = 80,
	Wdt = 60,
	Hgt = 40,
	NextAction = "MidEurope",
	EndCall = "Credits",
},

Matthi = {
	Prototype = Action,
	Name = "Matthi",
	Procedure = DFA_NONE,
	Length = 1,
	Delay = 100,
	X = 0,
	Y = 120,
	Wdt = 60,
	Hgt = 40,
	NextAction = "MidEurope",
},

Newton = {
	Prototype = Action,
	Name = "Newton",
	Procedure = DFA_NONE,
	Length = 1,
	Delay = 100,
	X = 60,
	Y = 120,
	Wdt = 60,
	Hgt = 40,
	NextAction = "MidEurope",
},

Boni = {
	Prototype = Action,
	Name = "Boni",
	Procedure = DFA_NONE,
	Length = 1,
	Delay = 100,
	X = 120,
	Y = 120,
	Wdt = 60,
	Hgt = 40,
	NextAction = "MidEurope",
},

Clonko = {
	Prototype = Action,
	Name = "Clonko",
	Procedure = DFA_NONE,
	Length = 1,
	Delay = 100,
	X = 180,
	Y = 120,
	Wdt = 60,
	Hgt = 40,
	NextAction = "MidEurope",
},

Raven = {
	Prototype = Action,
	Name = "Raven",
	Procedure = DFA_NONE,
	Length = 1,
	Delay = 100,
	X = 240,
	Y = 120,
	Wdt = 60,
	Hgt = 40,
	NextAction = "MidEurope",
},

};
