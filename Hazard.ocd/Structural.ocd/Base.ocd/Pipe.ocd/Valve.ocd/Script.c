/*-- Valve --*/


local open;

func Initialize()
{
	open = false;
	SetAction("Exist");
}

func ControlDig()
{
	open = !open;
	UpdatePipesystem();
}

func Status()
{
	return open;
}

/* Serialisierung */

func Serialize(array extra)
{
	if (open)
		extra[GetLength(extra)] = "ControlDig()";
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
Exist = {
	Prototype = Action,
	Name = "Exist",
	Procedure = DFA_FLOAT,
	Delay = 1,
	FacetBase = 1,
	NextAction = "Exist",
},

};
