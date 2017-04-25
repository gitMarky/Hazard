/*-- Pipe --*/


local pipe_left, pipe_right, pipe_up, pipe_down; // connect_toed objects
local valve; // valve
local drains, drain_index;
local has_liquid, power; // is in liquid?, amount of liquid output
local checked; // cache for UpdatePipesystem

static const PIPE_Left = 1;
static const PIPE_Right = 2;
static const PIPE_Up = 4;
static const PIPE_Down = 8;

func Initialize()
{
	SetAction("Pipe");
	DrawAsBackground();
	drains = [];
	
	has_liquid = GBackLiquid();
	
	// default output
	power = 1;
	
	AddTimer(this.LiquidCheck, 4);
}

// Allow connect_toions between valid pipelines (callbacks) only

func ExtendPipeLine(int direction_to, int direction_from, int repeat, bool solid, bool valve, id pipe_id, int power, object connect_to)
{
	repeat = repeat ?? 1;
	pipe_id = pipe_id ?? PIPL;
	connect_to = connect_to ?? CreatePipe(PIPE_Left, pipe_id);
	power = power ?? 1;

	ConnectTo(connect_to, PIPE_Left);
	connect_to->ConnectTo(this, PIPE_Right);
	connect_to->~ChangePower(power);
	if (solid)
	{
		connect_to->~Solid();
	}
	if (valve)
	{
		connect_to->~Valve();
	}
	
	return Max(0, repeat - 1);
}

func Left(int repeat, bool solid, bool valve, id pipe_id, int power, object connect_to)
{
	var remaining = ExtendPipeLine(PIPE_Left, PIPE_Right, repeat, solid, valve, pipe_id, power, connect_to);
	if (remaining > 0)
	{
		return connect_to->~Left(remaining, solid, valve, pipe_id, power);
	}
	else
	{
		return connect_to;
	}
}

func Right(int repeat, bool solid, bool valve, id pipe_id, int power, object connect_to)
{
	var remaining = ExtendPipeLine(PIPE_Right, PIPE_Left, repeat, solid, valve, pipe_id, power, connect_to);
	if (remaining > 0)
	{
		return connect_to->~Right(remaining, solid, valve, pipe_id, power);
	}
	else
	{
		return connect_to;
	}
}

func Up(int repeat, bool solid, bool valve, id pipe_id, int power, object connect_to)
{
	var remaining = ExtendPipeLine(PIPE_Up, PIPE_Down, repeat, solid, valve, pipe_id, power, connect_to);
	if (remaining > 0)
	{
		return connect_to->~Up(remaining, solid, valve, pipe_id, power);
	}
	else
	{
		return connect_to;
	}
}

func Down(int repeat, bool solid, bool valve, id pipe_id, int power, object connect_to)
{
	var remaining = ExtendPipeLine(PIPE_Down, PIPE_Up, repeat, solid, valve, pipe_id, power, connect_to);
	if (remaining > 0)
	{
		return connect_to->~Down(remaining, solid, valve, pipe_id, power);
	}
	else
	{
		return connect_to;
	}
}

func Valve(bool open)
{
	valve = CreateObject(VALV, 0, 11, GetOwner());
	valve->SetOpen(open);
	return this;
}

func Solid(bool desolidate)
{
	if (desolidate)
	{
		DrawAsBackground();
		SetSolidMask();
	}
	else
	{
		DrawAsForeground();
		// Delayed in order to account for possible changes
		ScheduleCall(this, this.Consolidate, 1);
	}
	return this;
}

func Consolidate()
{
	var index = GetPipeIndex();

	SetSolidMask(index % 4 * 50, index / 4 * 50, 50, 50);
}

func ConnectTo(object connect_to, int dir)
{
	
	// allocate local
	if (dir == PIPE_Left)
	{
		pipe_left = connect_to;
	}
	else if (dir == PIPE_Right)
	{
		pipe_right = connect_to;
	}
	else if (dir == PIPE_Up)
	{
		pipe_up = connect_to;
	}
	else if (dir == PIPE_Down)
	{
		pipe_down = connect_to;
	}
	else
	{
		FatalError(Format("Cannot connect_to in direction %d", dir));
	}
	
	UpdateGraphics();
}


func UpdateGraphics()
{
	// update graphic
	var index = GetPipeIndex();
	
	SetPhase(index % 4);
	SetDir(index / 4);
}

func CreatePipe(int dir, id pipe_id)
{
	var x = 0, y = 0;
	
	if (dir == PIPE_Left)
	{
		x -= GetDefWidth();
	}
	if (dir == PIPE_Right)
	{
		x += GetDefWidth();
	}
	if (dir == PIPE_Up)
	{
		y -= GetDefHeight();
	}
	if (dir == PIPE_Down)
	{
		y += GetDefHeight();
	}
	
	x = x * GetCon() / 100;
	y = y * GetCon() / 100;

	var pipe = CreateObject(pipe_id, 50, 50, GetOwner());
	pipe->DoCon(GetCon() - 100);
	pipe->SetCategory(GetCategory());
	
	pipe->SetPosition(GetX() + x, GetY() + y);
	return pipe;
}

func ChangePower(int power)
{
	this.power = power;
	return this;
}

/* Liquids */

func LiquidCheck()
{
	ScheduleCall(this, this.LiquidCheck, 4);

	if (!GBackLiquid())
	{
		has_liquid = false;
		return;
	}

	if (drains[0] == 0)
	{
		return NewLiquidCheck();
	}
	
	if (!power) return;
	
	var mat;
	for (var i = 0; i < power; i++)
	{
		mat = ExtractLiquid(0, 0);
		drains[drain_index]->CastLiquid(mat, 15);
	}
	
	if (!Random(4))
	{
		Bubble();
	}
	
	drain_index++;
	if (drains[drain_index] == 0)
	{
		drain_index = 0;
	}
}

func CastLiquid(int iMat, int iStr)
{
	var x, y;
	if (pipe_left || pipe_right)
	{
		x = 0;
		y = RandomX(-5, 5);
	}
	if (pipe_up || pipe_down)
	{
		x = RandomX(-5, 5);
		y = 0;
	}
	
	// TODO: this is already in the barrel, take it from there CastPXSX(MaterialName(iMat), 1, iStr, x,y, GetLiquidAngle(), 15);
}

func NewLiquidCheck()
{
	if (!has_liquid && GBackLiquid())
	{
		has_liquid = true;
		UpdateEfflux();
	}
}

func GetLiquidAngle()
{
	if (pipe_left)  return 0;
	if (pipe_right) return 180;
	if (pipe_down)  return 270;
	if (pipe_up)    return 90;
	
	FatalError("Asking liquid angle without connection");
}

/* Public interface */

func UpdateEfflux()
{
	if (!GBackLiquid())
	{
		return;
	}
	
	drains = [];
	
	if (pipe_left)
	{
		pipe_left->UpdateSystem(this);
	}
	if (pipe_right)
	{
		pipe_right->UpdateSystem(this);
	}
	if (pipe_down)
	{
		pipe_down->UpdateSystem(this);
	}
	if (pipe_up)
	{
		pipe_up->UpdateSystem(this);
	}
}

func UpdateSystem(object start, int from, int pump)
{
	// check only once per frame
	if (checked) return;
	
	if (valve)
		if (!(valve->~Status()))
			return;
	
	if (pump == 1 && IsEnd())
	{
		start->~NewConflux(this);
		return;
	}
	if (pump == 2 && IsEnd())
	{
		start->~NewEfflux(this);
		return;
	}
	
	if (IsEnd() && !GBackLiquid())
	{
		start->NewEfflux(this);
		return;
	}
	if (pipe_left && from != PIPE_Left)
		pipe_left->UpdateSystem(start, PIPE_Right, pump);
	if (pipe_right && from != PIPE_Right)
		pipe_right->UpdateSystem(start, PIPE_Left, pump);
	if (pipe_down && from != PIPE_Down)
		pipe_down->UpdateSystem(start, PIPE_Up, pump);
	if (pump || start->GetY() <= GetY())
	{
		if (pipe_up && from != PIPE_Up)
			pipe_up->UpdateSystem(start, PIPE_Down, pump);
	}

	checked = true;
	ScheduleCall(this, this.SystemUpdateAllow, 1);
}

func SystemUpdateAllow()
{
	checked = false;
}

func NewEfflux(object next)
{
	PushBack(drains, next);
}

func IsEnd()
{
	return (GetDir() == 0 && Inside(GetPhase(), 1, 2))
        || (GetDir() == 1 && GetPhase() == 0)
        || (GetDir() == 2 && GetPhase() == 0);
}

func DrawAsForeground()
{
	SetClrModulation(RGB());
}

func DrawAsBackground()
{
	SetClrModulation(RGB(180, 180, 180));
}

func GetPipeIndex()
{
	return !!pipe_left  * PIPE_Left
	     | !!pipe_right * PIPE_Right
	     | !!pipe_up    * PIPE_Up
	     | !!pipe_down  * PIPE_Down;
}

/* Global */

// Updates all drains in all pipe ends, and controls pumps
global func UpdatePipesystem()
{
	var pipe, pump;
	for (pump in FindObjects(Find_ID(PMP2))) 
	{
		pump->~UpdateEfflux();
	}
	for (pipe in FindObjects(Find_ID(PIPL))) 
	{
		if (pipe->~IsEnd())
			pipe->~UpdateEfflux();
	}
}

/* Serialisierung */

func Serialize(array extra) // TODO: implement proper saving mechanism
{
	if (pipe_left)
		extra[GetLength(extra)] = ["ConnectTo(Object(%d), PIPE_Left)", pipe_left];
	if (pipe_right)
		extra[GetLength(extra)] = ["ConnectTo(Object(%d), PIPE_Right)", pipe_right];
	if (pipe_up)
		extra[GetLength(extra)] = ["ConnectTo(Object(%d), PIPE_Up)", pipe_up];
	if (pipe_down)
		extra[GetLength(extra)] = ["ConnectTo(Object(%d), PIPE_Down)", pipe_down];
	if (GetClrModulation() == RGB())
		extra[GetLength(extra)] = "Solid()";
	if (power != 1)
		extra[GetLength(extra)] = Format("ChangePower(%d)", power);
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
Pipe = {
	Prototype = Action,
	Name = "Pipe",
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
