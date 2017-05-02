
local time, con, r, grow, dir, size;

local erup, er;

local light;

func Initialize()
{
	time = 0;
	SetGrowSpeed(600);
	SetRotationSpeed(-20);
	SetAction("Be");
	SetClrModulation(RGB(0, 128, 255));
	SetCategory(GetCategory() | C4D_Parallax);
	AddLightAmbience(400,);
    SetLightColor(RGB(100, 100, 255));
    AddTimer(this.Timer, 1);
}

func SetRotationSpeed(d)
{
	dir = d;
}

func SetGrowSpeed(d)
{
	grow = d;
}

func SetGrowPos(d)
{
	size = d;
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
	
	// Exploeffekte auf der Sonne
	if (erup)
	{
		if (!Random(15))
			erup = false;
		
		var x, y;
		x = -Sin(er + r + RandomX(-15, 15), 175 * con * 8 / 10000, 100);
		y = Cos(er + r + RandomX(-15, 15), 175 * con * 8 / 10000, 100);
		// TODO CreateParticle("SunSpark", x, y, x / 12, y / 12, RandomX(400, 500), RGBa(255, 60 + Random(80), 0, 100), this);
	}
	else if (!Random(35))
	{
		erup = true;
		er = Random(360);
	}
	
	// Protuberanzen (!)
	if (!Random(500))
	{
		var pr = Random(360), x, y, rx, ry;
		x = -Sin(pr, 175 * con * 8 / 10000);
		y = Cos(pr, 175 * con * 8 / 10000);
		for (var i = pr - 10; i < pr + 10; i += 2)
		{
			rx = -Sin((i - pr) * 9 + pr, 5);
			ry = Cos((i - pr) * 9 + pr, 5);
      		// TODO CreateParticle("SunFlare", rx + x, ry + y, rx, ry, RandomX(700, 800), RGBa(255,80+Random(32),0,80), this());
      		// TODO CreateParticle("SunSpark", x, y, rx, ry, RandomX(400, 600), RGBa(255,100+Random(128),0,80), this());
		}
	}  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BorderBound = 1;
local Parallaxity = [60, 60];

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