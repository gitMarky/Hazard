
func Initialize()
{
	SetAction("Off");
	SetName("Commander");
	AddFrame();
}


func GetPortrait()
{
	return {Source = Local_Characters, Name = Format("PortraitCommander")};
}


local ActMap = {

Off = {
	Prototype = Action,
	Name = "Off",
	Delay=1,
	Length=1,
	X = 0,
	Y = 0,
	Wdt = 64,
	Hgt = 64,
	NextAction = "Off"
},

Noise = {
	Prototype = Action,
	Name = "Noise",
	Delay=2,
	Length=3,
	X = 64,
	Y = 0,
	Wdt = 64,
	Hgt = 64,
	NextAction = "Noise"
},

On = {
	Prototype = Action,
	Name = "On",
	Delay = 1,
	Length = 1,
	X = 256,
	Y = 0,
	Wdt = 64,
	Hgt = 64,
	NextAction = "On"
},
};
