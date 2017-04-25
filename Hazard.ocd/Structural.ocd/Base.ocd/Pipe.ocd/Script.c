/*-- Pipe --*/


local left, right, up, down, valve; // connections, valve
local efflux, temp; // drain, chache
local noliquid, power; // is in liquid?, amount of liquid output
local checked; // cache for UpdatePipesystem

static const PIPE_Left = 1;
static const PIPE_Right = 2;
static const PIPE_Up = 4;
static const PIPE_Down = 8;

func Initialize()
{
	SetAction("Pipe");
	DrawAsBackground();
	efflux = [];
	
	if (!GBackLiquid())
	{
		noliquid = true;
	}
	
	// default output
	power = 1;
}

// Allow connections between valid pipelines (callbacks) only

func Left(int iRepeat, bool solid, bool valve, id pipeId, int iPower, object connect)
{
	iRepeat = iRepeat ?? 1;
	pipeId = pipeId ?? PIPL;
	connect = connect ?? CreatePipe(PIPE_Left, pipeId);
	iPower = iPower ?? 1;

	ConnectTo(connect, PIPE_Left);
	connect->ConnectTo(this, PIPE_Right);
	connect->~ChangePower(iPower);
	if (solid)
	{
		connect->~Solid();
	}
	if (valve)
	{
		connect->~Valve();
	}
	
	iRepeat -= 1;
	if (iRepeat > 0)
	{
		return connect->~Left(iRepeat, solid, valve, pipeId, iPower);
	}
	else
	{
		return connect;
	}
}

func Right(int iRepeat, bool solid, bool valve, id pipeId, int iPower, object connect)
{
	if (!iRepeat)
		iRepeat = 1;
	if (!pipeId)
		pipeId = PIPL;
	if (!connect)
		connect = CreatePipe(PIPE_Right, pipeId);
	if (!iPower)
		iPower = 1;
	ConnectTo(connect, PIPE_Right);
	connect->ConnectTo(this, PIPE_Left);
	connect->~ChangePower(iPower);
	if (solid)
		connect->~Solid();
	if (valve)
		connect->~Valve();
	
	if (iRepeat - 1)
		return connect->~Right(iRepeat - 1, solid, valve, pipeId, iPower);
	return connect;
}

func Up(int iRepeat, bool solid, bool valve, id pipeId, int iPower, object connect)
{
	if (!iRepeat)
		iRepeat = 1;
	if (!pipeId)
		pipeId = PIPL;
	if (!connect)
		connect = CreatePipe(PIPE_Up, pipeId);
	if (!iPower)
		iPower = 1;
	ConnectTo(connect, PIPE_Up);
	connect->ConnectTo(this, PIPE_Down);
	connect->~ChangePower(iPower);
	if (solid)
		connect->~Solid();
	if (valve)
		connect->~Valve();
	
	if (iRepeat - 1)
		return connect->~Up(iRepeat - 1, solid, valve, pipeId, iPower);
	return connect;
}

func Down(int iRepeat, bool solid, bool valve, id pipeId, int iPower, object connect)
{
	if (!iRepeat)
		iRepeat = 1;
	if (!pipeId)
		pipeId = PIPL;
	if (!connect)
		connect = CreatePipe(PIPE_Down, pipeId);
	if (!iPower)
		iPower = 1;
	ConnectTo(connect, PIPE_Down);
	connect->ConnectTo(this, PIPE_Up);
	connect->~ChangePower(iPower);
	if (solid)
		connect->~Solid();
	if (valve)
		connect->~Valve();
	
	if (iRepeat - 1)
		return connect->~Down(iRepeat - 1, solid, valve, pipeId, iPower);
	return connect;
}

func Valve(bool open)
{
	valve = CreateObject(VALV, 0, 11, GetOwner());
	valve.open = open;
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

func ConnectTo(object connect, int dir)
{
	
	// allocate local
	if (dir == PIPE_Left)
	{
		left = connect;
	}
	else if (dir == PIPE_Right)
	{
		right = connect;
	}
	else if (dir == PIPE_Up)
	{
		up = connect;
	}
	else if (dir == PIPE_Down)
	{
		down = connect;
	}
	else
	{
		FatalError(Format("Cannot connect in direction %d", dir));
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

func CreatePipe(int dir, id pipeId)
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

	var pipe = CreateObject(pipeId, 50, 50, GetOwner());
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
	if (!GBackLiquid())
	{
		noliquid = true;
		return;
	}

	if (efflux[0] == 0)
	{
		return NewLiquidCheck();
	}
	
	if (!power) return;
	
	var mat;
	for (var i = 0; i < power; i++)
	{
		mat = ExtractLiquid(0, 0);
		efflux[temp]->CastLiquid(mat, 15);
	}
	
	if (!Random(4))
	{
		Bubble();
	}
	
	temp++;
	if (efflux[temp] == 0)
	{
		temp = 0;
	}
}

func CastLiquid(int iMat, int iStr)
{
	var x, y;
	if (left || right)
	{
		x = 0;
		y = RandomX(-5, 5);
	}
	if (up || down)
	{
		x = RandomX(-5, 5);
		y = 0;
	}
	
	// TODO: this is already in the barrel, take it from there CastPXSX(MaterialName(iMat), 1, iStr, x,y, GetLiquidAngle(), 15);
}

func NewLiquidCheck()
{
	if (!noliquid)
		return;
	
	if (GBackLiquid())
	{
		noliquid = false;
		UpdateEfflux();
	}
}

func GetLiquidAngle()
{
	if (left)  return 0;
	if (right) return 180;
	if (down)  return 270;
	if (up)    return 90;
	
	FatalError("Asking liquid angle without connection");
}

/* �ffentliches */

func UpdateEfflux()
{
	if (!GBackLiquid())
	{
		return;
	}
	
	efflux = [];
	
	if (left)
	{
		left->UpdateSystem(this);
	}
	if (right)
	{
		right->UpdateSystem(this);
	}
	if (down)
	{
		down->UpdateSystem(this);
	}
	if (up)
	{
		up->UpdateSystem(this);
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
	if (left && from != PIPE_Left)
		left->UpdateSystem(start, PIPE_Right, pump);
	if (right && from != PIPE_Right)
		right->UpdateSystem(start, PIPE_Left, pump);
	if (down && from != PIPE_Down)
		down->UpdateSystem(start, PIPE_Up, pump);
	if (pump || start->GetY() <= GetY())
	{
		if (up && from != PIPE_Up)
			up->UpdateSystem(start, PIPE_Down, pump);
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
	PushBack(efflux, next);
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
	return !!left  * PIPE_Left
	     | !!right * PIPE_Right
	     | !!up    * PIPE_Up
	     | !!down  * PIPE_Down;
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
	if (left)
		extra[GetLength(extra)] = ["ConnectTo(Object(%d), PIPE_Left)", left];
	if (right)
		extra[GetLength(extra)] = ["ConnectTo(Object(%d), PIPE_Right)", right];
	if (up)
		extra[GetLength(extra)] = ["ConnectTo(Object(%d), PIPE_Up)", up];
	if (down)
		extra[GetLength(extra)] = ["ConnectTo(Object(%d), PIPE_Down)", down];
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
