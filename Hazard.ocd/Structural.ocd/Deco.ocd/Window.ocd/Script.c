
func Initialize()
{
	SetAction("Window1");
	SetDir(0);
}

func SetDir(int dir)
{
	SetSolidMask(70, 91 * dir, 70, 91, 0, 0);
	return _inherited(dir);
}

local ActMap = 
{
	Window1 =
	{
		Prototype = Action,
		Name = "Window1",
		Procedure = DFA_NONE,
		Directions = 2,
		FlipDir = 1,
		FacetBase = 1
	}
};

local Name = "$Name$";
local Description = "$Description$";
