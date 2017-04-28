/* Waypoint (Dummy) */


/* Global */

static WAYP_visibleWaypoints;

global func CreateWP(int x, int y)
{
	var WP = CreateObject(WAYP, AbsX(x), AbsY(y), NO_OWNER);
	WP->SetAction("Vis");
	return WP;
}

// Flags cannot be combined
static const Path_MoveTo = 0; // ;)
static const Path_Jump = 1;
static const Path_Backflip = 2;
static const Path_Lift = 3;

// Directions for launching the jet pack
static const Jetpack_Left = 1;
static const Jetpack_UpLeft = 2;
static const Jetpack_UpRight = 3;
static const Jetpack_Right = 4;

static const WAYP_PathErr = "Path %d does not exist.";

local path_targets;

func Initialize()
{
	path_targets = [];
}


func AddPath(object target, int flag, int dir, int jetpdelay, int jetpflag, bool fReconnect)
{
	// save info

	var path_data = {};
	path_data.target = target;
	path_data.dir = dir;
	path_data.jetpdelay = jetpdelay;
	path_data.jetpflag = jetpflag;
	
	var path_id = GetLength(path_targets);
	PushBack(path_targets, path_data);

	// dummy

	DebugPath->Create(this, target, flag, jetpdelay, path_id, dir);
	
	if (fReconnect)
	{
		target->AddPath(this, flag, dir * (-1), jetpdelay, jetpflag, false);
	}
	
	return 0;
}

func SetArriveCommand(int pId, int iNo, string command, object pTarget, int iX, int iY, object pTarget2, Data)
{
	// dummy
}

func RemovePath(int pId)
{
	// dummy
}

func GetPathTarget(int index)
{
	return path_targets[index].target;
}

public func GetPathDir(int index)
{
	return path_targets[index].dir;
}

public func GetPathFlag(int index)
{
	return path_targets[index].flag;
}

public func GetPathJetpack(int index)
{
	return path_targets[index].jetpdelay;
}

public func GetPathJetpackFlag(int index)
{
	return path_targets[index].jetpflag;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Plane = 10000;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Vis = {
	Prototype = Action,
	Name = "Vis",
	Procedure = DFA_NONE,
	Length = 1,
	X = 16,
	Y = 0,
	Wdt = 16,
	Hgt = 16,
	NextAction = "Hold",
},

};

local Visibility = VIS_Editor;
