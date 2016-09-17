#include Library_Lamp

local light;

public func GetLampRange() { return 40;}
public func GetLampFadeRange() { return 60;}
public func GetLampColor() { return RGB(100, 220, 255);}


func ConsoleControl(int i) // TODO
{
	if (i == 1)
	{
		if (lib_lamp_lit)
			return "$TurnOff$";
		else
			return "$TurnOn$";
	}
}

func ConsoleControlled(int i) // TODO
{
	if (i == 1)
	{
		if (lib_lamp_lit)
		{
			TurnOff();
		}
		else
		{
			TurnOn();
		}
	}
}


func IsMachine(){	return true;}
func EMPShock(){	return TurnOff();}

func TurnLightOn()
{
	SetAction("TurnOn");
	_inherited(...);
}

func TurnLightOff()
{
	if (GetAction() != "Idle") SetAction("TurnOff");
	_inherited(...);
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
	Procedure = DFA_NONE,
	Directions = 1,
	Length = 10,
	Delay = 4,
	X = 0,
	Y = 40,
	Wdt = 50,
	Hgt = 40,
	NextAction = "Turn",
},

TurnOn = {
	Prototype = Action,
	Name = "TurnOn",
	Procedure = DFA_NONE,
	Directions = 1,
	Length = 10,
	Delay = 2,
	X = 0,
	Y = 0,
	Wdt = 50,
	Hgt = 40,
	NextAction = "Turn",
},

TurnOff = {
	Prototype = Action,
	Name = "TurnOff",
	Procedure = DFA_NONE,
	Directions = 1,
	Length = 10,
	Reverse = 1,
	Delay = 2,
	X = 0,
	Y = 0,
	Wdt = 50,
	Hgt = 40,
	NextAction = "Hold",
},

};
