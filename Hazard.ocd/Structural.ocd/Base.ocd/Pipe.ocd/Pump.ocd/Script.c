/*-- Pump --*/

#include PIPL

local connects, eff, con;
local conflux, temp2;
local running;

func Initialize()
{
	SetAction("Pump");
	efflux = [];
	conflux = [];
	// default power
	power = 2;
}

/* Wichtig f�r die Pumpen:

    Erster Anschluss -> source
    Zweiter Anschluss -> drain
*/

func Left(int iRepeat, bool solid, bool valve, id pipeId, int iPower, object connect)
{
	if (connects < 2)
	{
		return _inherited(iRepeat, solid, valve, pipeId, iPower, connect);
	}
}

func Right(int iRepeat, bool solid, bool valve, id pipeId, int iPower, object connect)
{
	if (connects < 2)
	{
		return _inherited(iRepeat, solid, valve, pipeId, iPower, connect);
	}
}

func Up(int iRepeat, bool solid, bool valve, id pipeId, int iPower, object connect)
{
	if (connects < 2)
	{
		return _inherited(iRepeat, solid, valve, pipeId, iPower, connect);
	}
}

func Down(int iRepeat, bool solid, bool valve, id pipeId, int iPower, object connect)
{
	if (connects < 2)
	{
		return _inherited(iRepeat, solid, valve, pipeId, iPower, connect);
	}
}

func ConnectTo(object connect, int dir)
{
	if (!connects)
	{
		con = connect;
	}
	if (connects == 1)
	{
		eff = connect;
	}
	connects++;
	return _inherited(connect, dir);
}

/* Public interface */

func UpdateEfflux()
{
	efflux = [];
	
	if (eff)
	{
		if (eff == left)  eff->UpdateSystem(this, PIPE_Right, 2);
		if (eff == right) eff->UpdateSystem(this, PIPE_Left, 2);
		if (eff == down)  eff->UpdateSystem(this, PIPE_Up, 2);
		if (eff == up)    eff->UpdateSystem(this, PIPE_Down, 2);
	}
	
	UpdateConflux();
}

func UpdateConflux()
{
	conflux = CreateArray();

	if (con)
	{
		if (con == left)  con->UpdateSystem(this, PIPE_Right, 1);
		if (con == right) con->UpdateSystem(this, PIPE_Left, 1);
		if (con == down)  con->UpdateSystem(this, PIPE_Up, 1);
		if (con == up)    con->UpdateSystem(this, PIPE_Down, 1);
	}
}

func UpdateSystem(object start, int from, bool pump)
{
	if (pump)
	{
		start->~TwoPumpError();
	}
}


func NewConflux(object next)
{
	PushBack(conflux, next);
}


func TwoPumpError()
{
	Message("$Error$", this);
}

/* Do the pumping */

func Pumping()
{
	if (running && efflux[0] && conflux[0])
	{
		var mat;
		for (var i = 0; i < power; i++)
		{
			mat = ExtractLiquid(AbsX(GetX(conflux[temp2])), AbsY(GetY(conflux[temp2])));
			efflux[temp]->CastLiquid(mat, 35);
		}
		
		if (!Random(4))
		{
			Smoke(0, 0, 15);
		}
		if (!Random(4))
		{
			Bubble(AbsX(GetX(conflux[temp2])), AbsY(GetY(conflux[temp2])));
		}
		
		temp++;
		temp2++;
		if (efflux[temp] == 0)
		{
			temp = 0;
		}
		if (conflux[temp2] == 0)
		{
			temp2 = 0;
		}
	}
}

func On()
{
	running = true;
	Sound("Gear", false, 50, 0, 1);
}

func Off()
{
	running = false;
	Sound("Gear", false, 0, 0, -1);
}

func Status()
{
	return running;
}

/* Console control */

func ConsoleControl(int i)
{
	if (i == 1)
	{
		if (running)
		{
			return "$TurnOff$";
		}
		else
		{
			return "$TurnOn$";
		}
	}
}

func ConsoleControlled(int i)
{
	if (i == 1)
	{
		Access();
	}
}

/* Control by switch */
func Access()
{
	if (running)
	{
		Off();
	}
	else
	{
		On();
	}
}

/* Serialisierung */

func Serialize(array extra) // TODO: Implement proper saving mechanism
{
	_inherited(extra);
	if (running)
		extra[GetLength(extra)] = "On()";
	if (con)
		extra[GetLength(extra)] = ["LocalN(\"con\")=Object(%d)", con];
	if (eff)
		extra[GetLength(extra)] = ["LocalN(\"eff\")=Object(%d)", eff];
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
Pump = {
	Prototype = Action,
	Name = "Pump",
	Procedure = DFA_NONE,
	Directions = 4,
	Length = 4,
	Delay = 0,
	X = 0,
	Y = 0,
	Wdt = 50,
	Hgt = 50,
	FacetBase = 0,
	NextAction = "Hold",
},

};
