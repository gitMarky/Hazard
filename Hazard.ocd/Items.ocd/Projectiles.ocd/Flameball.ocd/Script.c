#include Projectile_Flame

protected func OnTravelling()
{
	SetYDir(GetYDir(1000) + GetGravity()*3, 1000);
	velocity_y = GetYDir();

	var r, g, b;
	if (slimy)
	{
		r = 160; g = 255; b = 0;
	}
	else
	{
		r = 150; g = 150; b = 150;
	}

 	CreateParticle("SmokeDirty", GetXDir() / 6, GetYDir() / 6, RandomX(-15, 15), RandomX(-5,-20), PV_Random(20, 30),
	{
		Prototype = Particles_ThrustColored(r, g, b),
		Size = PV_Random(25, 32),
		Alpha = PV_Linear(50, 0),
	});
	
	_inherited(...);
}

