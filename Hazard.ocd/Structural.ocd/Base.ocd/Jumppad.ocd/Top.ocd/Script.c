local strength;
local color;

func IsMachine()
{
	return true;
}

func Initialize()
{
	SetGraphics("Lamps", GetID(), 1, GFXOV_MODE_ExtraGraphics);
	SetGraphics("Light", GetID(), 2, GFXOV_MODE_ExtraGraphics, nil, GFX_BLIT_Additive);
	SetGraphics("Shine", GetID(), 3, GFXOV_MODE_ExtraGraphics, nil, GFX_BLIT_Additive);
 	AddEffect("IntCheckBounce", this, 1, 1, this);
 	SetObjDrawTransform(1000, 0, 0, 0, 1000, -4000, 3);

	color = LIGHT_COLOR_TELEPORT;
	Activate();
}


func Activate()
{
	SetClrModulation(0xffffff, 1);
	SetClrModulation(color, 2);
	SetClrModulation(color, 3);
}


func Deactivate()
{
	SetClrModulation(SetRGBaValue(color, 120, RGBA_ALPHA), 1);
	SetClrModulation(RGBa(255, 255, 255, 1), 2);
	SetClrModulation(RGBa(255, 255, 255, 1), 3);
}


func SetEffectColor(int color)
{
	this.color = color;
	Activate();
}


func SetStrength(int strength)
{
	this.strength = strength;
}

func GetStrength()
{
	return this.strength;
}

func FxIntCheckBounceTimer(object pad, proplist fx, int timer)
{
	if (EMPShocked())  return;

	// bounce targets
	for (var target in FindObjects(
			Find_InRect(-8, -8, 16, 16),
			Find_Or(Find_OCF(OCF_Alive), Find_Func("IsBouncy")),
			Find_NoContainer()))
	{
		Bounce(target);
	}

	// particle effect for jump pad "waves"
	var lifetime = 40;
	var range = 180; // 18 pixels
	var xdir = +Sin(GetR(), range / lifetime);
	var ydir = -Cos(GetR(), range / lifetime);
	if (!(timer % 8)) CreateParticle("JumpPad", 0, 0, xdir, ydir, lifetime, Particles_JumpPad(GetR(), color, 3), 1);
}

func Bounce(object target)
{
	// bazillions of complificated calculiationons!
	var xdir_new, ydir_new, xdir_old, ydir_old;
	xdir_old = target->GetXDir();
	ydir_old = target->GetYDir();
	xdir_new = Sin(GetR(), strength);
	ydir_new = -Cos(GetR(), strength);
	// the object keeps a bit of its old velocity
	xdir_new += xdir_old / 10;
	ydir_new += ydir_old / 10;
	// puff!
	target->SetAction("Jump");
	target->SetSpeed(xdir_new, ydir_new);
	target->~OnBouncedByJumpPad(this);
	Sound("Structural::Jumppad");
}

func EMPShock()
{
	EMPShockEffect(38 * 3);
}

func EMPShockEnd()
{
}

func SaveScenarioObject(proplist props)
{
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {

Attach = {
	Prototype = Action,
	Name = "Attach",
	Procedure = DFA_ATTACH,
	Length = 1,
	Delay = 0,
	X = 0,
	Y = 0,
	Wdt = 25,
	Hgt = 8,
	NextAction = "Disabled",
},

};
