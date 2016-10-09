local crane, clamp, xdir;

func Initialize()
{
	clamp = CreateObject(CLMP, 0, 25, GetOwner());
	clamp->SetSlide(this);
}

func SetCrane(object crane)
{
	this.crane = crane;
	SetAction("Sliding", clamp);
	Adjust();
}

func Adjust()
{
	var x = Back2Crane();
	var y = crane->GetY() + 5;
	
	SetPosition(x, y);
}

func InRange() //TODO: probably unused
{
	return Inside(GetX(), crane->~LeftX() + 10, crane->~RightX() - 10);
}

func Back2Crane()
{
	return BoundBy(GetX(), crane->~LeftX() + 10, crane->~RightX() - 10);
}

/* Konsolensteuerung */

func ConsoleControl(int i)
{
	if (i == 1)	return "$ControlCrane$";
}

func ConsoleControlled(int i, int user_number)
{
	var user = Object(user_number);
	if (!user) return;
	// Wird bereits kontrolliert?
	if (GetEffect("Controller", this))
	{
		user->Sound("UI::Error", nil, nil, user->GetOwner() + 1);
		return ;
	}
	// Steuerung übernehmen
	AddEffect("Controller", this, 99, 2, this, nil, user->GetOwner(), user);
	SetCursor(user->GetOwner(), this, true);
}

func FxControllerStart(object target, proplist controller, int temp, int owner, object clonk)
{
	if (temp)
		return;
	controller.owner = owner;
	controller.user = clonk;
}

func FxControllerTimer(object target, proplist controller, int time)
{
	if (GetCursor(controller.owner) != target || !controller.user)
	{
		target->Stop();
		return FX_Execute_Kill;
	}
	if (controller.user->GetAction() != "Push" || controller.user->GetActionTarget()->~IsConsole() != true)
	{
		target->Stop();
		SetCursor(controller.owner, controller.user);
		return FX_Execute_Kill;
	}
	target->~CheckMovement();
}

func CrewSelection(bool deselect, bool cursoronly)
{
	if (deselect)
	{
		RemoveEffect("Controller2", this);
		Stop();
	}
	else
	{
		AddEffect("Controller2", this, 99, 2, this, nil, GetController(), this);
		SetPlrView(GetController(), clamp);
	}
}

func FxController2Effect(string neweffect)
{
	if (neweffect == "Controller2")
		return -1;
}

func FxController2Timer()
{
	CheckMovement();
}

/* Control */

func ControlLeft(object user)
{
	if (xdir > -2)
		xdir -= 2;
	
	SetPlrView(user->GetController(), clamp);
}

func ControlRight(object user)
{
	if (xdir < 2)
		xdir += 2;
	
	SetPlrView(user->GetController(), clamp);
}

func ControlUp(object user)
{
	clamp->Up();
	
	SetPlrView(user->GetController(), clamp);
}

func ControlDown(object user)
{
	clamp->Down();
	
	SetPlrView(user->GetController(), clamp);
}

func ControlThrow(object user)
{
	clamp->Grab();
	
	SetPlrView(user->GetController(), clamp);
}

func ControlDig(object user)
{
	xdir = 0;
	clamp->Stop();
	
	SetPlrView(user->GetController(), clamp);
}

func CheckMovement()
{
	// out of range?
	if (!InRange())
	{
		Adjust();
		xdir = 0;
	}
	// clamp hits something?
	if (clamp && clamp->GBackSolid(xdir * 3, 0))
	{
		xdir = 0;
	}
	// sounds
	ElevatorSound(xdir != 0);
	SetPosition(GetX() + xdir, GetY());
}

func CheckY()
{
	if (!crane) return RemoveObject();
	if (GetY() != GetY(crane) + 10) Adjust();
}

func Stop()
{
	xdir = 0;
	ElevatorSound(false);
	clamp.ydir = 0;
}

// Maus macht mich zZ kaputt
func ControlCommand()
{
	return true;
}

/* Serialisierung */

func NoSerialize() // TODO: Save object
{
	return true;
}

func Reconfigure(int dx, int dy, object load)
{
	SetPosition(GetX() + dx, GetY());
	clamp->SetPosition(clamp->GetX(), clamp->GetY() + dy);
	if (load)
	{
		clamp.load = load;
		clamp->SetAction("Load");
		clamp->AddEffect("Loading", load, 99, 1, clamp, nil, load->GetX() - clamp->GetX(), load->GetY() - clamp->GetY());
	}
}

func ElevatorSound(play)
{
	if (play)
		Sound("Structures::Elevator::Moving", false, 50, nil, 1);
	else
		Sound("Structures::Elevator::Moving", false, 50, nil, -1);
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Sliding = {
	Prototype = Action,
	Name = "Sliding",
	Procedure = DFA_FLOAT,
	X = 37,
	Y = 0,
	Wdt = 21,
	Hgt = 4,
	OffX = 8,
	OffY = 16,
	FacetBase = 1,
	FacetTargetStretch = 1,
	NextAction = "Sliding",
},

};
