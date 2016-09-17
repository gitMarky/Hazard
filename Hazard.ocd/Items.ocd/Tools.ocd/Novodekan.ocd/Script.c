#include Library_HealingItem

func Decorate(object user, proplist healing_effect)
{
	user->CreateEffect(NovodekanHeal, 1, 1, healing_effect);
}

local NovodekanHeal = new Effect
{
	Start = func (int temporary, proplist healing_effect)
	{
		if (temporary)
		{
//			if (GetPhysical("Walk", 2, pTarget) <= GetPhysical("Walk", 1, 0, GetID(pTarget)) * 5 / 10)
				return;
		}
		Log("*HealStart*");
		
		this.healing_effect = healing_effect;
		
		// Lähmung
//		this.phys_walk = GetPhysical("Walk", 1, 0, GetID(pTarget)) * 3 / 10;
//		this.phys_jump = GetPhysical("Jump", 1, 0, GetID(pTarget)) * 3 / 10;
//		this.phys_scale = GetPhysical("Scale", 1, 0, GetID(pTarget)) * 3 / 10;
//		this.phys_hangle = GetPhysical("Hangle", 1, 0, GetID(pTarget)) * 3 / 10;
//		
//		SetPhysical("Walk",		GetPhysical("Walk", 0, pTarget) - this.phys_walk,		2, pTarget);
//		SetPhysical("Jump", 	GetPhysical("Jump", 0, pTarget) - this.phys_jump,		2, pTarget);
//		SetPhysical("Scale",	GetPhysical("Scale", 0, pTarget) - this.phys_scale,		2, pTarget);
//		SetPhysical("Hangle",	GetPhysical("Hangle", 0, pTarget) - this.phys_hangle,	2, pTarget);
	},
	
	Timer = func (int time)
	{
		if (!this.healing_effect)
		{
			return FX_Execute_Kill;
		}
	
		NovodekanSpark();
	},
	
	Stop = func (int reason, int temp)
	{
		Log("Heal stop");
		// TODO:
		//SetPhysical("Walk", GetPhysical("Walk", 0, target) + EffectVar(2, target, no), 2, target);
		//SetPhysical("Jump", GetPhysical("Jump", 0, target) + EffectVar(3, target, no), 2, target);
		//SetPhysical("Scale", GetPhysical("Scale", 0, target) + EffectVar(4, target, no), 2, target);
		//SetPhysical("Hangle", GetPhysical("Hangle", 0, target) + EffectVar(5, target, no), 2, target);
	},
	
	NovodekanSpark = func ()
	{
		if (!Target) return;
		var width = Target->GetObjWidth();
		var height = Target->GetObjHeight();
		width -= width / 3;
		height -= height / 3;
		width /= 2;
		height /= 2;

		Target->CreateParticle("Heal", PV_Random(-width, width), PV_Random(-height, height), 0, -10, PV_Random(15, 20),
		{
			Prototype = Particles_Magic(),
			R = 255, G = 0, B = 255,
			Alpha = PV_Linear(155, 0),
			Size = PV_Random(2, 3),
			//BlitMode = GFX_BLIT_Additive,
			Rotation = 0,
		}, 1);
	},
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = true;
