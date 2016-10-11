#appendto Cloud

func Initialize()
{
	_inherited(...);
	rain = 960;
	mode = CLOUD_ModeRaining;
}

// Instant full evaporation
func Evaporation() 
{
	rain = 960;
	mode_time = 0;
}

func MoveCloud()
{
	// stay in place
}

func RainDrop()
{
	_inherited(...);
	return false; // this way the cloud will rain forever
}

// modded to not insert new water
private func DropHit(string material_name, int color, int x_orig, int y_orig)
{
	// Adjust position so that it's in the air.
	var x = AbsX(x_orig), y = AbsY(y_orig);
	while (GBackSemiSolid(x, y - 1)) y--;

	if(GBackLiquid(x,y))
	{
		particle_cache.splash_water = particle_cache.splash_water ?? Particles_SplashWater(color);
		CreateParticle("RaindropSplashLiquid", x, y - 3, 0, 0, 20, particle_cache.splash_water);
	}
	// Solid? normal splash!
	else
	{
		CreateParticle("RaindropSplash", x, y-1, 0, 0, 5, Particles_Splash(color), 0);

		particle_cache.small_rain = particle_cache.small_rain ?? Particles_RainSmall(color);
		CreateParticle("RaindropSmall", x, y, RandomX(-4, 4), -Random(10), PV_Random(300, 300), particle_cache.small_rain, 0);
	}
}
