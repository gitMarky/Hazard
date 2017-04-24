#include Keypad

func CorrectCodeEffect()
{
	CreateLEDEffect(RGB(0, 255, 0), 5, 1, nil, 50);
}

func WrongCodeEffect()
{
	CreateLEDEffect(RGB(255, 0, 0), 5, 1, nil, 50);
}

// overloaded

public func OpenDoor(object user)
{
	if (target_door) target_door->~Access();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
