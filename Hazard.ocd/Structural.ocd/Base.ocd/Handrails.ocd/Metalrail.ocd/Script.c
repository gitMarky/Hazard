#include Rail_Basic

/* Status */

func Index(int index)
{
	if (index == 0)      return "End1";
	else if (index == 1) return "Linkage1";
	else if (index == 2) return "Linkage2";
	else if (index == 3) return "Backing";
	else if (index == 4) return "End2";
	else FatalError(Format("Unknown index %d", index));
}

func Left() {        return 0;}
func Right(){        return 4;}
func Linkage(int i){ return 1 + (!!i);}
func Backing(){      return 3;}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
End1 = {
	Prototype = Action,
	Name = "End1",
	X = 0,
	Y = 0,
	Wdt = 4,
	Hgt = 12,
},

Linkage1 = {
	Prototype = Action,
	Name = "Linkage1",
	X = 4,
	Y = 0,
	Wdt = 18,
	Hgt = 12,
},

Linkage2 = {
	Prototype = Action,
	Name = "Linkage2",
	X = 24,
	Y = 0,
	Wdt = 18,
	Hgt = 12,
},

Backing = {
	Prototype = Action,
	Name = "Backing",
	X = 22,
	Y = 0,
	Wdt = 2,
	Hgt = 12,
},

End2 = {
	Prototype = Action,
	Name = "End2",
	X = 22,
	Y = 0,
	Wdt = 4,
	Hgt = 12,
},

};
