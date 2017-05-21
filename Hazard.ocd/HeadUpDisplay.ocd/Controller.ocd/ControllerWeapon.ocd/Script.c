
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
		Style = GUI_Multiple | GUI_IgnoreMouse | GUI_NoCrop,
		BackgroundColor = RGBa(0, 255, 200, 90),
		
		bar = { // sub-window that contains the ammo-bar
			Priority = 10,
			Left = ToPercentString(150),
			Right =  ToPercentString(650),
			Top = ToPercentString(750),
			Bottom = ToPercentString(850),
			BackgroundColor = RGBa(150, 150, 150, 150),
			
			full = {
				Priority = 11,
			},
			ammo = {
				Priority = 12,
			},
			recharge = {
				Priority = 13,
			},
			reload = {
				Priority = 14,
			},
		},
		
		mode = {
			Priority = 11,
			Left = ToPercentString(150),
			Right = ToPercentString(650),
			Top = Format("%s%s", ToPercentString(750), ToEmString(-15)),
			Bottom = ToPercentString(750),
			Style = GUI_TextHCenter | GUI_TextVCenter,
		},
		
		count = {
			Priority = 12,
			Left = Format("%s%s", ToPercentString(600), ToEmString(10)),
			Right = Format("%s%s", ToPercentString(600), ToEmString(10)),
			Top = ToPercentString(700),
			Bottom = ToPercentString(850),
			Style = GUI_NoCrop | GUI_TextVCenter,
		},
		
		icon = {
			Priority = 20,
			Left = Format("%s%s", ToPercentString(150), ToEmString(-20)),
			Right =  ToPercentString(150),
			Top = Format("%s%s", ToPercentString(800), ToEmString(-10)),
			Bottom = Format("%s%s", ToPercentString(800), ToEmString(+10)),
		},
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
			UpdateHazardWeaponDisplay(cursor, weapon);
		}
		else
		{
			GuiHideMenu(gui_hazard_weapon);
		}
	}
}


private func UpdateHazardWeaponDisplay(object cursor, object weapon)
{
	var ammoid = weapon->GetFiremode().ammo_id;
	var ammoload = weapon->GetFiremode().ammo_load;
	var modusname = weapon->GetFiremode().name;
	var ammocount = weapon->GetAmmo(ammoid);

	var infinite = (weapon->GetAmmoSource(ammoid) == AMMO_Source_Infinite);
/*		
		var ammodiff = 0;
		if (current_weapon == weapon && current_ammo_id == ammoid)
		{
			ammodiff = ammocount - current_ammo_count;
		}
		
		// set status information
		if (weapon->IsRecovering())
		{
			progress_recovery = BoundBy(weapon->GetRecoveryProgress(), 0, 100);
		}
		else
		{
			progress_recovery = 0;
		}

		if (weapon->IsReloading())
		{
			progress_reload = BoundBy(weapon->GetReloadProgress(), 0, 100);
		}
		else
		{
			if (infinite)
			{
				progress_reload = 100;
			}
			else
			{
				progress_reload = BoundBy(ammocount * 100 / ammoload, 0, 100);
			}
		}
		
		// draw the stuff

		//SetCurrentWeapon(weapon);

		current_ammo_count = ammocount;
		if (ammodiff) AddEffect("AmmoUpdateNotification", icon_status, 300, 1, this, nil, ammodiff, 750);
*/	


		// message for displayed ammo amount
		var color;
		if (ammocount || infinite)
		{
			color = "ffff00";
		}
		else
		{
			color = "ff0000";
		}


		var count;
		if (infinite)
		{
			//->Message("");
			//icon_status->SetGraphics("Inf", Icon_Number, HUD_Layer_AmmoAmount, GFXOV_MODE_Base);
			//icon_status->SetObjDrawTransform(400, 0, 132 * 1000, 0, 400, -1000, HUD_Layer_AmmoAmount);
		}
		else
		{
			count = Format("<c %s>%d/%d</c>", color, ammocount, ammoload);
		}

		// Compose the update!
		var update =
		{
			mode = {Text = modusname},
			bar = {
				full = {Symbol = Hazard_HUD},
				ammo = {Symbol = Hazard_HUD, GraphicsName = Format("Row%i", ammoid), Right = ToPercentString(BoundBy(ammocount * 1000 / ammoload, 0, 1000))},
			},
			count = {Text = count},
			icon = {Symbol = ammoid},
		};
	
		GuiUpdate(update, gui_hazard_weapon.ID, nil, this);
}
