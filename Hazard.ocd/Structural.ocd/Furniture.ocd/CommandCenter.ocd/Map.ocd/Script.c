
local next_phase;

func Initialize()
{
	SetAction("Move");
	SetPhase(Random(20));
	next_phase = 0;
	Move();
}

func Move()
{
	if (GetAction() != "Stand")
	{
		var phase = GetPhase();
		if (phase != next_phase)
		{
			SetPhase(BoundBy(next_phase, phase - 1, phase + 1)); // not there yet
		}
		else if (!Random(50))
		{
			// moved there: get next target. 
			next_phase = Random(20);
		}
		if (!Random(2)) CreateLEDEffect(RGB(200, 255, 255), RandomX(-26, 22), RandomX(-18, 9), RandomX(2, 4), 20);
	}
	ScheduleCall(this, this.Move, 5, 1);
}

func TurnOff()
{
	var phase = GetPhase();
	SetAction("Stand");
	SetPhase(phase);
}

func TurnOn()
{
	var phase = GetPhase();
	SetAction("Move");
	SetPhase(phase);
}

func IsMachine()
{
	return true;
}

func EMPShock()
{
	return TurnOff();
}

/* Serialisierung */

func Serialize(array extra)
{
	if (GetAction() == "Stand")
	{
		extra[GetLength(extra)] = "SetAction(\"Stand\")";
		extra[GetLength(extra)] = Format("SetPhase(%d)", GetPhase());
	}
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
Move = {
	Prototype = Action,
	Name = "Move",
	Procedure = DFA_NONE,
	Length = 20,
	X = 0,
	Y = 55,
	Wdt = 54,
	Hgt = 42,
	OffX = 22,
	OffY = 1,
	FacetBase = 1,
},

Stand = {
	Prototype = Action,
	Name = "Stand",
	Procedure = DFA_NONE,
	Length = 20,
	X = 0,
	Y = 55,
	Wdt = 54,
	Hgt = 42,
	OffX = 22,
	OffY = 1,
	FacetBase = 1,
},

};
