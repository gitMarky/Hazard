local damaged;

func Initialize()
{
	SetColor(RGB(100, 255, 100));
}

func Incineration()
{
	if (!damaged)
	{
		damaged = true;

		for (var i = 0; i < 7; i++)
		{
			var dummy = CreateObject(Dummy, RandomX(-80, 80), RandomX(-20, 20), -1);
			ScheduleCall(dummy, dummy.Explode, RandomX(15, 50), 0, RandomX(20, 40));
		}

		InstaExplode();
	}
}

func InstaExplode()
{
	var particles = {Prototype = Particles_WoodChip(), Size = PV_Random(6, 12), R = 200, G = 200, B = 200, DampingX = 1000, DampingY = 1000,};

	var x = PV_Random(GetX()- 3, GetX() + 3);
	var y = PV_Random(GetY()- 3, GetY() + 3);

	var vx = PV_Random(-30, 30);
	var vy = PV_Random(-30, 0);
	
	var lifetime = PV_Random(36 * 3, 36 * 10);

	// cast debris
	Global->CreateParticle("Splinter", x, y, vx, vy, lifetime, particles, RandomX(15, 30));	

	// explosion	
	CreateTemporaryLight(0, 0)->LightRangeStart(120)->SetLifetime(20)->Color(RGB(255, 255, 200))->Activate();
	CreateSparksEffect(7 + Random(5), RGBa(255, 255, 150, 155));
	Explode(50);
}

func IsCraneGrabable(){ return true;}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 50;
