
local sky;
local reset;
local is_busy;
static a;

func Initialize()
{
	Sound("Rain", true, nil, nil, 1);	
	CreateEffect(Raining, 1, 1);
	
	Cloud->Place(10);
	Cloud->SetPrecipitation("Water", 1000);
	Cloud->SetInsertMaterial(false);
	for (var cloud in FindObjects(Find_ID(Cloud)))
	{
		cloud.Visibility = VIS_None;
	}
}

local Raining = new Effect
{
	Timer = func ()
	{
		Target->Thunder();
	},
};

func Thunder()
{
	if (sky < 6)
	{
		is_busy = 0;
	}
	else
	{
		is_busy = 1;
		sky = sky - reset;
		if (!Random(256 - sky))
			sky = RandomX(192, 224);
	}
	
	SetSkyAdjust(RGBa(255, 255, 255, 255-sky), RGB(255, 255, 255));
	
	if (!Random(350) && !is_busy)
	{
		reset = RandomX(3, 5);
		Sound("Thunders?", true);
		sky = RandomX(208, 240);
	}
}

