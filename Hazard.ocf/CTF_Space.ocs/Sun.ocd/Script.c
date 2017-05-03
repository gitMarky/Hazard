
local time, con, r, grow, dir, size;

local erup, er;

local light;

func Initialize()
{
	// set effect values
	time = 0;
	SetGrowSpeed(600);
	SetRotationSpeed(-20);

	// set look
	SetAction("Be");
	SetCategory(GetCategory() | C4D_Parallax);
	AddLightAmbience(400);
    SetLightColor(RGB(100, 100, 255));
    
    // start effect
    AddTimer(this.Timer, 1);
}

func SetRotationSpeed(int amount)
{
	dir = amount;
}

func SetGrowSpeed(int amount)
{
	grow = amount;
}

func SetGrowPos(int amount)
{
	size = amount;
}


func Timer()
{
	time++;
	
	con = 1200 + Sin(size, 20, 100);

	var w = con;
	var h = con;
	
	var fsin = -Sin(r, 1000, 100), fcos = Cos(r, 1000, 100);
	
	var xoff = 0;
	var yoff = 0;
	
	var width = +fcos * w / 1000, height = +fcos * h / 1000;
	var xskew = +fsin * h / 1000, yskew = -fsin * w / 1000;
	
	var xadjust = +fcos * xoff + fsin * yoff;
	var yadjust = -fsin * xoff + fcos * yoff;
	
	// set matrix values
	SetObjDrawTransform(width, xskew, xadjust, yskew, height, yadjust);
	
	r += dir;
	size += grow;
	if (size > 36000)
		size -= 36000;
	
	//SetClrModulation(RGB(200 - Sin(time, 55), 128, 0));

	// sun explosion effects
	if (erup)
	{
		if (!Random(15))
			erup = false;
		
		var x, y;
		x = -Sin(er + r + RandomX(-15, 15), 175 * con * 8 / 10000, 100);
		y = Cos(er + r + RandomX(-15, 15), 175 * con * 8 / 10000, 100);
		CreateParticle("SunSpark", x, y, x / 12, y / 12, 127, Particles_SunSpark(255, PV_Random(60, 140), 0, 155, PV_Random(80, 100)));
	}
	else if (!Random(35))
	{
		erup = true;
		er = Random(360);
	}
	
	// protuberances (!)
	if (!Random(500))
	{
		var pr = Random(360), x, y, rx, ry;
		var x = -Sin(pr, 175 * con * 8 / 10000);
		var y = Cos(pr, 175 * con * 8 / 10000);
		for (var i = pr - 10; i < pr + 10; i += 2)
		{
			rx = -Sin((i - pr) * 9 + pr, 5);
			ry = Cos((i - pr) * 9 + pr, 5);
      		CreateParticle("SunFlare", rx + x, ry + y, rx, ry, 255, Particles_SunFlare(255, PV_Random(80, 122), 0, 175, PV_Random(115, 160)));
      		CreateParticle("SunSpark", x, y, rx, ry, 127, Particles_SunSpark(255, PV_Random(100, 228), 0, 175, PV_Random(80, 120)));
		}
	}  
}


func Particles_SunSpark(r, g, b, a, size)
{
	// lifetime should be 127
	return
	{
		BlitMode = GFX_BLIT_Additive,
		Rotation = PV_Direction(),
		Attach = ATTACH_Front | ATTACH_MoveRelative,
		Size = size,
		R = r ?? 255,
		G = g ?? 255,
		B = b ?? 255,
		Alpha = PV_Linear(a ?? 100, 0),
	};
}

func Particles_SunFlare(r, g, b, a, size)
{
	// lifetime should be 255
	return
	{
		BlitMode = GFX_BLIT_Additive,
		Rotation = PV_Direction(),
		Attach = ATTACH_Front | ATTACH_MoveRelative,
		Size = size,
		R = r ?? 255,
		G = g ?? 255,
		B = b ?? 255,
		Alpha = PV_Linear(a ?? 100, 0),
	};
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BorderBound = 1;
local Parallaxity = [60, 60];
local Plane = -1000;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Be = {
	Prototype = Action,
	Name = "Be",
	Procedure = DFA_FLOAT,
	FacetBase = 1,
	NextAction = "Hold",
},

};