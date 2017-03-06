#appendto Library_ClonkControl

/* Main control function */
public func ObjectControl(int plr, int ctrl, int x, int y, int strength, bool repeat, int status)
{
	if (!this) return false;

	if (_inherited(plr, ctrl, x, y, strength, repeat, status))
	{
		return true;
	}

	var weapon = GetHandItem(0);
	if (weapon)
	{	
		if (ctrl == CON_WeaponFiremode)
		{
			return ObjectControlToggleFiremode(weapon);
		}
		else if (ctrl == CON_WeaponReload)
		{
			return ObjectControlReloadWeapon(weapon);
		}
	}

	return false;
}


private func ObjectControlToggleFiremode(object weapon)
{
	if (!weapon->~IsHazardWeapon())
	{
		return false;
	}
	
	weapon->~ToggleFiremode();
	return true;
}

private func ObjectControlReloadWeapon(object weapon)
{
	if (!weapon->~IsHazardWeapon())
	{
		return false;
	}
	
	weapon->~RemoveAmmo();
	return weapon->~StartReload(this, nil, nil, true);
}
