#include Rail_Basic

/* Status */

func Index(int index)
{
	if (index == 0)      return "End1";
	else if (index == 1) return "Linkage";
	else if (index == 2) return "End2";
	else FatalError(Format("Unknown index %d", index));
}

func Left() {        return 0;}
func Right(){        return 2;}
func Linkage(int i){ return 1;}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
End1 = {
	Prototype = Action,
	Name = "End1",
	X = 0,
	Y = 0,
	Wdt = 8,
	Hgt = 14,
},

Linkage = {
	Prototype = Action,
	Name = "Linkage",
	X = 8,
	Y = 0,
	Wdt = 14,
	Hgt = 14,
},

End2 = {
	Prototype = Action,
	Name = "End2",
	X = 22,
	Y = 0,
	Wdt = 8,
	Hgt = 14,
},

};
