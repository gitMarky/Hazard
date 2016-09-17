
local damaged;

func Damage()
{
	// it explodes easily
	if (GetDamage() > 20) DoExplode(Random(3));
}

func DoExplode(int type)
{
	if (damaged) return;
	damaged = true;

	// 1 - many explosions!
	if (type == 0)
	{
		// cast several small bombs
		for (var i = 0; i < 4; i++)
		{
			var dummy = CreateObject(Dummy, RandomX(-40, 40), RandomX(-30, 30), -1);
			ScheduleCall(dummy, dummy.Explode, RandomX(5, 20), 0, RandomX(15, 35));
		}
		// explode yourself
		InstaExplode();
		RemoveObject();
	}
	// 2 - explosion + fling around
	else if (type == 1)
	{
		InstaExplode();
		SetSpeed(RandomX(-25, 25), RandomX(-55, -30));
		SetRDir(RandomX(-10, 10));
		if (!GetRDir()) SetRDir(2);
		SetClrModulation(RGB(50, 50, 50));
	}
	// 3 - fly like a rocket!
	else
	{
		CreateObject(Dummy)->Explode(20 + Random(10));
		Incinerate();
		Sound("Fire::Inflame");
		Sound("Fire::Fire", 0, 0, 0, 1);
		SpeedUp();
	}
}

func InstaExplode()
{
	CreateTemporaryLight(0, 0)->LightRangeStart(60)->SetLifetime(5)->Color(RGBa(255, 255, 200))->Activate();
	CreateSparksEffect(RandomX(7, 12), RGBa(255, 255, 150, 155));
	CreateObject(Dummy)->Explode(RandomX(25, 45));
}

func SpeedUp(int time)
{
	// stop?
	if (time > 80)
	{
		Sound("Fire::Fire", nil, nil, nil, -1);
		InstaExplode();
		RemoveObject();
		return;
	}
	// up, up and away!
	SetR(GetR() + RandomX(-10, 10));
	var speed = 35;
	var xdir = +Sin(GetR(), speed);
	var ydir = -Cos(GetR(), speed);
	SetSpeed(xdir, ydir);
	Smoke(0, 0, RandomX(5, 15));
	ScheduleCall(this, this.SpeedUp, 1, 0, time + 1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
