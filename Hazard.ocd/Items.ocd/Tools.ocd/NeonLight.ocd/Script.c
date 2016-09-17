
static const NEON_LIGHT_Range = 150;
static const NEON_LIGHT_BeginFade = 3000;
static const NEON_LIGHT_Lifetime = 4000;

local on; // Ob das Licht gezündet wurde
local color; // Die Farbwerte.

func Initialize()
{
	SetOwner(NO_OWNER);

	color = {
		H = Random(256),
		S = 255,
		L = 128,
	};
	
	// have it be a little darker while it is switched off
	SetColor(HSL(color.H, color.S / 2, color.L - 50));
}

func ControlUse(object user, int x, int y)
{
	return Activate(user, x, y);
}


func Activate(object user, int x, int y)
{
	if (on) return false;
	on = true;
	this.Collectible = false;
	
	CreateEffect(IntNeonGlow, 100, 5);
	
	if (!Place(user, x, y))
	{
		user->ControlThrow(this, x, y);
	}
	return true;
}

func Place(object user, int x, int y)
{
	var angle = Angle(0, 0, x, y);
	var pos = GetWall(angle);
	if(pos)
	{
		Exit(pos[0], pos[1], Angle(pos[0],pos[1]));
		SetPosition(user->GetX()+pos[0], user->GetY()+pos[1]);
		return true;
	}
	return false;
}


// returns true if there is a wall in direction in which "clonk" looks
// and puts the offset to the wall into "xo, yo" - looking from the clonk
func GetWall(int angle)
{
	var dist = 12;
	for (var dist = 12; dist < 18; dist++)
	{
		var x = +Sin(angle, dist);
		var y = -Cos(angle, dist);
		if (GBackSolid(x, y))
			return [Sin(angle, dist-5), -Cos(angle, dist-5)];
	}
	return false;
}


local IntNeonGlow = new Effect
{
    Start = func(int temp)
    {
        if(temp) return;
        
        this.Target->SetColor(HSL(this.Target.color.H, this.Target.color.S, this.Target.color.L));
        this.Target->SetLightRange(NEON_LIGHT_Range);
        this.Target->SetLightColor(HSLa(this.Target.color.H, this.Target.color.S, this.Target.color.L, 30));
  
  		NeonSparks();
  		NeonSmoke();
    },
    
    Timer = func(int time)
    {
        NeonSparks(); //this.Target->CreateParticle("StarSpark", RandomX(-3, 3), RandomX(-3, 3), RandomX(-5, 5), RandomX(-4, -9), RandomX(40, 90), GetColor());
        if (!Random(3)) NeonSmoke(); //this.Target->CreateParticle("Smoke", RandomX(-3, 3), RandomX(-5, 5), RandomX(-4, -9), RandomX(140, 190), GetColor());
        
        var light_reduction = NEON_LIGHT_Range * Max(0, time - NEON_LIGHT_BeginFade) / (NEON_LIGHT_Lifetime - NEON_LIGHT_BeginFade);
		this.Target->SetLightRange(Max(NEON_LIGHT_Range - light_reduction, 0));

        if (time >= NEON_LIGHT_Lifetime) return FX_Execute_Kill;
    },
    
    Stop = func(bool temp)
    {
        if(temp) return;

        this.Target->SetLightRange();
        this.Target->SetColor(HSL(this.Target.color.H, this.Target.color.S / 3, 30));
    },
    
    NeonSparks = func ()
    {
  		var radius = PV_Random(-3, 3);
  
        this.Target->CreateParticle("StarSpark", radius, radius, PV_Random(-5, 5), PV_Random(-4, -9), PV_Random(20, 40),
        {
        	Prototype = Particles_Glimmer(),
        	R = GetRGBaValue(this.Target->GetColor(), RGBA_RED),
        	G = GetRGBaValue(this.Target->GetColor(), RGBA_GREEN),
        	B = GetRGBaValue(this.Target->GetColor(), RGBA_BLUE),
        	Size = PV_Random(2, 6),
        }, 5);
    },
    
    NeonSmoke = func ()
    {
  		var radius = PV_Random(-3, 3);

        this.Target->CreateParticle("Smoke", radius, radius, PV_Random(-5, -5), PV_Random(-4, -9), PV_Random(140, 190), 
        {
        	Prototype = Particles_Smoke(),
        	R = GetRGBaValue(this.Target->GetColor(), RGBA_RED),
        	G = GetRGBaValue(this.Target->GetColor(), RGBA_GREEN),
        	B = GetRGBaValue(this.Target->GetColor(), RGBA_BLUE),
        	Size = PV_Random(2, 6),
        }, 5);
    },
};


func RejectEntrance(){	return on;} // do not collect when on
func IsEquipment(){	return true;}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = true;
