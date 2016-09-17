#include BLGH

local lightbulb;


func Initialize()
{
	lightbulb = {
		base = nil,
		length = nil,
		cable = nil,
		phase = nil,
		speed = nil,
		dir = Random(2) * -2 + 1,
		minspeed = 0,
	};

	_inherited(...);
}

func Init(object base, int length)
{
	lightbulb.base = base;
	lightbulb.cable = CreateObject(BLBC);
	lightbulb.cable->Connect(base, this);
	lightbulb.length = length;
	SetPosition(lightbulb.base->GetX(), lightbulb.base->GetY() + length);
	lightbulb.speed = length / 3 * -lightbulb.dir;
	lightbulb.phase = 0;
	
	CreateEffect(CalculatePosition, 1, 1);
}

func SetCableLength(int length)
{
	if (length <= 0) FatalError(Format("Length must be a positiv value. You passed %d", length));
	lightbulb.length = length;
	UpdatePos();
}

func UpdatePos()
{
	var x, y;
	x = Sin(lightbulb.phase / 10, lightbulb.length);
	y = Cos(lightbulb.phase / 10, lightbulb.length);
	SetPosition(lightbulb.base->GetX() + x, lightbulb.base->GetY() + y);
}

local CalculatePosition = new Effect
{
	Timer = func ()
	{
		Target->Adjust();
	},
};

func Adjust()
{
	if (!lightbulb.base)
	{
		lightbulb.cable->RemoveObject();
		RemoveObject();
	}
	if (!lightbulb.dir) return;
	UpdatePos();
	
	lightbulb.phase += lightbulb.speed;
	lightbulb.speed += lightbulb.dir;
	
	if ((lightbulb.speed > 0 && lightbulb.dir < 0) || (lightbulb.speed < 0 && lightbulb.dir > 0))
		if (lightbulb.speed % 5)
			lightbulb.speed += lightbulb.dir;
	

	if (Abs(lightbulb.phase) >= 900)
	{
		lightbulb.speed = 0;
		lightbulb.phase = lightbulb.phase / Abs(lightbulb.phase) * 899;
	}
	
	if ((lightbulb.phase >= 0 && lightbulb.speed >= 0 && lightbulb.dir > 0) || (lightbulb.phase <= 0 && lightbulb.speed <= 0 && lightbulb.dir < 0))
	{
		lightbulb.dir *= -1;
		if (Abs(lightbulb.speed) < 15)
		{
			lightbulb.speed += lightbulb.dir;
			lightbulb.phase += lightbulb.dir;
			if (Abs(lightbulb.speed) < 7 && Abs(lightbulb.phase) < 5)
			{
				lightbulb.dir = 0;
				lightbulb.speed = 0;
				lightbulb.speed = 0;
			}
		}
	}
	
	SetR(Angle(GetX(), GetY(), lightbulb.base->GetX(), lightbulb.base->GetY()));
	lightbulb.cable->Update();
}

func IsProjectileTarget(object projectile, object shooter)
{
	if (!projectile) return false;
	var type = projectile->GetID();
	if (type != Projectile_Bullet) return false; 
	
	lightbulb.speed += projectile->GetXDir();
	lightbulb.speed = BoundBy(lightbulb.speed, -55, 55);
	lightbulb.dir = BoundBy(-lightbulb.speed, -1, 1);
	return true;
}


func GetLampRange() { return 40; }
func GetLampFadeRange() { return 40; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Off = {
	Prototype = Action,
	Name = "Off",
	Procedure = DFA_FLOAT,
	Delay = 0,
	X = 0,
	Y = 0,
	Wdt = 6,
	Hgt = 10,
	NextAction = "Hold",
},

On = {
	Prototype = Action,
	Name = "On",
	Procedure = DFA_FLOAT,
	Delay = 0,
	X = 6,
	Y = 0,
	Wdt = 6,
	Hgt = 10,
	NextAction = "Hold",
},

};
