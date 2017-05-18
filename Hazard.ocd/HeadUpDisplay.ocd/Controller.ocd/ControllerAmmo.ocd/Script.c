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
	gui_hazard_ammo.Menu = AssembleHazardAmmo();
	gui_hazard_ammo.ID = GuiOpen(gui_hazard_ammo.Menu);
	
	CreateHazardAmmoCounters();
	
	return _inherited(...);
}

private func Destruction()
{
	GuiClose(gui_hazard_ammo.ID);
	gui_hazard_ammo.ID = nil;

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

public func OnSlotObjectChanged(int slot)
{
	ScheduleUpdateHazardAmmo();

	return _inherited(slot, ...);
}

public func OnHazardAmmoChange(object clonk)
{
	ScheduleUpdateHazardAmmo();

	return _inherited(clonk);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GUI definition

private func AssembleHazardAmmo()
{
	var menu = {
		Target = this,
		Player = NO_OWNER, // will be shown once a gui update occurs
		Style = GUI_Multiple | GUI_NoCrop | GUI_IgnoreMouse,
	};
	
	return menu;
}


private func CreateHazardAmmoCounters()
{
	gui_hazard_ammo.counters = [];
	
	var ammo_types = [];
	var ammo_type;

	// get all ammo
	for (var i = 0; ammo_type = GetDefinition(i, C4D_StaticBack); ++i)
	{
		if (ammo_type->~IsAmmo())
		{
			PushBack(ammo_types, ammo_type);
		}
	}
	
	// need to remove some inventory buttons?
	for (var type in ammo_types)
	{
		CreateHazardAmmoCounter(GetLength(ammo_types), type);
	}
}


private func CreateHazardAmmoCounter(int max_counters, id ammo_type)
{
	var counter_number = GetLength(gui_hazard_ammo.counters);
	var counter_info =
	{
		ID = counter_number + 1,
		Type = ammo_type,
		Amount = 0,
	};
	PushBack(gui_hazard_ammo.counters, counter_info);

	var counter = AssembleHazardAmmoCounter(max_counters, counter_number, counter_info);

	GuiUpdate({_new_icon = counter}, gui_hazard_ammo.ID);
}


private func AssembleHazardAmmoCounter(int max_counters, int counter_number, proplist counter_info)
{
	// The gui already exists, only update it with a new submenu
	var pos = GuiCalculateGridElementPosition(AmmoCounterGridLayout(max_counters), counter_number, 0);

	var counter = 
	{
		Target = this,
		Style = GUI_NoCrop,
		ID = counter_info.ID,
		Symbol = counter_info.Type,
		Style = GUI_NoCrop,
		Count = {
			Target = this,
			Right = ToEmString(20),
			Bottom = ToEmString(12),
			Text = "",
			Style = GUI_TextRight | GUI_TextVCenter,
		},
	};
	
	return AddProperties(counter, pos);
}


private func AmmoCounterGridLayout(int max_counters)
{
	var grid_margin_top = 2 * GUI_Controller_CrewBar_CursorMargin
	                        + GUI_Controller_CrewBar_CursorSize
	                    + 2 * GUI_Controller_CrewBar_BarMargin
	                        + GUI_Controller_CrewBar_BarSize;
	                        
	var grid_margin_left = 5 + 30; // the additional margin is added until the old hud can be removed

	var icon_size = 12;
	return
	{
		Grid = {
			Prototype = GUI_BoxLayout,
			Margin = {Left = grid_margin_left, Top = grid_margin_top},
			Align = { X = GUI_AlignLeft,  Y = GUI_AlignTop,},
			Rows = max_counters,
			Columns = 1,
			Dimension = Global.ToEmString,
		},
		Cell = {
			Prototype = GUI_BoxLayout,
			Width = icon_size,
			Height = icon_size,
			Dimension = Global.ToEmString,
		}
	};
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Drawing / display

private func ScheduleUpdateHazardAmmo()
{
	if (!GetEffect("UpdateHazardAmmo", this))
		AddEffect("UpdateHazardAmmo", this, 1, 1, this);
}


private func FxUpdateHazardAmmoTimer()
{
	UpdateHazardAmmo();
	return FX_Execute_Kill;
}


// Update everything
private func UpdateHazardAmmo()
{
	var cursor = GetCursor(GetOwner());
	
	if (GuiShowForCrew(gui_hazard_ammo, GetOwner(), cursor))
	{
    	var weapon = cursor->~GetCurrentItem();

		for (var counter_info in gui_hazard_ammo.counters)
		{
			UpdateHazardAmmoCounter(cursor, weapon, counter_info);
		}
	}
}


private func UpdateHazardAmmoCounter(object cursor, object weapon, proplist counter_info)
{
	var amount = cursor->GetAmmo(counter_info.Type);

	var color;
	if (weapon && weapon->~IsHazardWeapon() && weapon->GetFiremode().ammo_id == counter_info.Type)
	{
		if (amount > 0)
			color = "ffff00";
		else
			color = "ff0000";
	}
	else
	{
		if (amount > 0)
			color = "eeeeee";
		else
			color = "777777";
	}

	// Compose the update!
	var update =
	{
		Symbol = counter_info.Type,
		Count = {Text = Format("<c %s>%d</c>", color, amount)},
	};

	GuiUpdate(update, gui_hazard_ammo.ID, counter_info.ID, this);
}
