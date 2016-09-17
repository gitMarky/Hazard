#include Library_Lamp

public func GetLampRange() { return 80; }
public func GetLampFadeRange() { return 60; }
public func GetLampColor() { return lib_lamp_color;}

local lib_lamp_color;

func Initialize()
{
	_inherited(...);
	SetGraphics("Light", GetID(), 1, GFXOV_MODE_ExtraGraphics, nil, nil);
	ChangeColor(RGB(255, 0, 0));
	AddEffect("IntAlert", this, 1, 2, this);
}


func ChangeColor(int color)
{
	lib_lamp_color = color;
	SetLightColor(color);
	return this;
}

func TurnOn()
{
	lib_lamp_lit = true;
}

func TurnOff()
{
	lib_lamp_lit = false;
}

func FxIntAlertTimer(object lamp, proplist fx, int timer)
{
	var phase = 0;
	if (lib_lamp_lit) phase = timer;
	Alerting(phase);
}

func Alerting(int timer)
{
	var len = 32;
	var phase = timer % len;
	
	var precision = 1000;
	var percent = Sin(phase * 180 / len, precision);

	SetClrModulation(SetRGBaValue(GetLampColor(), 55 + percent / 5, RGBA_ALPHA), 1);
	SetLightRange(percent * GetLampRange() / precision, GetLampFadeRange());
}
