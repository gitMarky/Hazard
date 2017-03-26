#include Library_Lamp

public func GetLampRange() { return 95;}
public func GetLampFadeRange() { return 30;}
public func GetLampColor() { return LIGHT_COLOR_LAMP;}

func Initialize()
{
	_inherited(...);
	Glowing();
}


func TurnLightOn()
{
	AddLightCone(this->GetLampRange(), 180, this->GetLampFadeRange(), this->GetLampColor());
}

func TurnLightOff()
{
	RemoveLightCone();
}

func Glowing()
{
	if (lib_lamp_lit && Random(2)) CreateParticle("Magic", PV_Random(-2, +2), 4, PV_Random(-1, 1), PV_Random(1, 3), 40,
	{
		Prototype = Particles_Magic(),
		BlitMode = GFX_BLIT_Additive,
		R = 100, G = 100, B = 50,
		Size = PV_Random(1, 3),
	});
	
	ScheduleCall(this, this.Glowing, 5, 1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
