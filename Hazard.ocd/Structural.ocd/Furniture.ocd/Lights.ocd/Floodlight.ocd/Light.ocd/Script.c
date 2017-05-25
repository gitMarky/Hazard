#include Library_Lamp

public func GetLampRange() { return 770;}
public func GetLampFadeRange() { return 20;}
public func GetLampColor() { return LIGHT_COLOR_LAMP;}

func TurnOn() // TODO: no idea why, but overloading did not work properly
{
	if (EMPShocked()) return;
	if (lib_lamp_lit) return false;
	TurnLightOn();
	lib_lamp_lit = true;
	return true;
}

func TurnOff()
{
	if (!lib_lamp_lit) return false;
	TurnLightOff();
	lib_lamp_lit = false;
	return true;
}

func Switch()
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

func IsMachine()
{
	return true;
}

func EMPShock()
{
	EMPShockEffect(800 + Random(200));
	return TurnOff();
}

func EMPShockEnd()
{
	if (lib_lamp_lit) TurnOn();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// floodlight suff

local turn;

func ConnectTo(object flood_light)
{
	SetAction("Attach", flood_light);
}

func TurnLightOn()
{
	AddLightCone(this->GetLampRange(), GetR(), this->GetLampFadeRange(), this->GetLampColor());
	RotateLight();
}

func TurnLightOff()
{
	RemoveLightCone();
}

func Turning()
{
	if (EMPShocked()) return;
	var anglediff = Normalize(GetR() - GetActionTarget()->GetR(), -180);

	if (turn == -1 && anglediff < -90 || turn == +1 && anglediff > 90)
		return SetAction("Attach", GetActionTarget());
	
	SetR(GetR() + turn);
	RotateLight();
}

func RotateLight() // TODO
{
	var cone = GetLightCone();
	if (cone)
	{
		cone.angle = GetR();
		DrawLightCone(cone);
	}
}

func TurnLeft()
{
	if (EMPShocked()) return;
	turn = -1;
	SetAction("Turn");
}

func TurnRight()
{
	if (EMPShocked()) return;
	turn = +1;
	SetAction("Turn");
}

func Stop()
{
	turn = 0;
	SetAction("Attach");
	//Sound("CannonStop");
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Attach = {
	Prototype = Action,
	Name = "Attach",
	Procedure = DFA_ATTACH,
	Delay = 1,
	FacetBase = 1,
	NextAction = "Attach",
},

Turn = {
	Prototype = Action,
	Name = "Turn",
	Procedure = DFA_ATTACH,
	Delay = 5,
	FacetBase = 1,
	NextAction = "Turn",
	EndCall = "Turning",
},

};
