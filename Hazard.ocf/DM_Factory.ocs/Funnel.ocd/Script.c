local reek_size = 100;

func SetSize(int size)
{
	reek_size = size;
	ScheduleCall(this, this.Reek, 2);	
	return this;
}

func Reek()
{	
	var dirrand = RandomX(-reek_size / 15, reek_size / 15);
	var xdir = +Sin(GetR() + dirrand, reek_size / 10);
	var ydir = -Cos(GetR() + dirrand, reek_size / 10);

	CreateParticle("Thrust", 0, 0, xdir, ydir, PV_Random(20, 60),
	{
		Prototype = Particles_ThrustColored(255, 200, 200),
		Size = PV_Random(reek_size * 4 / 50, reek_size / 10),
		OnCollision = PC_Stop(),
	}, 1);

	if (FrameCounter() % 10 == 0) Smoke(0, -10 - (15 * reek_size / 100), reek_size / 5);
	ScheduleCall(this, this.Reek, 2);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
