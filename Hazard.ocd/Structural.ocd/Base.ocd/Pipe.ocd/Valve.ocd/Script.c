/*-- Valve --*/


local open;

protected func Initialize() {
  open = false;
  SetAction("Exist");
}

protected func ControlDig() {
  open = !open;
  UpdatePipesystem();
}

public func Status() { return(open); }

/* Serialisierung */

public func Serialize(array& extra)
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
