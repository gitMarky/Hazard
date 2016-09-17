local slide, ydir, load;

func Initialize()
{
	AddLightAmbience(45);
}

func SetSlide(object slide)
{
	this.slide = slide;
	SetAction("NoLoad");
	AddEffect("Movement", this, 99, 2, this);
}

func Down()
{
	if (ydir < 2)
		ydir += 2;
}

func Up()
{
	if (ydir > -2)
		ydir -= 2;
}

func Stop()
{
	ydir = 0;
}

/* Motion */

func FxMovementTimer()
{
	var y = BoundBy(GetY() + ydir, slide->GetY() + 10, LandscapeHeight());
	if (CheckSolid(y))
	{
		y = GetY();
		ydir = 0;
	}
	SetPosition(slide->GetX(), y);
}

func CheckSolid(int y)
{
	if (!load) return GBackSolid(0, y - GetY());
	y -= GetY();
	var ypos = load->GetY() + load->GetObjHeight() + load->GetDefOffset(0, 1) + y;
	if (y < 0)
		ypos = load->GetY() + load->GetDefOffset(0, 1) + y;
	return GBackSolid(0, ypos - GetY());
}


/* Grab objects */

func Grab()
{
	// Got one already?
	if (GetAction() == "Load") return Ungrab();

	var targets = FindObjects(Find_Or(Find_AtPoint(0, 0), Find_AtPoint(0, 20)),
							  Find_NoContainer(),
							  Find_Func("IsCraneGrabable"),
							  Find_Exclude(this));
					 
	for (var target in targets) 
		if (target->GetProcedure() != "FLOAT")
			if (!target->~NoCrane())
			{
				load = target;
				SetAction("Load");
				Sound("Grapple"); // TODO
				AddEffect("Loading", load, 99, 1, this, nil, load->GetX() - GetX(), load->GetY() - GetY());
				return true;
			}
}

func FxLoadingStart(object target, proplist fx, int temp, int x, int y)
{
	if (temp) return;
	fx.x = x;
	fx.y = y;
}

func FxLoadingTimer(object target, proplist fx)
{
	target->SetPosition(GetX() + fx.x, GetY() + fx.y);
	target->SetXDir(0);
	target->SetYDir(0);
}

func Loading()
{
	if (!load) return SetAction("NoLoad");
}

func Ungrab()
{
	if (!load) return;

	SetAction("NoLoad");
	if (GetEffect("Loading", load))
		RemoveEffect("Loading", load);
	load = nil;
	Sound("Grapple"); // TODO: sound
}

/* Serialisierung */

func NoSerialize() // TODO: Save object
{
	return !false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
NoLoad = {
	Prototype = Action,
	Name = "NoLoad",
	Procedure = DFA_FLOAT,
	Delay = 1,
	FacetBase = 1,
	Speed = 100,
	Accel = 16,
	Decel = 16,	
	NextAction = "NoLoad",
},

Load = {
	Prototype = Action,
	Name = "Load",
	Procedure = DFA_FLOAT,
	Delay = 1,
	FacetBase = 1,
	Speed = 100,
	Accel = 12,
	Decel = 12,
	NextAction = "Load",
	EndCall = "Loading",
},

};
