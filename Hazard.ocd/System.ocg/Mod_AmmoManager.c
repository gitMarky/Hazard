#appendto Library_AmmoManager


/**
 Update the HUD whenever ammo changes.
 */
public func SetAmmo(id ammo, int new_value)
{
	var info = _inherited(ammo, new_value);
	
	if (this->~GetHUDController())
	{
		this->~GetHUDController()->~OnHazardAmmoChange(this);
	}

	return info;
}
