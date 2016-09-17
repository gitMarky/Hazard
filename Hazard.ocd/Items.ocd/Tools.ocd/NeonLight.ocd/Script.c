/*-- Neonlicht --*/

local on;

local color;

protected func Initialize() 
{
  //Kein Besitzer
  SetOwner(-1);
  
  color = new color {
      H = Random(256),
      S = 255,
      L = 128
  }
  
  SetColor(HSL(color. H, color.S / 2, color.L - 50));
}

public func Activate(object pByObj)
{
    if(on) return;
    else on = true;
  
    //Effect
    CreateEffect(IntNeonGlow, 100, 5);
    
    if(Contained()) Exit(Contained()->GetDir()*12 - 6, 0, 0, Contained()->GetDir()*6 - 3, -3, Contained()->GetDir()*60 - 30);
    
    return true;
}

public func RejectEntrance()
{
	// Nicht mehr sammelbar wenn an
	return on;
}

public func IsEquipment() { return true; }


// Properties

local Collectible = 1;
local Name = "$Name$";

// Effects

local IntNeonGlow = new Effect {
    Start = func(int temp) {
        if(temp) return;
        
        this.Target->SetColor(HSL(this.Target.color.H, this.Target.color.S, this.Target.color.L));
        this.Target->SetLightRange(400);
        this.Target->SetLightColor(HSLa(this.Target.color.H, this.Target.color.S, this.Target.color.L, 30));
        
        this.Target->CastParticles("StarSpark", 5, 5, 10, 40, 40, 90, GetColor(), GetColor());
        this.Target->CastParticles("Smoke", 5, 5, 10, 40, 40, 90, GetColor(), GetColor());
    },
    
    Timer = func(int time) {
        this.Target->CreateParticle("StarSpark", RandomX(-3, 3), RandomX(-3, 3), RandomX(-5, 5), RandomX(-4, -9), RandomX(40, 90), GetColor());
        if(!Random(3)) this.Target->CreateParticle("Smoke", RandomX(-3, 3), RandomX(-5, 5), RandomX(-4, -9), RandomX(140, 190), GetColor());
        
        if(time >= 4000) return -1;
    },
    
    Stop = func(bool temp) {
        if(temp) return;
        
        this.Target->SetLightColor();
        this.Target->SetLightRange();
        this.Target->SetColor(HSL(this.Target.color.H, this.Target.color.S / 3, 30));
        //FadeOut();
    },
};
