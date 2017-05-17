/**
	Shows the current ammo on the top left corner.

	@author Marky
*/

local gui_hazard_item;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Creation / Destruction

private func Construction()
{
	gui_hazard_item = {};
	gui_hazard_item.menu = AssembleHazardItem();
	gui_hazard_item.id = GuiOpen(gui_hazard_item.menu);

	return _inherited(...);
}

private func Destruction()
{
	GuiClose(gui_hazard_item.id);
	gui_hazard_item.id = nil;

	_inherited(...);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Callbacks

public func OnCrewRecruitment(object clonk, int plr)
{
	UpdateHazardItem();

	return _inherited(clonk, plr, ...);
}

public func OnCrewDeRecruitment(object clonk, int plr)
{
	UpdateHazardItem();

	return _inherited(clonk, plr, ...);
}

public func OnCrewDeath(object clonk, int killer)
{
	UpdateHazardItem();

	return _inherited(clonk, killer, ...);
}

public func OnCrewDestruction(object clonk)
{
	UpdateHazardItem();

	return _inherited(clonk, ...);
}

public func OnCrewDisabled(object clonk)
{
	UpdateHazardItem();

	return _inherited(clonk, ...);
}

public func OnCrewEnabled(object clonk)
{
	UpdateHazardItem();

	return _inherited(clonk, ...);
}

public func OnCrewSelection(object clonk, bool unselect)
{
	UpdateHazardItem();

	return _inherited(clonk, unselect, ...);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GUI definition

private func AssembleHazardItem()
{
	return {}; // empty menu for now
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Drawing / display

// Update everything
private func UpdateHazardItem()
{
	var cursor = GetCursor(GetOwner());
}
