local target, // attach target
      damage; // damage dealt to target

func Initialize()
{
	SetR(Random(360));
	AddAlienFlareEffect(100);
	SetObjectBlitMode(GFX_BLIT_Additive);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// sticking to a clonk

func AttachTo(target)
{
	SetAction("AGlobbing", target);
	
	if (!DecreasePhysical(target))
	{
		RemoveObject();
	}
}

func DecreasePhysical(object target)
{
	// Decrease at most 30% of walk speed
	if (IsSlowed(target)) return false;

	AddEffect("Slimed", target, 50, 800, nil, GetID());
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// sticking to the ground

func Glob2Ground(int damage)
{
	this.damage = damage;
	SetAction("Globbing");
}

func Check()
{
	var living;
	while (living = FindObject(Find_InRect(-5, -5, 10, 10), Find_OCF(OCF_Alive), Find_NoContainer(), Find_Exclude(living)))
		if (!(living->~IsAlien()))
			return HitLiving(living);
	while (living = FindObject(Find_AtPoint(), Find_OCF(OCF_Alive), Find_NoContainer(), Find_Exclude(living)))
		if (!(living->~IsAlien()))
			return HitLiving(living);
	
	if (GetActTime() >= 600)
		return Boom();
}

func HitLiving(target)
{
	if (!IsSlowed(target)) AddEffect("Slimed", target, 101, 1500, nil, GetID());

	// TODO damage roflol
	
	//DoDmg(damage, DMG_Bio, target);
	Boom();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// slime stuff

func Boom()
{
	RemoveObject();
}

func AttachTargetLost()
{
	Boom();
}

func IsSlowed(object target)
{
	return true;
	// TODO return (GetPhysical("Walk", 2, target) <= GetPhysical("Walk", 1, 0, GetID(target)) * 7 / 10);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// slow down effect

func FxSlimedStart(object target, proplist no, int temp, int strength)
{
	if (temp && IsSlowed(target)) return 0;
	
	// Variablen
	// 0: Walk
	// 1: Jump
	// 2: Scale
	// 3: Hangle
//	EffectVar(0, target, no) = GetPhysical("Walk", 1, 0, GetID(target)) * 1 / 10;
//	EffectVar(1, target, no) = GetPhysical("Jump", 1, 0, GetID(target)) * 1 / 10;
//	EffectVar(2, target, no) = GetPhysical("Scale", 1, 0, GetID(target)) * 1 / 10;
//	EffectVar(3, target, no) = GetPhysical("Hangle", 1, 0, GetID(target)) * 1 / 10;
//	
//	SetPhysical("Walk", GetPhysical("Walk", 0, target) - EffectVar(0, target, no), 2, target);
//	SetPhysical("Jump", GetPhysical("Jump", 0, target) - EffectVar(1, target, no), 2, target);
//	SetPhysical("Scale", GetPhysical("Scale", 0, target) - EffectVar(2, target, no), 2, target);
//	SetPhysical("Hangle", GetPhysical("Hangle", 0, target) - EffectVar(3, target, no), 2, target);

	no.original_clr = target->GetClrModulation();

	var r = 200 * GetRGBaValue(no.original_clr, RGBA_RED) / 255;
	var g = GetRGBaValue(no.original_clr, RGBA_GREEN);
	var b = 200 * GetRGBaValue(no.original_clr, RGBA_BLUE) / 255;
	var a = GetRGBaValue(no.original_clr, RGBA_ALPHA);

	target->SetClrModulation(RGBa(r, g, b, a));
}

func FxSlimedTimer()
{
	return -1;
}

func FxSlimedStop(object target, proplist no, int reason, int temp)
{
//	SetPhysical("Walk", GetPhysical("Walk", 0, target) + EffectVar(0, target, no), 2, target);
//	SetPhysical("Jump", GetPhysical("Jump", 0, target) + EffectVar(1, target, no), 2, target);
//	SetPhysical("Scale", GetPhysical("Scale", 0, target) + EffectVar(2, target, no), 2, target);
//	SetPhysical("Hangle", GetPhysical("Hangle", 0, target) + EffectVar(3, target, no), 2, target);
	
	// remove color info
	if (!GetEffect("*Slimed*", target)) target->SetClrModulation(no.original_clr);
	
	if (temp) return 0;
	
	// remove glob
	var glob = FindObject(Find_ID(SlimeGlob), Find_Action("AGlobbing"), Find_ActionTarget(target));
	if (glob) glob->~Boom();
}

// Fire! :o
func Incineration()
{
	Boom();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local BlastIncinerate = 1;
local ContactIncinerate = 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Globbing = {
	Prototype = Action,
	Name = "Globbing",
	Procedure = DFA_FLOAT,
	Delay = 4,
	FacetBase = 1,
	NextAction = "Globbing",
	EndCall = "Check",
},

AGlobbing = {
	Prototype = Action,
	Name = "AGlobbing",
	Procedure = DFA_ATTACH,
	Delay = 4,
	FacetBase = 1,
	NextAction = "AGlobbing",
},

};
