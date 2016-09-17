func Initialize()
{
	SetAction("Walk");
	SetComDir(COMD_Left);
}

func ContactLeft()
{
	SetComDir(COMD_Right);
}

func ContactRight()
{
	SetComDir(COMD_Left);
}

func Walking()
{
	CreateLEDEffect(RGB(255, 50, 50), RandomX(-2, 2), -2, RandomX(1, 3), 20);
	
	if (!Random(30)) Sound("Structural::Wheeng");
	
	if (Random(2)) SetComDir(COMD_Left);
	else SetComDir(COMD_Right);
}

func IsProjectileTarget(){	return true;}
func IsMachine(){	return true;}
func CanBeLaserRecycled(){	return 2;}

func EMPShock()
{
	Detonate();
}

func Hit3()
{
	Detonate();
}

func Damage()
{
	Detonate();
}

local destroyed;

func Detonate()
{
	if (!destroyed)
	{
		destroyed = true;
		Explode(10 + Random(5));
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local ContactCalls = true;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Walk = {
	Prototype = Action,
	Name = "Walk",
	Procedure = DFA_WALK,
	Directions = 2,
	FlipDir = 1,
	Delay = 300,
	Speed = 100,
	Accel = 16,
	Decel = 48,
	FacetBase = 1,
	NextAction = "Walk",
	EndCall = "Walking",
},

Jump = {
	Prototype = Action,
	Name = "Jump",
	Procedure = DFA_FLIGHT,
	Directions = 2,
	FlipDir = 1,
	Delay = 1,
	Speed = 10,
	Accel = 16,
	FacetBase = 1,
	NextAction = "Hold",
},

};
