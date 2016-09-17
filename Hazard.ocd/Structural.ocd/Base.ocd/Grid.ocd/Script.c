/* Ventilation grid */


protected func Initialize()
{
	SetAction("Grid");
}

protected func Damage()
{
	if (GetAction() == "Put") return;
	if (GetDamage() < 30) return;
	
	// Crack open
	while (Contents()) Contents()->Exit();
	Sound("CrateCrack");
	Sound("Blast2");
	SetAction("Put");
}

// TODO: proper implementation
//public func SaveScenarioObject(array& extra)
//{
//	if (GetAction() == "Put")
//		extra[GetLength(extra)] = "SetAction(\"Put\")";
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Grid = {
	Prototype = Action,
	Name = "Grid",
	Procedure = DFA_NONE,
	Delay = 100,
	X = 0,
	Y = 0,
	Wdt = 40,
	Hgt = 40,
	OffX = 0,
	OffY = 0,
	FacetBase = 0,
	NextAction = "Grid",
},

Put = {
	Prototype = Action,
	Name = "Put",
	Procedure = DFA_NONE,
	Delay = 100,
	X = 0,
	Y = 40,
	Wdt = 40,
	Hgt = 40,
	OffX = 0,
	OffY = 0,
	NextAction = "Put",
},

};
