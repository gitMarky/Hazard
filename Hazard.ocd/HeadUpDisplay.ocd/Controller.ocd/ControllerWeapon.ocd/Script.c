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
	ScheduleUpdateHazardWeapon();

	return _inherited(clonk, plr, ...);
}

public func OnCrewDeRecruitment(object clonk, int plr)
{
	ScheduleUpdateHazardWeapon();

	return _inherited(clonk, plr, ...);
}

public func OnCrewDeath(object clonk, int killer)
{
	ScheduleUpdateHazardWeapon();

	return _inherited(clonk, killer, ...);
}

public func OnCrewDestruction(object clonk)
{
	ScheduleUpdateHazardWeapon();

	return _inherited(clonk, ...);
}

public func OnCrewDisabled(object clonk)
{
	ScheduleUpdateHazardWeapon();

	return _inherited(clonk, ...);
}

public func OnCrewEnabled(object clonk)
{
	ScheduleUpdateHazardWeapon();

	return _inherited(clonk, ...);
}

public func OnCrewSelection(object clonk, bool unselect)
{
	ScheduleUpdateHazardWeapon();

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

private func ScheduleUpdateHazardWeapon()
{
	if (!GetEffect("UpdateHazardWeapon", this))
		AddEffect("UpdateHazardWeapon", this, 1, 1, this);
}


private func FxUpdateHazardWeaponTimer()
{
	UpdateHazardWeapon();
	return FX_Execute_Kill;
}


// Update everything
private func UpdateHazardWeapon()
{
	var cursor = GetCursor(GetOwner());
}
