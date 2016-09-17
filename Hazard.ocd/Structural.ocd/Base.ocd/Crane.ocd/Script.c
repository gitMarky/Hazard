
local length, size, slide;

func Initialize()
{
	// default configuration for a part
	SetAction("Crane");
	size = 14;
	AddPart();
	CreateCrane();
}

func CreateCrane()
{
	if (slide) return slide;
	slide = CreateObject(SLDE, 0, 5, GetOwner());
	slide->SetCrane(this);
}

func SetCraneLength(int new_length)
{
	// 0 geht nicht
	if (new_length <= 0)
	{
		FatalError(Format("You have to pass a positive length, got %d", new_length));
	}
	if (new_length > length) AddParts(new_length);
	else if (new_length < length) RemoveParts(new_length);
}

// handle length

func AddParts(int new_length)
{
	while (length < new_length) AddPart();
}

func RemoveParts(int new_length)
{
	new_length = Max(1, new_length);
	// Solang wegnehmen, bis richtig
	while (length > new_length) RemovePart();
}

func AddPart()
{
	length += 1;
	SetGraphics("Part", GetID(), length, GFXOV_MODE_Base);
	AdjustSize();
}

func RemovePart()
{
	if (length == 1) return;
	SetGraphics(nil, GetID(), length);
	length -= 1;
	AdjustSize();
}

func AdjustSize()
{
	// adjust shape
	var width = size * length;
	SetShape(-width / 2, -4, width, 8);
	
	// adjust graphics
	for (var part = 1, offset = -length + 1; part <= length; part++)
	{
		SetObjDrawTransform(1000, 0, size * 500 * offset, 0, 1000, 0, part);
		offset += 2;
	}
}

/* Callbacks */

func LeftX()
{
	if (length % 2)
		return GetX() - (length / 2 * size) - size / 2;
	else
		return GetX() - (length / 2 * size);
}

func RightX()
{
	if (length % 2)
		return GetX() + (length / 2 * size) + size / 2;
	else
		return GetX() + (length / 2 * size);
}

func ConsoleControl(int i)
{
	if (slide)
		return slide->ConsoleControl(i);
}

func ConsoleControlled(int i, int Clonk)
{
	if (slide)
		return slide->ConsoleControlled(i, Clonk);
}

/* Serialisierung */

//func Serialize(array extra) // TODO: Saving the object
//{
//	extra[GetLength(extra)] = Format("Set(%d)", length);
//	var clamp = slide->LocalN("clamp");
//	if (clamp && clamp->LocalN("load"))
//	{
//		extra[GetLength(extra)] = Format
//		(
//			"Reconfigure(%d,%d,Object(%%d))",
//			GetX(slide) - GetX(),
//			GetY(clamp) - (GetY(slide) + 25),
//			clamp->LocalN("clamp")
//		);
//	}
//	else
//	{
//		extra[GetLength(extra)] = Format("Reconfigure(%d,%d)", GetX(slide) - GetX(), GetY(clamp) - (GetY(slide) + 25));
//	}
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Crane = {
	Prototype = Action,
	Name = "Crane",
	Procedure = DFA_FLOAT,
	Directions = 1,
	Length = 1,
	Delay = 0,
	FacetBase = 1,
	NextAction = "Crane",
},

};
