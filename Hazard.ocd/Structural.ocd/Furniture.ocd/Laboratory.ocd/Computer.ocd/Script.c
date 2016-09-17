func Initialize()
{
	SetAction("Blink");
	Spark();
}

func Spark()
{
	if (!Random(4))
	{
		Laser(-13, -20, 14, RandomX(-28, -15));
	}
	if (!Random(4))
	{
		Laser(14, -28, -13, RandomX(-20, -7));
	}
	ScheduleCall(this, this.Spark, 36);
}

func Laser(int x1, int y1, int x2, int y2)
{
	var laser = CreateObject(LaserEffect, x1, y1, NO_OWNER);

	laser->Line(GetX() + x1, GetY() + y1, GetX() + x2, GetY() + y2)
		 ->SetWidth(9)
		 ->SetLifetime(RandomX(10, 18))
		 ->Color(RGB(114, 194, 255))
		 ->Activate();
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
Blink = {
	Prototype = Action,
	Name = "Blink",
	Procedure = DFA_NONE,
	Directions = 2,
	FlipDir = 1,
	Length = 4,
	Delay = 10,
	X = 0,
	Y = 0,
	Wdt = 50,
	Hgt = 55,
	NextAction = "Blink2",
},

Blink2 = {
	Prototype = Action,
	Name = "Blink2",
	Procedure = DFA_NONE,
	Directions = 2,
	FlipDir = 1,
	Length = 2,
	Reverse = 1,
	Delay = 10,
	X = 50,
	Y = 0,
	Wdt = 50,
	Hgt = 55,
	NextAction = "Blink",
},

};
