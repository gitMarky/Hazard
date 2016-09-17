#include WNDW

func SetDir(int dir)
{
	SetSolidMask(70, 47 * dir, 70, 47, 0, 0);
	return _inherited(dir);
}

local ActMap = {
Window1 = {
	Prototype = Action,
	Name = "Window1",
	Procedure = DFA_NONE,
	Directions = 2,
	FlipDir = 1,
	FacetBase = 1,
},
};
