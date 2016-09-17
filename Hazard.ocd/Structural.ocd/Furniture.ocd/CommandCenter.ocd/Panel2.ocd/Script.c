
local broken;

func Damage()
{
	if (GetDamage() > 20 && !broken)
	{
		broken = true;
		SetAction("Broken");
		// TODO: Sparkle(20);
		Sound("Structural::Electrify");
		// TODO: Schedule("CastObjects(SPRK, 1, 30);", 100, 10, this);
	}
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
Broken = {
	Prototype = Action,
	Name = "Broken",
	Delay = 1,
	X = 28,
	Y = 0,
	Wdt = 28,
	Hgt = 32,
	NextAction = "Hold",
},

};
