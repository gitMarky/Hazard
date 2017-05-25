func Initialize()
{
	SetAction("Off");
}

func On(int iAction)
{
	AddLightAmbience(15);
	if (!iAction)
		iAction = Random(GetActions() + 1);
	return SetAction(Format("On%d", iAction));
}

func Off()
{
	if (GetAction() == "Off")
	{
		return false;
	}
	else
	{
		RemoveLight();
		SetGraphics(nil, GetID(), 1);
		SetAction("Off");
		return true;
	}
}

func GetActions(){	return 3;}

/* Damage */

func IsProjectile(object projectile)
{
	if (GetAction() != "Broken") return false;
	return !(projectile->~NoDecoDamage());
}

func Damage()
{
	if (GetAction() == "Broken") return;
	RemoveLight();
	// BANG!
	//CastObjects(SPRK, 7, 50);
	CreateSparksEffect(15, RGB(210, 210, 0));
	CreateSmokeTrail(RandomX(15, 20), Random(360), 0, 0, nil, true);
	CreateSmokeTrail(RandomX(15, 20), Random(360), 0, 0, nil, true);
	
	// TODO:
	Sound("Hits::Materials::Glass::GlassShatter");
	//TODO Sound("Blast1");
	// launch!
	SetSpeed(RandomX(-25, 25), RandomX(-45, -35));
	SetRDir(GetXDir() * 2);
	SetAction("Broken");
	SetPhase(Random(3));
}

func ChooseImage()
{
	var id, defs;
	while (id = GetDefinition(defs++))
		if (!Random(18))
			break;
	if (!id)
		return SetGraphics(nil, GetID(), 1);
	
	SetGraphics(nil, id, 1, 1);
	SetObjDrawTransform(7000 / id->GetDefWidth(), 0, 0, 0, 5000 / id->GetDefHeight(), -1000, 1);
}

/* EMP */

func IsMachine()
{
	return (GetAction() != "Off" && GetAction() != "Broken");
}

func EMPShock()
{
	return Off();
}

/* Serialisierung */

func Serialize(array extra) // TODO: save object
{
	if (GetAction() == "On1")
		extra[GetLength(extra)] = "SetAction(\"On1\")";
	if (GetAction() == "On2")
		extra[GetLength(extra)] = "SetAction(\"On2\")";
	if (GetAction() == "On3")
		extra[GetLength(extra)] = "SetAction(\"On3\")";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Off = {
	Prototype = Action,
	Name = "Off",
	Delay = 1,
	FacetBase = 1,
	NextAction = "Off",
},

Broken = {
	Prototype = Action,
	Name = "Broken",
	Length = 3,
	Delay = 0,
	X = 10,
	Y = 0,
	Wdt = 8,
	Hgt = 6,
	OffX = 1,
	OffY = 1,
	FacetBase = 1,
	NextAction = "Broken",
},

On1 = {
	Prototype = Action,
	Name = "On1",
	Length = 4,
	Delay = 3,
	X = 10,
	Y = 6,
	Wdt = 8,
	Hgt = 6,
	OffX = 1,
	OffY = 1,
	FacetBase = 1,
	NextAction = "On1",
},

On2 = {
	Prototype = Action,
	Name = "On2",
	Length = 8,
	Delay = 2,
	X = 10,
	Y = 12,
	Wdt = 8,
	Hgt = 6,
	OffX = 1,
	OffY = 1,
	FacetBase = 1,
	NextAction = "On2",
},

On3 = {
	Prototype = Action,
	Name = "On3",
	Length = 0,
	Delay = 50,
	FacetBase = 1,
	NextAction = "On3",
	StartCall = "ChooseImage",
},

};
