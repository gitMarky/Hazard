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
	gui_hazard_weapon.Menu = AssembleHazardWeapon();
	gui_hazard_weapon.ID = GuiOpen(gui_hazard_weapon.Menu);

	return _inherited(...);
}

private func Destruction()
{
	GuiClose(gui_hazard_weapon.ID);
	gui_hazard_weapon.ID = nil;

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

public func OnSlotObjectChanged(int slot)
{
	ScheduleUpdateHazardWeapon();

	return _inherited(slot, ...);
}

public func OnHazardWeaponAmmoChange(object clonk)
{
	ScheduleUpdateHazardWeapon();

	return _inherited(clonk);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GUI definition

private func AssembleHazardWeapon()
{

	var menu = {
		Target = this,
		Player = NO_OWNER, // will be shown once a gui update occurs
		Style = GUI_Multiple | GUI_IgnoreMouse,
		BackgroundColor = RGBa(0, 255, 200, 90),
	};
	
	return AddProperties(menu, this->GuiPositionHazardInfoField());
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

	if (GuiShowForCrew(gui_hazard_weapon, GetOwner(), cursor))
	{
		var weapon = cursor->GetCurrentItem();

		if (weapon && weapon->~IsHazardWeapon())
		{
			// do nothing for now
		}
		else
		{
			GuiHideMenu(gui_hazard_weapon);
		}
	}
}
