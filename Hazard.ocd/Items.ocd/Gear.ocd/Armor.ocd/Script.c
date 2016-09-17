#include Gear_Basic

func GetGearType(){	return GEAR_Armor;}
func IsEquipment(){	return true;}
func Hit(){	Sound("Hits::Materials::Metal::DullMetalHit?");}

/* Callbacks */

func GearEffect(object user)
{
	user->~SetHazardArmorSkin();
	Sound("Objects::Connect");
}

func GearEffectReset(object user)
{
	user->~SetHazardSkin();
	Sound("Objects::Connect");
}


/* Damage reduction */

/* TODO: Damage system
func OnClonkDmg(int amount, int type, object user)
{
	if (!user) return;
	if (type == DMG_Melee)		return 60;
	if (type == DMG_Projectile)	return 40;
	if (type == DMG_Fire)		return 0;
	if (type == DMG_Explosion)	return 20;
	if (type == DMG_Energy)		return -20;
	if (type == DMG_Bio)		return 25;
}
*/

/* Use per context menu of the hazard clonk */

// TODO: Nightvision interaction

//func ConDesc()
//{
//	if (pNightVision)
//		return "$CtxNightVisionOff$";
//	return "$CtxNightVisionOn$";
//}
//
//func ConUseable()
//{
//	// without darkness, there is no need for nightvision
//	if (IsDark())
//		return true;
//}
//
//func ConUse(object pHazard)
//{
//	
//	// turn on
//	if (!pNightVision)
//	{
//		pNightVision = AddLight(1200, RGBa(50, 255, 50, 65), pHazard);
//		if (!pNightVision)
//			return;
//		pNightVision->SetVisibility(VIS_Owner);
//	}
//	else
//	{
//		RemoveObject(pNightVision);
//	}
//	
//
//	// Attentioooon: Here comes the effect!
//	// ..
//	// .....!
//	Sound("Click"); // Ba-bum.
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
