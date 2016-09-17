func Initialize()
{
	WaterCast();
}

func WaterCast()
{
	CastPXS("Water", 2, 5, 0, 0);
	ScheduleCall(this, this.WaterCast, 4, 1);
}
