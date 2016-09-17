#include MINE

func OnActive()
{
	SetVertex(1, 1, 0, 2);
	SetVertex(2, 1, 0, 2);

	var speed = 30;
	var xdir = +Sin(GetR(), speed);
	var ydir = -Cos(GetR(), speed);

	SetAction("Fly"); // bounce
	SetSpeed(xdir, ydir);
	SetRDir(RandomX(-50, 50));
	ScheduleCall(this, this.Swarm, this->MineExplosionDelay());
}

func Swarm()
{
	// split into smaller mines
	for (var i = 0, swarmy; i < 10; i++)
	{
		swarmy = CreateObject(SWRM, 0, 0, GetOwner());
		swarmy->Activate();
	}
	CreateSparksEffect(10, RGB(255, 125, 0));
	RemoveObject();
}

func Triggered()
{
	Explode(10);
}

func MineExplosionDelay(){	return 10;}
func IsUpgradeable(id upgrade){ return false;}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Activate = {
	Prototype = Action,
	Name = "Activate",
	Procedure = DFA_NONE,
	Length = 5,
	Delay = 20,
	FacetBase = 1,
	EndCall = "OnActive",
	PhaseCall = "Warning",
	NextAction = "Fly",
},

Fly = {
	Prototype = Action,
	Name = "Fly",
	Procedure = DFA_FLIGHT,
	Length = 5,
	Delay = 15,
	FacetBase = 1,
	NextAction = "Fly",
	PhaseCall = "Warning",
},

};
