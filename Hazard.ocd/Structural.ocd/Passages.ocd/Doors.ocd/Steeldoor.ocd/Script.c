#include Library_HazardDoor

public func Initialize()
{
	SetAction("Close");
	_inherited(...);
	SetMaxDamage(80);
}

/* TODO: damage system*/
/*
public func OnDmg(int iDmg, int iType) {

	// this door is not especially strong
	if(iType == DMG_Projectile)	return(50);
	if(iType == DMG_Melee)	return(20);
	if(iType == DMG_Energy)	return(40);
	if(iType == DMG_Explosion)	return(0);

	return(100);
}
*/

public func OnOpen()
{
	if (GetAction() == "Open") return;

	SetAction("Open");
	SetSolidMask(0);
	Sound("Structural::Passages::SteeldoorOpen");
}

public func OnClose()
{
	if (GetAction() == "Close") return;  
	SetAction("Close");
	SetSolidMask(12, 0, 10, 30, 12, 0);
	Sound("Structural::Passages::SteeldoorClose");
}

public func OnDestroyed(int damage_type)
{
	SetAction("Destroyed");
}

/* Serialisierung

TODO

public func Serialize(array& extra)
{
	if (destroyed)
		extra[GetLength(extra)] = "SetAction(\"Destroyed\")";
}
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Open = {
	Prototype = Action,
	Name = "Open",
	Procedure = DFA_NONE,
	Length = 10,
	Delay = 1,
	X = 0,
	Y = 0,
	Wdt = 34,
	Hgt = 30,
	FacetTopFace = 1,
	NextAction = "Hold",
},

Close = {
	Prototype = Action,
	Name = "Close",
	Procedure = DFA_NONE,
	Length = 10,
	Reverse = 1,
	Delay = 1,
	X = 0,
	Y = 0,
	Wdt = 34,
	Hgt = 30,
	FacetTopFace = 1,
	NextAction = "Hold",
},

Destroyed = {
	Prototype = Action,
	Name = "Destroyed",
	Procedure = DFA_NONE,
	Length = 1,
	X = 319,
	Y = 0,
	Wdt = 9,
	Hgt = 30,
	OffX = 13,
	OffY = 0,
	NextAction = "Hold",
	NoOtherAction = 1,
	ObjectDisabled = 1,
},

};
