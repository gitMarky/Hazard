/*-- Pump --*/

#include PIPL

local connections;
local drain, source;
local sources, source_index;
local is_running;

func Initialize()
{
	SetAction("Pump");
	drains = [];
	sources = [];
	// default power
	power = 2;
	
	AddTimer(this.Pumping, 4);
}

/* Important for pumps:

   first connect_toion -> source
   second connect_toion -> drain
*/

func Left(int repeat, bool solid, bool valve, id pipe_id, int power, object connect_to)
{
	if (connections < 2)
	{
		return _inherited(repeat, solid, valve, pipe_id, power, connect_to);
	}
}

func Right(int repeat, bool solid, bool valve, id pipe_id, int power, object connect_to)
{
	if (connections < 2)
	{
		return _inherited(repeat, solid, valve, pipe_id, power, connect_to);
	}
}

func Up(int repeat, bool solid, bool valve, id pipe_id, int power, object connect_to)
{
	if (connections < 2)
	{
		return _inherited(repeat, solid, valve, pipe_id, power, connect_to);
	}
}

func Down(int repeat, bool solid, bool valve, id pipe_id, int power, object connect_to)
{
	if (connections < 2)
	{
		return _inherited(repeat, solid, valve, pipe_id, power, connect_to);
	}
}

func ConnectTo(object connect_to, int dir)
{
	if (!connections)
	{
		source = connect_to;
	}
	if (connections == 1)
	{
		drain = connect_to;
	}
	connections++;
	return _inherited(connect_to, dir);
}

/* Public interface */

func UpdateEfflux()
{
	drains = [];
	
	if (drain)
	{
		if (drain == pipe_left)  drain->UpdateSystem(this, PIPE_Right, 2);
		if (drain == pipe_right) drain->UpdateSystem(this, PIPE_Left, 2);
		if (drain == pipe_down)  drain->UpdateSystem(this, PIPE_Up, 2);
		if (drain == pipe_up)    drain->UpdateSystem(this, PIPE_Down, 2);
	}
	
	UpdateConflux();
}

func UpdateConflux()
{
	sources = CreateArray();

	if (source)
	{
		if (source == pipe_left)  source->UpdateSystem(this, PIPE_Right, 1);
		if (source == pipe_right) source->UpdateSystem(this, PIPE_Left, 1);
		if (source == pipe_down)  source->UpdateSystem(this, PIPE_Up, 1);
		if (source == pipe_up)    source->UpdateSystem(this, PIPE_Down, 1);
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
	PushBack(sources, next);
}


func TwoPumpError()
{
	Message("$Error$", this);
}

/* Do the pumping */

func Pumping()
{
	if (is_running && drains[0] && sources[0])
	{
		var mat;
		for (var i = 0; i < power; i++)
		{
			mat = ExtractLiquid(AbsX(GetX(sources[source_index])), AbsY(GetY(sources[source_index])));
			drains[drain_index]->CastLiquid(mat, 35);
		}
		
		if (!Random(4))
		{
			Smoke(0, 0, 15);
		}
		if (!Random(4))
		{
			Bubble(AbsX(GetX(sources[source_index])), AbsY(GetY(sources[source_index])));
		}
		
		drain_index++;
		source_index++;
		if (drains[drain_index] == 0)
		{
			drain_index = 0;
		}
		if (sources[source_index] == 0)
		{
			source_index = 0;
		}
	}
}

func On()
{
	is_running = true;
	Sound("Gear", false, 50, 0, 1);
}

func Off()
{
	is_running = false;
	Sound("Gear", false, 0, 0, -1);
}

func Status()
{
	return is_running;
}

/* Console control */

func ConsoleControl(int i)
{
	if (i == 1)
	{
		if (is_running)
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
	if (is_running)
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
	if (is_running)
		extra[GetLength(extra)] = "On()";
	if (source)
		extra[GetLength(extra)] = ["LocalN(\"con\")=Object(%d)", source];
	if (drain)
		extra[GetLength(extra)] = ["LocalN(\"eff\")=Object(%d)", drain];
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
