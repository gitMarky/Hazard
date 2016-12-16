#include Library_HealingItem
#include Library_HazardEquipment

func HealRate(){	return 3;}
func HealAmount(){	return 100;}

func Decorate(object user, proplist healing_effect)
{
	user->CreateEffect(MedipackHeal, 1, 1, healing_effect);
}


local MedipackHeal = new Effect
{
	Start = func (int temporary, proplist healing_effect)
	{
		if (temporary) return;
		this.healing_effect = healing_effect;
	},

	Timer = func (int time)
	{
		if (!this.healing_effect)
		{
			return FX_Execute_Kill;
		}
		// TODO: if (Target->GetAction() != "Heal") return FX_Execute_Kill;
	
		MedipackSpark();
	},

	Damage = func (int change)
	{
		if (change >= 0) return change;

		RemoveEffect(nil, Target, this.healing_effect);
		RemoveEffect("MedipackHeal", Target);
		return change;
	},

	Stop = func (int reason, bool temp)
	{
		if (temp) return;
		
		if (Target->GetAction() == "Heal") Target->SetAction("Walk");
	},

	MedipackSpark = func ()
	{
		if (!Target) return;
		var width = Target->GetObjWidth();
		var height = Target->GetObjHeight();
		width -= width / 3;
		height -= height / 3;
		width /= 2;
		height /= 2;

		Target->CreateParticle("Heal", PV_Random(-width, width), PV_Random(-height, height), 0, -7, PV_Random(15, 20),
		{
			Prototype = Particles_Magic(),
			R = 255, G = 0, B = 0,
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
