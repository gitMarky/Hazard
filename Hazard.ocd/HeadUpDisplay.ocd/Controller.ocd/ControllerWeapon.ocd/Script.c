/**
	Shows information about the current weapon.

	@author Marky
*/

local gui_hazard_weapon;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Creation / Destruction

private func Construction()
{
	gui_hazard_weapon = {};
	gui_hazard_weapon.menu = AssembleHazardWeapon();
	gui_hazard_weapon.id = GuiOpen(gui_hazard_weapon.menu);

	return _inherited(...);
}

private func Destruction()
{
	GuiClose(gui_hazard_weapon.id);
	gui_hazard_weapon.id = nil;

	_inherited(...);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Callbacks

public func OnCrewRecruitment(object clonk, int plr)
{
	UpdateHazardWeapon();

	return _inherited(clonk, plr, ...);
}

public func OnCrewDeRecruitment(object clonk, int plr)
{
	UpdateHazardWeapon();

	return _inherited(clonk, plr, ...);
}

public func OnCrewDeath(object clonk, int killer)
{
	UpdateHazardWeapon();

	return _inherited(clonk, killer, ...);
}

public func OnCrewDestruction(object clonk)
{
	UpdateHazardWeapon();

	return _inherited(clonk, ...);
}

public func OnCrewDisabled(object clonk)
{
	UpdateHazardWeapon();

	return _inherited(clonk, ...);
}

public func OnCrewEnabled(object clonk)
{
	UpdateHazardWeapon();

	return _inherited(clonk, ...);
}

public func OnCrewSelection(object clonk, bool unselect)
{
	UpdateHazardWeapon();

	return _inherited(clonk, unselect, ...);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GUI definition

private func AssembleHazardWeapon()
{
	return {}; // empty menu for now
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Drawing / display

// Update everything
private func UpdateHazardWeapon()
{
	var cursor = GetCursor(GetOwner());
}
