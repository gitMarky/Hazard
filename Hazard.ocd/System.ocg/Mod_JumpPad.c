#appendto Arena_JumpPad

local emp_state;

func IsMachine()
{
	return true;
}

func OnBounced(object target)
{
	target->Sound("Structural::Jumppad");
}


func EMPShock()
{
	EMPShockEffect(38 * 3);
}

func EMPShockStart()
{
	emp_state = is_active;
	Deactivate();
}

func EMPShockEnd()
{
	if (emp_state)
	{
		Activate();
	}
}
