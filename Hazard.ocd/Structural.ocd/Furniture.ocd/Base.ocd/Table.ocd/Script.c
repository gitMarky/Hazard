
func IsProjectileTarget()
{
	return Inside(Abs(GetR()), 80, 100) || Inside(Abs(GetR()), 260, 280);
}

/* TODO: Damage system
func OnDmg(int iDmg, int iType)
{
	if (iType == DMG_Fire)
	{
		return -100;
	}
}

func OnHit(int iDmg, int iType, object pFrom)
{
	if (iType == DMG_Fire)
	{
		Incinerate();
	}
}

func ControlDigDouble(object pByObj)
{
	SetR(85 * (pByObj->GetR() * 2 - 1));
	SetPosition(GetX(), GetY() - 8);
}

func Damage()
{
	Sound("WoodHit*");
	// Kaputtgehen
	if (Inside(GetDamage(), 25, 34))
	{
		Sound("CrateCrack");
		RemoveObject();
	}
}
*/

func IsCraneGrabable(){	return true;}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 35;
local BurnTo = TABB;

