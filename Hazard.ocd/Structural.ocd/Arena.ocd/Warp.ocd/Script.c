local destination_x, destination_y;

func Initialize()
{
	SetAction("Warp");
	CreateEffect(CheckWarp, 100, 2);
}

func SetDestination(int x, int y)
{
	destination_x = x;
	destination_y = y;
}

local CheckWarp = new Effect
{
	Timer = func()
	{
		for (var obj in this.Target->FindObjects
		(
			Find_Distance(17),
			Find_NoContainer(),
			Find_Not(Find_Func("NoWarp")),
			Find_Or(Find_Category(C4D_Living), Find_Category(C4D_Object), Find_Category(C4D_Vehicle))
		))
		{
			this.Target->Warp(obj);
		}
	},
};

func Warp(object target)
{
	var xv = target->GetXDir();
	var yv = target->GetYDir();
	target->SetPosition(destination_x, destination_y);
	target->SetXDir(xv);
	target->SetYDir(yv);
	target->~AddSpawnEffect(RGBa(0, 200, 255, 255));
}


func Serialize(array extra) // TODO: implement saving object
{
	extra[GetLength(extra)] = Format("SetDestination(%d, %d)", destination_x, destination_y);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = 
{
	Warp = 
	{
		Prototype = Action,
		Name = "Warp",
		Directions = 2,
		FlipDir = 1,
		Length = 10,
		Delay = 2,
		X = 0,
		Y = 0,
		Wdt = 36,
		Hgt = 36,
		NextAction = "Warp"
	}
};
