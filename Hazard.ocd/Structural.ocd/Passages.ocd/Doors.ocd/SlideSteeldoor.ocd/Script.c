#include Library_HazardDoor

local pathfree;


func Initialize()
{
	pathfree = false;
	SetAction("Closed");
	_inherited(...);
	SetMaxDamage(300);
}

/* TODO: damage system*/
/*
func OnDmg(int iDmg, int iType)
{
	// this door is not especially strong
	if (iType == DMG_Projectile)
		return 60;
	if (iType == DMG_Melee)
		return 80;
	if (iType == DMG_Energy)
		return 30;
	if (iType == DMG_Explosion)
		return 0;
	return 100;
}
*/

func OnOpen()
{
	if (GetAction() == "Open" || GetAction() == "Opened") return;

	SetAction("Open");
	Sound("Structural::Passages::SlideSteeldoorOpen");
}

func OnClose()
{
	if (GetAction() == "Closed" || GetAction() == "Close") return;

	SetAction("Close");
	Sound("Structural::Passages::SlideSteeldoorClose");
	SetSolidMask(140, 0, 4, 30, 7, 0);
}

func SetPathFree()
{
	pathfree = true;
	SetSolidMask();
}

func OnDestroyed(int type)
{
	CreateObject(Dummy, 0, 0, NO_OWNER)->Explode(20);
	SetAction("Destroyed");
}

/* Serialisierung */

func Serialize(array extra) // TODO save object properly
{
//	_inherited(extra);
//	if (destroyed)
//		extra[GetLength(extra)] = "SetAction(\"Destroyed\")";
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
	X = 120,
	Y = 0,
	Wdt = 12,
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
	Length = 9,
	Delay = 2,
	X = 0,
	Y = 0,
	Wdt = 12,
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
	X = 108,
	Y = 0,
	Wdt = 12,
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
	Length = 9,
	Reverse = 1,
	Delay = 2,
	X = 0,
	Y = 0,
	Wdt = 12,
	Hgt = 30,
	FacetTopFace = 1,
	NextAction = "Closed",
},

Destroyed = {
	Prototype = Action,
	Name = "Destroyed",
	Procedure = DFA_NONE,
	Directions = 1,
	FlipDir = 1,
	Length = 1,
	X = 132,
	Y = 0,
	Wdt = 12,
	Hgt = 30,
	FacetTopFace = 1,
	NextAction = "Hold",
	NoOtherAction = 1,
	ObjectDisabled = 1,
},

};
