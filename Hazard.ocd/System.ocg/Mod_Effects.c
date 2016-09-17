/*
	Contains functions for (visual) effects that require particles or definitions from Objects.ocd to be loaded.
*/

/*
Creates a visual explosion effect at a position.
smoothness (in percent) determines how round the effect will look like
*/
global func ExplosionEffect(int level, int x, int y, int smoothness, bool silent, int damage_level)
{
	// Zero-size explosion doesn't affect anything
	if (level <= 0) return;
	
	if(!silent) //Does object use it's own explosion sound effect?
	{
		// Select sound according to level: from 1 to 3, add the * to allow alternatives.
		var grade = BoundBy(level / 10 - 1, 1, 3);
		if(GBackLiquid(x, y))
			SoundAt(Format("Fire::BlastLiquid%d*",grade), x, y);
		else
			SoundAt(Format("Fire::Blast%d*", grade), x, y);
	}
	
	// possibly init particle definitions?
	if (!ExplosionParticles_Blast)
		ExplosionParticles_Init();
	
	smoothness = smoothness ?? 0;
	var level_pow = level ** 2;
	var level_pow_fraction = Max(level_pow / 25, 5 * level);
	var wilderness_level = level * (100 - smoothness) / 100;
	var smoothness_level = level * smoothness / 100;
	
	var smoke_size = PV_KeyFrames(0, 180, level, 1000, level * 2);
	var blast_size = PV_KeyFrames(0, 0, 0, 260, level * 2, 1000, level);
	var blast_smooth_size = PV_KeyFrames(0, 0, 0, 250, PV_Random(level, level * 2), 1000, level);
	var star_size = PV_KeyFrames(0, 0, 0, 500, level * 2, 1000, 0);
	var shockwave_size = PV_Linear(0, level * 4);
	
	CreateParticle("Smoke2", PV_Random(x - 10,x + 10), PV_Random(y - 10, y + 10), 0, PV_Random(-2, 0), PV_Random(50, 100), {Prototype = ExplosionParticles_Smoke, Size = smoke_size}, Max(2, wilderness_level / 10));
	CreateParticle("Smoke2", PV_Random(x - 5, x + 5), PV_Random(y - 5, y + 5), PV_Random(-1, 1), PV_Random(-1, 1), PV_Random(20, 40), {Prototype = ExplosionParticles_BlastSmoothBackground, Size = blast_smooth_size}, smoothness_level / 5);
	CreateParticle("Smoke2", PV_Random(x - 5, x + 5), PV_Random(y - 5, y + 5), PV_Random(-1, 1), PV_Random(-1, 1), PV_Random(20, 40), {Prototype = ExplosionParticles_BlastSmooth, Size = blast_smooth_size}, smoothness_level / 5);
	CreateParticle("Dust", PV_Random(x - 5, x + 5), PV_Random(y - 5, y + 5), 0, 0, PV_Random(18, 25), {Prototype = ExplosionParticles_Blast, Size = blast_size}, smoothness_level / 5);
	CreateParticle("StarFlash", PV_Random(x - 6, x + 6), PV_Random(y - 6, y + 6), PV_Random(-wilderness_level/4, wilderness_level/4), PV_Random(-wilderness_level/4, wilderness_level/4), PV_Random(10, 12), {Prototype = ExplosionParticles_Star, Size = star_size}, wilderness_level / 3);
	CreateParticle("Shockwave", x, y, 0, 0, 15, {Prototype = ExplosionParticles_Shockwave, Size = shockwave_size}, nil);
	
	// cast either some sparks on land or bubbles under water
	if(GBackLiquid(x, y) && Global.CastBubbles)
	{
		Global->CastBubbles(level * 7 / 10, level, x, y);
	}
	else
	{
		CreateParticle("Magic", PV_Random(x - 5, x + 5), PV_Random(y - 5, y + 5), PV_Random(-level_pow_fraction, level_pow_fraction), PV_Random(-level_pow_fraction, level_pow_fraction), PV_Random(25, 70), ExplosionParticles_Glimmer, level);
	}
	
	// very wild explosion? Smoke trails!
	var smoke_trail_count = wilderness_level / 10;
	var angle  = Random(360);
	var failsafe = 0; // against infinite loops
	while (smoke_trail_count > 0 && (++failsafe < smoke_trail_count * 10))
	{
		angle += RandomX(40, 80);
		var smokex = Sin(angle, RandomX(level / 4, level / 2));
		var smokey = -Cos(angle, RandomX(level / 4, level / 2));
		if (GBackSolid(x + smokex, y + smokey))
			continue;
		var lvl = 2 * wilderness_level;
		CreateSmokeTrail(lvl, angle, x + smokex, y + smokey);
		smoke_trail_count--;
	}
	
	// Temporary light effect
	if (level > 5)
		Global->CreateLight(x, y, level, Fx_Light.LGT_Blast);

	return;
}


global func FxSmokeTrailTimer(object target, effect e, int fxtime)
{
	var strength = e.strength;
	e.curr_strength = e.curr_strength * 94 / 100;
	
	var str = e.curr_strength;
	
	var initial_speed = 100 * (strength+20)/6;
	var speed = initial_speed * str / strength;
	var angle = e.angle + RandomX(-20,20);
	var x_dir = Sin(angle, speed);
	var y_dir = -Cos(angle , speed);
	
	if (speed < 2*100) return -1;
	
	// gravity
	y_dir += GetGravity() * 15;
	
	// draw
	e.particles_smoke.Size = PV_KeyFrames(0, 0, str / 2, 1000, str);
	e.particles_blast.Size = PV_KeyFrames(0, 0, 0, 200, str / 3, 1000, 0);

	CreateParticle("Smoke2", e.x/100, e.y/100, RandomX(-1,1), RandomX(-1,1), 60, e.particles_smoke,1);
		
	// then calc next position
	e.x += x_dir;
	e.y += y_dir;
	
	if (!e.noblast)
	{
		var x_dir_blast = x_dir / 200;
		var y_dir_blast = y_dir / 200;
		CreateParticle("Thrust", e.x/100, e.y/100, PV_Random(x_dir_blast - 2, x_dir_blast + 2), PV_Random(y_dir_blast - 2, y_dir_blast + 2), 50, e.particles_blast, 1);
	}
	
	
	if (GBackSemiSolid(e.x/100, e.y/100))
		return -1;
	
	e.curr_strength = str;
}

