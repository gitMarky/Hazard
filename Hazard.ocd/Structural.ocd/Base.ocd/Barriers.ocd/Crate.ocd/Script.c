public func IsProjectileTarget() { return !Random(5); }
public func IsCraneGrabable() { return true; }

local damaged;

func Damage()
{
 	if (GetDamage() > 20 && !damaged)
	{
		damaged = true;
		var speed = 50;
    	CreateParticle("CrateSplinter", 0, 0, PV_Random(-speed, speed), PV_Random(-speed, speed), PV_Random(200, 255),
    	{
    		Prototype = Particles_WoodChip(),
    		DampingX = 1000, DampingY = 1000,
    	}, 5);
    	Sound("Structural::Furniture::CrateCrack");
    	while (Contents())
    		Contents()->Exit(, 0, 0, Random(360), RandomX(-5, 5), RandomX(-5, 5), RandomX(-15, 15));
    	RemoveObject();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
