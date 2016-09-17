#include Gear_Basic
#include Upgrade_Basic

func ControlUse(object user, int x, int y)
{
	var upgrade = GetUpgradeable();
	if (GetLength(upgrade))
	{
		CreateUpgradeMenu(user);
		return true;
	}
	return ActivateGear(user);
}

/* Status */

func GetGearType()
{
	return GEAR_Shield;
}

func Hit()
{
	Sound("Hits::Material::Metal::LightMetalHit?");
}

func IsEquipment()
{
	return true;
}

/* Callbacks */

func GearEffect(object user)
{
	var fx = AddEffect("HazardShield", user, 99, 3, nil, HSHD);
	fx.size = 3 * Distance(0, 0, user->GetDefWidth(), user->GetDefHeight()) / 2;
	Sound("Objects::Connect");
}

func GearEffectReset(object user)
{
	if (GetEffect("HazardShield", user))
		return RemoveEffect("HazardShield", user);
	Sound("Objects::Connect");
}

func FxHazardShieldTimer(object target, proplist fx, int time)
{
	var boom = fx.phase == 2;
	var alpha = 40;
	if (boom) alpha = 240;
	target->CreateParticle("HazardShield", 0, 0, 0, 0, 40,
	{
		Size = fx.size ?? 30 + (boom * 30),
		BlitMode = GFX_BLIT_Additive,
		Alpha = PV_Linear(alpha, 0),
		Attach = ATTACH_Front | ATTACH_MoveRelative,
		Phase = PV_Random(0, 2),
		Rotation = PV_Random(0, 360),
	}, 1);
	
	if (fx.phase > 0) fx.phase -= 1;
}

func FxHazardShieldBulletHit(object target, proplist fx)
{
	if (fx.phase == 0) fx.phase = 2;
	Sound("Item::Shield");
}

func OnClonkDmg(int amount, int type)
{
	//Energy
	// TODO: if (type == DMG_Energy) return 60;
}

func OnClonkHit(int amount, int type, object user)
{
	// energy only
	//if (type != DMG_Energy) return 0;
		
	// shield flickers
	EffectCall(user, GetEffect("HazardShield", user), "BulletHit");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = true;
