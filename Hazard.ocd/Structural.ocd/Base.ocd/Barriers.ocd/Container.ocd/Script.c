func Initialize()
{
	SetAction("Be");
	SetPerspective(1);
	SetColor(HSL(Random(255), Random(100) + 25, 88 + 40));
}

func IsCraneGrabable(){ return true;}

func Hit(){ Sound("Objects::Clonk");}

func SetPerspective(int perspective)
{
	SetPhase(perspective);
	SetSolidMask(perspective * 64, 0, 64, 29);
	if (perspective == 2)
	{
		SetVertexXY(0, +15, 13);
		SetVertexXY(0, -15, 13);
	}
	else
	{
		SetVertexXY(0, +28, 13);
		SetVertexXY(1, -28, 13);
	}
}

func Serialize(array extra) // TODO: Implement scenario saving properly
{
	if (GetPhase() != 1)
	{
		extra[GetLength(extra)] = Format("SetPerspective(%d)", GetPhase());
	}
	extra[GetLength(extra)] = Format("SetColor(%d)", GetColor());
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
Be = {
	Prototype = Action,
	Name = "Be",
	Length = 4,
	X = 0,
	Y = 0,
	Wdt = 64,
	Hgt = 30,
},

};
