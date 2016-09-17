
protected func Initialize()
{
	SetAction("Radar");
}

protected func IsFakeRadar()
{
    return GameCallEx("FakeRadars");
}

local ActMap = {
	Radar = {
	Prototype = Action,
	Name = "Radar",
	Delay = 4,
	Length = 20,
	X = 0,
	Y = 0,
	Wdt = 46,
	Hgt = 50,
	NextAction = "Radar",
	},
};

local Name = "$Name$";
local Description = "$Description$";
