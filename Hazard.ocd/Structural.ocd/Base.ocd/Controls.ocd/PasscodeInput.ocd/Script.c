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

public func SetSwitchState(bool state, object by_user)
{
	if (GetSwitchTarget())
	{
		// Invert the state?
		var actual_state = state != lib_switch.invert_signal;
		// Forward to the target
		if (actual_state)
		{
			GetSwitchTarget()->~Access();
		}
		// was: GetSwitchTarget()->SetInputSignal(by_user, this, actual_state);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
