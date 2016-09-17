#include Library_HazardDoor

local pathfree;

func Initialize()
{
	_inherited(...);
	pathfree = false;
	SetAction("Closed");
	// not destroyable
	SetMaxDamage(-1);
}

func OnOpen()
{
	if (GetAction() == "Open" || GetAction() == "Opened") return;
	SetAction("Open");
	Sound("Structural::Passages::SequiumDoorOpen");
}

func OnClose()
{
	if (GetAction() == "Closed" || GetAction() == "Close") return;
	SetAction("Close");
	SetSolidMask(5, 0, 8, 30, 5, 0);
	Sound("Structural::Passages::SequiumDoorClose");
}

func SetPathFree()
{
	pathfree = true;
	SetSolidMask();
}


func Serialize(array extra) // TODO
{
//	_inherited(extra);
//	if (pathfree)
//		extra[GetLength(extra)] = "SetPathFree()";
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
Closed = {
	Prototype = Action,
	Name = "Closed",
	Procedure = DFA_NONE,
	Directions = 1,
	FlipDir = 0,
	Length = 1,
	X = 0,
	Y = 0,
	Wdt = 20,
	Hgt = 30,
	FacetTopFace = 1,
	NextAction = "Hold",
},

Open = {
	Prototype = Action,
	Name = "Open",
	Procedure = DFA_NONE,
	Directions = 1,
	FlipDir = 0,
	Length = 10,
	Delay = 2,
	X = 0,
	Y = 0,
	Wdt = 20,
	Hgt = 30,
	FacetTopFace = 1,
	NextAction = "Opened",
	EndCall = "SetPathFree",
},

Opened = {
	Prototype = Action,
	Name = "Opened",
	Procedure = DFA_NONE,
	Directions = 1,
	FlipDir = 0,
	Length = 1,
	X = 180,
	Y = 0,
	Wdt = 20,
	Hgt = 30,
	FacetTopFace = 1,
	NextAction = "Hold",
},

Close = {
	Prototype = Action,
	Name = "Close",
	Procedure = DFA_NONE,
	Directions = 1,
	FlipDir = 0,
	Length = 10,
	Reverse = 1,
	Delay = 2,
	X = 0,
	Y = 0,
	Wdt = 20,
	Hgt = 30,
	FacetTopFace = 1,
	NextAction = "Closed",
},

};
