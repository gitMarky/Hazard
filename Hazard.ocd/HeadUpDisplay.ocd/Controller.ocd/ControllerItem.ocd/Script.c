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
	var margin = ToEmString(5);
	var margin_bottom = ToEmString(-5);
	var width = ToPercentString(400);
	var height = ToPercentString(-200);
	var bottom = ToPercentString(1000);

	var menu = {
		Target = this,
		Player = NO_OWNER, // will be shown once a gui update occurs
		Style = GUI_Multiple | GUI_IgnoreMouse,
		Left = Format("%s", margin), Right = Format("%s%s", margin, width),
		Top = Format("%s%s%s", bottom, margin_bottom, height), Bottom = Format("%s%s", bottom, margin_bottom),
		BackgroundColor = RGBa(0, 200, 255, 90),
		icon = {
			Priority = 10,
			Right = ToPercentString(300),
			Top = ToPercentString(100),
			Bottom = ToPercentString(900),
			Symbol = nil,
		},
		desc = {
			Priority = 20, 
			Left = ToPercentString(200),
			Top = ToPercentString(100),
			Bottom = ToPercentString(900),
		},
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
	
	if (GuiShowForCrew(gui_hazard_item, GetOwner(), cursor))
	{
		var item = cursor->GetCurrentItem();

		if (item && !item->~IsHazardWeapon())
		{
			var text = Format("<c ffff00>%s</c>|%s", item->GetName(), item.Description ?? "");
			var symbol = item;
			
			// Compose the update!
			var update =
			{
				icon = {Symbol = symbol,},
				desc = {Text = text,},
			};
		
			GuiUpdate(update, gui_hazard_item.ID, nil, this);
		}
		else
		{
			GuiHideMenu(gui_hazard_item);
		}
	}
}
