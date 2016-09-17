
global func Particles_JumpPad(int angle, int color, int size)
{
	size = size ?? 21;
	color = color ?? 0xffffffff;
	
	return
	{
		Size = size,
		Alpha = PV_KeyFrames(0, 0, 0, 400, 255, 1000, 0),
		R = GetRGBaValue(color, RGBA_RED),
		G = GetRGBaValue(color, RGBA_GREEN),
		B = GetRGBaValue(color, RGBA_BLUE),
		Rotation = angle,
	};
}

global func Particles_EmpShock(int color)
{
	color = color ?? 0xffffffff;
	return {
		Alpha = PV_KeyFrames(0, 0, 0, 200, 255, 1000, 0),
		R = GetRGBaValue(color, 1),
		G = GetRGBaValue(color, 2),
		B = GetRGBaValue(color, 3),
		BlitMode = GFX_BLIT_Additive,
	};
}

global func Particles_ThrustColored(int r, g, b)
{
	return {
		Prototype = Particles_Thrust(),
		R = PV_KeyFrames(0, 0, r, 500, 2 * r / 5, 1000, r / 5),
		G = PV_KeyFrames(0, 0, g, 500, 2 * g / 5, 1000, g / 5),
		B = PV_KeyFrames(0, 0, b, 500, 2 * b / 5, 1000, b / 5),		
	};
}


global func CreateSparksEffect(int amount, int rgb, int x, int y)
{
	AssertObjectContext("CreateSparksEffect()");

	var prototype = Particles_ElectroSpark1();
	
	if (rgb)
	{	
		prototype = Particles_Colored(prototype, rgb);
	}

	var level = 30;
	for (var i = 0; i < amount; ++i)
	{
		var angle = Random(360);
		var speed = RandomX(0, level);
		CreateParticle("ElectroSpark", PV_Random(x - 2, x + 2),PV_Random(y - 2, y + 2),
		                               Sin(angle, speed), Cos(angle, speed), 20,
		{
			Prototype = prototype,
			Size = PV_Random(5, 8),
		});
	}
}


global func CreateLEDEffect(int color, int x, int y, int size, int lifetime)
{
	AssertObjectContext("CreateLEDEffect()");

	var r = GetRGBaValue(color, RGBA_RED);
	var g = GetRGBaValue(color, RGBA_GREEN);
	var b = GetRGBaValue(color, RGBA_BLUE);
	var a = GetRGBaValue(color, RGBA_ALPHA) / 2; // because the default value for magic particles is 128

	CreateParticle("Magic", x, y, 0, 0, lifetime ?? 20,
	{
		Prototype = Particles_Magic(),
		BlitMode = GFX_BLIT_Additive,
		R = r, G = g, B = b,
		Size = size ?? 8,
	});
}


global func CastParticles(string name, int amount, int level, int x, int y, int a0, int a1, int b0, int b1, object obj)
{
    if(!obj) if(!(obj = this)) return;
    
    var a, b;
    if(Random(2))
    {
        a = a1;
        b = b1;
    }
    else
    {
        a = a0;
        b = b0;
    }
    
    var particles = {
        R = SplitRGBaValue(b)[0],
        G = SplitRGBaValue(b)[1],
        B = SplitRGBaValue(b)[2],
        A = SplitRGBaValue(b)[3],
        size = a * 5,
    };
    
    for(var i = 0; i < amount; i++)
    {
        obj->CreateParticle(name, x, y, RandomX(-level, level), RandomX(-level, level),10, particles, 1);
    }
    
    return true;
}
