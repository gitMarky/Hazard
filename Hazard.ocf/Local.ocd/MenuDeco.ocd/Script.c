/*-- Deco --*/


protected func FrameDecorationBackClr(){ return RGBa(50, 50, 50, 128);}

protected func SolidBackClr(){ return RGBa(10, 10, 10, 128);}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
FrameDecoTopLeft = {
	Prototype = Action,
	Name = "FrameDecoTopLeft",
	X = 1,
	Y = 2,
	Wdt = 10,
	Hgt = 24,
	OffX = -5,
	OffY = -10,
},

FrameDecoTop = {
	Prototype = Action,
	Name = "FrameDecoTop",
	X = 11,
	Y = 2,
	Wdt = 79,
	Hgt = 9,
	OffX = 0,
	OffY = -9,
},

FrameDecoTopRight = {
	Prototype = Action,
	Name = "FrameDecoTopRight",
	X = 90,
	Y = 2,
	Wdt = 9,
	Hgt = 24,
	OffX = 0,
	OffY = -10,
},

FrameDecoRight = {
	Prototype = Action,
	Name = "FrameDecoRight",
	X = 90,
	Y = 25,
	Wdt = 9,
	Hgt = 50,
	OffX = 0,
	OffY = 0,
},

FrameDecoBottomRight = {
	Prototype = Action,
	Name = "FrameDecoBottomRight",
	X = 90,
	Y = 75,
	Wdt = 9,
	Hgt = 24,
	OffX = 0,
	OffY = -15,
},

FrameDecoBottom = {
	Prototype = Action,
	Name = "FrameDecoBottom",
	X = 11,
	Y = 90,
	Wdt = 79,
	Hgt = 9,
	OffX = 0,
	OffY = 0,
},

FrameDecoBottomLeft = {
	Prototype = Action,
	Name = "FrameDecoBottomLeft",
	X = 1,
	Y = 75,
	Wdt = 10,
	Hgt = 24,
	OffX = -5,
	OffY = -15,
},

FrameDecoLeft = {
	Prototype = Action,
	Name = "FrameDecoLeft",
	X = 1,
	Y = 25,
	Wdt = 10,
	Hgt = 50,
	OffX = -5,
	OffY = 0,
},

FrameDecoWall = {
	Prototype = Action,
	Name = "FrameDecoWall",
	X = 10,
	Y = 10,
	Wdt = 80,
	Hgt = 80,
},

};
