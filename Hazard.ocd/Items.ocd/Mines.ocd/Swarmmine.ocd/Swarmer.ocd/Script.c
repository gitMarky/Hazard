#include MINE

local xdir, ydir;

func Activate()
{
	var speed = RandomX(0, 50);
	var angle = Random(360);
	xdir = +Sin(angle, speed);
	ydir = -Cos(angle, speed);
	
	SetSpeed(xdir, ydir);
	SetAction("Fly");
	
	var tmp = CreateObject(Helper_MineFlag, 0, 0, GetController());
	tmp->Set(this);
	tmp->SetR(Random(360));
	tmp->SetCon(70);
}

func DecreaseSpeed()
{
	xdir += BoundBy(-xdir, -1, 1);
	ydir += BoundBy(-ydir, -1, 1);
	SetSpeed(xdir, ydir);
	if (!(GetActTime() % 20)) Warning();
	Check();
}

func Triggered(){	Explode(15);}

func MaxDamage(){	return 5;}
func MineExplosionRadius(){	return 16;}
func MineExplosionDelay(){	return 5;}
func WarningDist(){ return 0;}

func IsEquipment(){	return false;}

local Collectible = false;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Fly = {
	Prototype = Action,
	Name = "Fly",
	Procedure = DFA_FLIGHT,
	Delay = 1,
	FacetBase = 1,
	NextAction = "Fly",
	EndCall = "DecreaseSpeed",
},

};
