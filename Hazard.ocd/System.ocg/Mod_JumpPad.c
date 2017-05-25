#appendto Arena_JumpPad

local emp_state;

func IsMachine()
{
	return true;
}


func OnBounce(object target)
{
	target->Sound("Structural::Jumppad");
}


func EMPShock()
{
	if (EMPShocked())
	{
		return false;
	}
	else
	{
		EMPShockEffect(38 * 3);
		return true;
	}
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
