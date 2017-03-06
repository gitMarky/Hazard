#appendto Library_ClonkControl

/* Main control function */
public func ObjectControl(int plr, int ctrl, int x, int y, int strength, bool repeat, int status)
{
	if (!this) return false;

	if (_inherited(plr, ctrl, x, y, strength, repeat, status))
	{
		return true;
	}
	
	if (ctrl == CON_WeaponFiremode)
	{
		Log("Toggle firemode");
	}
	else if (ctrl == CON_WeaponReload)
	{
		Log("Reload");
	}

	return false;
}