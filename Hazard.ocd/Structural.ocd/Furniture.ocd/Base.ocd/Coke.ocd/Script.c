local broken;

public func EMPShock()
{
	Break();
}

public func Incineration()
{
	Break();
}

func Break()
{
	if(broken) return false;
	broken = true;
	// many colourful cans!
	ScheduleCall(this, this.CastTin, 2, RandomX(7, 14));
	ScheduleCall(this, this.CastSparks, 3, 15);
	Sound("Structural::Furniture::CokeCrash");
	//Sound("FreezerLoop", 0,0,0,0, -1);
	SetClrModulation(RGB(100, 100, 100));
	return true;
}

func CastTin()
{
	var tin =
	{
		Size = 6,
		Phase = PV_Random(0, 2),
		Alpha = PV_KeyFrames(0, 0, 255, 900, 255, 1000, 0),
		CollisionVertex = 500,
		OnCollision = PC_Bounce(100),
		ForceY = PV_Gravity(100),
		Rotation = PV_Random(-10, 10),
	};

	CreateParticle("Tin", -5, 12, PV_Random(-10, 10), -1, PV_Random(30, 90), Particles_Colored(tin, TinColor()));
}

func CastSparks()
{
	CreateSparksEffect(RandomX(1, 3), RGB(255, 255, 255), RandomX(-10, 10), RandomX(-15, 15));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 100;
local BurnTo = CLVB;

public func IsMachine() { return true; }
public func TinColor() { return RGB(255, 25, 25); }
public func IsCraneGrabable() { return true; }
public func CanBeRecycled() { return 2; } // TODO: find out what this is good for
