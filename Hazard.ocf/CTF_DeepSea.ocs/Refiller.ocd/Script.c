/*-- Refiller --*/


func Initialize()
{
	ScheduleCall(this, this.Check, 35);
}

func Check()
{
	if (InLiquid())
	{
		return ScheduleCall(this, this.Check, 35);
	}
	else
	{
		for (var i = 0; i < 10; i++)
		{
			InsertMaterial(Material("Water"));
		}
		ScheduleCall(this, this.Check, 2);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
