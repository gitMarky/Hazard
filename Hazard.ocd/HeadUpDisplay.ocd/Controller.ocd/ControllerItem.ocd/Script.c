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
	gui_hazard_item.Menu = AssembleHazardItem();
	gui_hazard_item.ID = GuiOpen(gui_hazard_item.Menu);

	return _inherited(...);
}

private func Destruction()
{
	GuiClose(gui_hazard_item.ID);
	gui_hazard_item.ID = nil;

	_inherited(...);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Callbacks

public func OnCrewRecruitment(object clonk, int plr)
{
	ScheduleUpdateHazardItem();

	return _inherited(clonk, plr, ...);
}

public func OnCrewDeRecruitment(object clonk, int plr)
{
	ScheduleUpdateHazardItem();

	return _inherited(clonk, plr, ...);
}

public func OnCrewDeath(object clonk, int killer)
{
	ScheduleUpdateHazardItem();

	return _inherited(clonk, killer, ...);
}

public func OnCrewDestruction(object clonk)
{
	ScheduleUpdateHazardItem();

	return _inherited(clonk, ...);
}

public func OnCrewDisabled(object clonk)
{
	ScheduleUpdateHazardItem();

	return _inherited(clonk, ...);
}

public func OnCrewEnabled(object clonk)
{
	ScheduleUpdateHazardItem();

	return _inherited(clonk, ...);
}

public func OnCrewSelection(object clonk, bool unselect)
{
	ScheduleUpdateHazardItem();

	return _inherited(clonk, unselect, ...);
}

public func OnSlotObjectChanged(int slot)
{
	ScheduleUpdateHazardItem();

	return _inherited(slot, ...);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GUI definition

private func AssembleHazardItem()
{
	var menu = {
		Target = this,
		Player = NO_OWNER, // will be shown once a gui update occurs
		Style = GUI_Multiple | GUI_NoCrop | GUI_IgnoreMouse,
	};
	
	return menu;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Drawing / display

private func ScheduleUpdateHazardItem()
{
	if (!GetEffect("UpdateHazardItem", this))
		AddEffect("UpdateHazardItem", this, 1, 1, this);
}


private func FxUpdateHazardItemTimer()
{
	UpdateHazardItem();
	return FX_Execute_Kill;
}


// Update everything
private func UpdateHazardItem()
{
	var cursor = GetCursor(GetOwner());
	
	if (GuiShowForCrew(cursor, gui_hazard_item))
	{
	}
}
