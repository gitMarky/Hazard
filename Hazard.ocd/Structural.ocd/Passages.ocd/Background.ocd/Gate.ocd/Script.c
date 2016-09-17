//TODO: #include DOOR

func SoundOpenDoor()
{
	Sound("Structural::Passages::Airlock1");
}

func SoundCloseDoor()
{
	Sound("Structural::Passages::Airlock2");
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
OpenDoor = {
	Prototype = Action,
	Name = "OpenDoor",
	Length = 10,
	Delay = 1,
	X = 0,
	Y = 0,
	Wdt = 20,
	Hgt = 23,
	NextAction = "DoorOpen",
	StartCall = "SoundOpenDoor",
},

CloseDoor = {
	Prototype = Action,
	Name = "CloseDoor",
	Length = 10,
	Reverse = 1,
	Delay = 1,
	X = 0,
	Y = 0,
	Wdt = 20,
	Hgt = 23,
	NextAction = "Idle",
	StartCall = "SoundCloseDoor",
},

DoorOpen = {
	Prototype = Action,
	Name = "DoorOpen",
	Length = 1,
	Delay = 18,
	X = 180,
	Y = 0,
	Wdt = 20,
	Hgt = 23,
	NextAction = "CloseDoor",
	StartCall = "OpenEntrance",
	EndCall = "CloseEntrance",
},

};
