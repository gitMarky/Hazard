#include Library_Lamp

public func GetLampRange() { return 50;}
public func GetLampFadeRange() { return 20;}
public func GetLampColor() { return LIGHT_COLOR_LAMP;}

local light;

func Initialize()
{
	_inherited(...);
	
	SetObjDrawTransform(1000 * (-1 + 2 * Random(2)), 0, 0, 0, 1000);

	light = CreateObject(Dummy, 0, -11, NO_OWNER);
	light.Visibility = VIS_All;
	TurnOff();
}

func TurnLightOn()
{
	light->AddLightCone(this->GetLampRange(), 180, this->GetLampFadeRange(), this->GetLampColor());
}

func TurnLightOff()
{
	light->RemoveLightCone();
}

func Destruction()
{
	if (light) light->RemoveObject();
	_inherited(...);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

