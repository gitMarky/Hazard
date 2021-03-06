
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
		CreateParticle("ElectroSpark", PV_Random(x - 2, x + 2), PV_Random(y - 2, y + 2),
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

	CreateParticle("Magic", x, y, 0, 0, lifetime ?? 20,
	{
		Prototype = Particles_Magic(),
		BlitMode = GFX_BLIT_Additive,
		R = r, G = g, B = b,
		Size = size ?? 8,
	});
}

/* Spawn-Effect */

static const FxSpawnEffect = new Effect
{
	Start = func(int temp, int rgba)
	{
		this.r = GetRGBaValue(rgba, RGBA_RED);
		this.g = GetRGBaValue(rgba, RGBA_GREEN);
		this.b = GetRGBaValue(rgba, RGBA_BLUE);
		this.a = GetRGBaValue(rgba, RGBA_ALPHA);

		this.angle = 360;
	},

    Timer = func()
    {
		if (this.angle <= 0)
		{		
			this.Target->CreateParticle("Magic", 0, 0, PV_Random(-10, 10), PV_Random(-10, 10), 20,
			{
				Prototype = Particles_Magic(),
				BlitMode = GFX_BLIT_Additive,
				R = this.r, G = this.g, B = this.b, Alpha = PV_Linear(this.a, 0),
				Size = PV_Random(1, 4),
				Attach = ATTACH_Front | ATTACH_MoveRelative,
			}, 20);
			
			return FX_Execute_Kill;
		}

		for (var i = 0; i < 5; i++)
		{
			var angle = this.angle - 90 * i;
			var radius = this.angle / 20;
			var x = Cos(angle, radius);
			var y = Sin(angle, radius);

			this.Target->CreateParticle("Magic", x, y, 0, 0, 20,
			{
				Prototype = Particles_Magic(),
				BlitMode = GFX_BLIT_Additive,
				R = this.r, G = this.g, B = this.b, Alpha = PV_Linear(this.a / 2, 0),
				Size = BoundBy((360 - this.angle) / 50, 1, 4),
				Attach = ATTACH_Front | ATTACH_MoveRelative,
			});
		}

		this.angle -= 10;
    },
};


global func AddSpawnEffect(int rgba)
{
	AssertObjectContext("AddSpawnEffect()");

    CreateEffect(FxSpawnEffect, 2, 1, rgba);
    FadeIn(72);
}
