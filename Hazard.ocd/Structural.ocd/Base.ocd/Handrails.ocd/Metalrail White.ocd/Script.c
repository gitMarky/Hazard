#include Rail_Basic

/* Status */

func Index(int index)
{
	if (index == 0)      return "End1";
	else if (index == 1) return "Linkage";
	else if (index == 2) return "Backing";
	else if (index == 3) return "End2";
	else FatalError(Format("Unknown index %d", index));
}

func Left() {        return 0;}
func Right(){        return 3;}
func Linkage(int i){ return 1;}
func Backing(){      return 2;}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
End1 = {
	Prototype = Action,
	Name = "End1",
	X = 0,
	Y = 0,
	Wdt = 11,
	Hgt = 12,
},

Linkage = {
	Prototype = Action,
	Name = "Linkage",
	X = 11,
	Y = 0,
	Wdt = 17,
	Hgt = 12,
},

Backing = {
	Prototype = Action,
	Name = "Backing",
	X = 9,
	Y = 0,
	Wdt = 2,
	Hgt = 12,
},

End2 = {
	Prototype = Action,
	Name = "End2",
	X = 27,
	Y = 0,
	Wdt = 11,
	Hgt = 12,
},

};
