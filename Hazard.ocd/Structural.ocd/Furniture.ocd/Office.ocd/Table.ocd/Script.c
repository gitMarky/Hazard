
func IsProjectileTarget()
{
	return Random(3);
}

func Damage()
{
	Sound("Hits::Materials::Wood::WoodHit?");
	// Kaputtgehen
	if (Inside(GetDamage(), 25, 34))
	{
		Sound("CrateCrack"); // TODO
		RemoveObject();
	}
}

func IsCraneGrabable()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 35;
local BurnTo = TABB;
