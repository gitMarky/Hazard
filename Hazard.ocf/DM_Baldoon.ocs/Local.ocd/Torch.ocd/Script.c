func Initialize()
{
	CreateEffect(IntBurning, 100, 1);
}

local IntBurning = new Effect
{
	Start = func (int temp)
	{
		if (temp) return;
		// Set the light range for this torch.
		Target->SetLightRange(80, 60);
		Target->SetLightColor(FIRE_LIGHT_COLOR);
	},
	
	Timer = func ()
	{
		Target->CreateParticle("FireSharp", PV_Random(-2, +2), -21, 0, PV_Random(-8, -14), PV_Random(10, 15), Particles_Fire(), 1);
		Target->CreateParticle("Fire", PV_Random(-2, +2), -21, PV_Random(-2, +2), PV_Random(-6, -12), PV_Random(10, 3), 
		{
			Prototype = Particles_Fire(),
			Size = PV_KeyFrames(0, 0, PV_Random(4, 6), 500, 5, 1000, 0),
			R = 255, G = PV_Random(224, 255), B = 0,
		}
		, 1);
	},
	
	Stop = func()
	{
		Target->SetLightRange(0);
	},
};
