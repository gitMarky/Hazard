#include Library_HazardDoor

local bBackground;


func Initialize()
{
	SetDir(DIR_Right);
	SetAction("Close");
	UpdateSolidMask();
	_inherited(...);
	SetMaxDamage(100);
}

/* TODO damage system
public func OnDmg(int iDmg, int iType) 
{
	if(iType == DMG_Projectile) return(40);
	if(iType == DMG_Melee)    	return(20);
	if(iType == DMG_Energy)   	return(70);
	if(iType == DMG_Explosion)  return(-10);

	return(100);
}
*/

func OnOpen()
{
	if (GetAction() == "Open" || bBackground) return;
	
	SetAction("Open");
	SetSolidMask(0);
	Sound("Structural::Passages::LabDoorOpen");
}

func OnClose()
{
	if (GetAction() == "Close" || bBackground) return;
	SetAction("Close");
	UpdateSolidMask();
	Sound("Structural::Passages::LabDoorClose");
}

func OnDestroyed(int damage_type)
{
	SetAction("Destroyed");
}

func ShowFront()
{
	bBackground = true;
	SetAction("FrontSight");
	SetSolidMask();
	return bBackground;
}

func UpdateSolidMask()
{
	if (GetDir() == DIR_Left)
		return SetSolidMask(14, 0, 1, 30, 14, 0);
	else
		return SetSolidMask(14, 0, 1, 30, 1, 0);
}

func IsProjectileTarget()
{
	if (bBackground) return false;
	return _inherited(...);
}

/* Serialisierung

func Serialize(array extra)
{
	_inherited(extra);
	if (destroyed)
		extra[GetLength(extra)] = "SetAction(\"Destroyed\")";
	if (GetDir() == DIR_Left)
	{
		extra[GetLength(extra)] = "SetDir(DIR_Left)";
		extra[GetLength(extra)] = "UpdateSolidMask()";
	}
	if (bBackground)
		extra[GetLength(extra)] = "ShowFront()";
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
	Directions = 2,
	FlipDir = 1,
	Length = 13,
	Delay = 1,
	X = 0,
	Y = 0,
	Wdt = 15,
	Hgt = 30,
	FacetTopFace = 1,
	NextAction = "Hold",
},

Close = {
	Prototype = Action,
	Name = "Close",
	Procedure = DFA_NONE,
	Directions = 2,
	FlipDir = 1,
	Length = 13,
	Reverse = 1,
	Delay = 1,
	X = 0,
	Y = 0,
	Wdt = 15,
	Hgt = 30,
	FacetTopFace = 1,
	NextAction = "Hold",
},

Destroyed = {
	Prototype = Action,
	Name = "Destroyed",
	Procedure = DFA_NONE,
	Directions = 2,
	FlipDir = 1,
	Length = 4,
	Delay = 2,
	X = 107,
	Y = 31,
	Wdt = 15,
	Hgt = 30,
	FacetTopFace = 1,
	NextAction = "Hold",
	NoOtherAction = 1,
	ObjectDisabled = 1,
},

FrontSight = {
	Prototype = Action,
	Name = "FrontSight",
	Procedure = DFA_NONE,
	Directions = 1,
	Length = 1,
	X = 66,
	Y = 30,
	Wdt = 40,
	Hgt = 30,
	OffX = -20,
	OffY = 0,
	FacetTopFace = 1,
	NextAction = "Hold",
},

};
