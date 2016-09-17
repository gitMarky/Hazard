#include Library_Lamp

public func GetLampRange() { return 80; }
public func GetLampFadeRange() { return 60; }
public func GetLampColor() { return LIGHT_COLOR_NEON; }

func TurnOn()
{
	if (EMPShocked()) return;
	if (_inherited(...)) SetAction("On");
}

func TurnOff()
{
	if (_inherited(...)) if (!SetAction("Off")) SetAction("Idle");
}

func Switch()
{
	if (GetAction() == "On")
	{
		TurnOff();
	}
	else
	{
		TurnOn();
	}
}

func IsMachine()
{
	return true;
}

func EMPShock()
{
	TurnOff();
	EMPShockEffect(800 + Random(200));
}

func EMPShockEnd()
{
	if (lib_lamp_lit) TurnOn();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions and properties

local ActMap = {
On = {
	Prototype = Action,
	Name = "On",
	Delay = 1,
	X = 0,
	Y = 15,
	Wdt = 20,
	Hgt = 15,
	NextAction = "Hold",
},

};
