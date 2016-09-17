
func ControlUse(object user, int x, int y)
{
	return Activate(user);
}

func Activate(object user)
{
	if (user->GetPhysicalEnergy() >= user.MaxEnergy) return false;
	if (GetEffect("*Heal*", user)) return false;

	var fx = user->Heal(HealAmount(), HealRate());
	Decorate(user, fx);
	Sound("Item::Medi");
	RemoveObject();
	return true;
}

func HealRate(){	return 7;}
func HealAmount(){	return 100;}

func IsEquipment(){	return true;}

// TODO: check if the return value is correct; at the moment it returns 'true' regardless of the outcome.
// maybe it should return true only if it was actually handled
func AI_Inventory(object user)
{
	// use if you have less than 2/3 of your energy
	if (user->GetPhysicalEnergy() < 2 * user.MaxEnergy / 3)
		// delayed use
		ScheduleCall(this, this.Activate, 1, 0, user);
	// handled!
	return true;
}

func Decorate(object user, proplist fx)
{
}

local Collectible = true;
