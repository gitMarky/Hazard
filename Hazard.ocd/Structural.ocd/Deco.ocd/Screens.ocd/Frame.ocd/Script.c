
local smashed;
local width, height;
 
global func AddFrame()
{
	AssertObjectContext();

	var frame = CreateObject(FRME, 0, 25, GetOwner());
	ScheduleCall(frame, frame.Set, 1, nil, this);
	return frame;
}
 
global func RemoveFrame()
{
	AssertObjectContext();

	var frame = FindObject(Find_ID(FRME), Find_AtPoint());
	if (frame)
		frame->RemoveObject();
}
 

func Initialize()
{
	SetClrModulation(RGBa(255, 255, 255, 25));
	SetObjectBlitMode(GFX_BLIT_Additive);
	SetGraphics("Frame", GetID(), 4, 1);
}

 
func Set(object target)
{
	if (target == nil)
	{
		FatalError("This function needs a target other than nil!");
	}

	// *1000/(51-2-3) => Normalized to 1000 and relation: target <-> screen without frame
	var divisor = 61;
	var full_size = 1000;

	width = target->GetObjWidth() * full_size / divisor;
	height = target->GetObjHeight() * full_size / divisor;
	
	SetShape
	(
		(FRME->GetDefOffset(0) * width) / full_size,
		(FRME->GetDefOffset(1) * height) / full_size,
		(FRME->GetDefWidth() * width) / full_size,
		(FRME->GetDefHeight() * height) / full_size
	);
	SetPosition(target->GetX(), target->GetY());
	
	for (var i = 0; i < 5; i++)
	{
		SetObjDrawTransform(width, 0, 0, 0, height, 0, i);
	}
}
 
/* Color modulation */
 
func PanelColor(int rgba)
{
	var r = GetRGBaValue(rgba, RGBA_RED);
	var g = GetRGBaValue(rgba, RGBA_GREEN);
	var b = GetRGBaValue(rgba, RGBA_BLUE);
	SetClrModulation(RGBa(r, g, b, 25));
	return this;
}
 

func FrameColor(int rgba)
{
	SetClrModulation(rgba, 4);
	return this;
}
 

func Damage()
{
	if (!smashed || (smashed < 3 && !Random(4)))
	{
		Scratch();
	}
	if (GetDamage() >= 75)
	{
		Shatter();
	}
}


func Scratch()
{
	smashed++;
	// TODO: effects
	//CastObjects(SPRK, 7, 50);
	CreateSparksEffect(15, RGB(120, 150, 135));
	Sound("Hits::Materials::Glass::GlassHit?");

	SetGraphics(Format("%s%d", "Broken", RandomX(1, 4)), GetID(), smashed, 1, nil, 1);
	SetObjDrawTransform(width, 0, 0, 0, height, 0, smashed);
}


func Shatter()
{
	smashed = 4;
	// TODO: effects
	//CastParticles("SplinterGlass", 1, 35, RandomX(-20, 20), -5, 20, 20, GetClrModulation(), GetClrModulation());
	Sound("Hits::Materials::Glass::GlassShatter");
	
	SetGraphics("BrokenGlass", GetID(), 0, 1, nil, 1);
	SetGraphics("BrokenEnd", GetID(), 1, 1, nil, 1);
	SetGraphics(nil, nil, 2);
	SetGraphics(nil, nil, 3);
}


// TODO: proper implementation of SaveScenarioObject(), with call to AddFrame() in the other object.


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
