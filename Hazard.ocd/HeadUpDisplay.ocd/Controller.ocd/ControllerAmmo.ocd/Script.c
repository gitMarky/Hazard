/**
	Shows the current ammo on the top left corner.

	@author Marky
*/

local gui_hazard_ammo;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Creation / Destruction

private func Construction()
{
	gui_hazard_ammo = {};
	gui_hazard_ammo.menu = AssembleHazardAmmo();
	gui_hazard_ammo.id = GuiOpen(gui_hazard_ammo.menu);

	return _inherited(...);
}

private func Destruction()
{
	GuiClose(gui_hazard_ammo.id);
	gui_hazard_ammo.id = nil;

	_inherited(...);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Callbacks

public func OnCrewRecruitment(object clonk, int plr)
{
	ScheduleUpdateHazardAmmo();

	return _inherited(clonk, plr, ...);
}

public func OnCrewDeRecruitment(object clonk, int plr)
{
	ScheduleUpdateHazardAmmo();

	return _inherited(clonk, plr, ...);
}

public func OnCrewDeath(object clonk, int killer)
{
	ScheduleUpdateHazardAmmo();

	return _inherited(clonk, killer, ...);
}

public func OnCrewDestruction(object clonk)
{
	ScheduleUpdateHazardAmmo();

	return _inherited(clonk, ...);
}

public func OnCrewDisabled(object clonk)
{
	ScheduleUpdateHazardAmmo();

	return _inherited(clonk, ...);
}

public func OnCrewEnabled(object clonk)
{
	ScheduleUpdateHazardAmmo();

	return _inherited(clonk, ...);
}

public func OnCrewSelection(object clonk, bool unselect)
{
	ScheduleUpdateHazardAmmo();

	return _inherited(clonk, unselect, ...);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GUI definition

private func AssembleHazardAmmo()
{
	return {}; // empty menu for now
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Drawing / display

private func ScheduleUpdateHazardAmmo()
{
	if (!GetEffect("UpdateHazardAmmo", this))
		AddEffect("UpdateHazardAmmo", this, 1, 1, this);
}


private func FxUpdateHazardItemTimer()
{
	UpdateHazardAmmo();
	return FX_Execute_Kill;
}


// Update everything
private func UpdateHazardAmmo()
{
	var cursor = GetCursor(GetOwner());
}
