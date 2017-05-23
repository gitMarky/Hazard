
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
			
			full = {
				Priority = 11,
				BackgroundColor = RGBa(150, 150, 150, 150),
			},
			ammo = {
				Priority = 12,
				BackgroundColor = RGBa(255, 255, 0, 150),
			},
			recharge = {
				Priority = 13,
				BackgroundColor = RGBa(230, 0, 0, 200),
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
			tile = {},
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


private func ScheduleUpdateHazardWeaponBar(object cursor, object weapon)
{
	var ammoid = weapon->GetFiremode().ammo_id;
	var ammocount = weapon->GetAmmo(ammoid);

	var fx = GetEffect("UpdateHazardWeaponBar", this) ?? AddEffect("UpdateHazardWeaponBar", this, 1, 1, this); 
	fx.cursor = cursor;
	if (fx.weapon != weapon)
	{
		fx.ammocount = ammocount;
	}
	fx.weapon = weapon;
}


private func CancelUpdateHazardWeaponBar()
{
	RemoveEffect("UpdateHazardWeaponBar", this); 
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
			ScheduleUpdateHazardWeaponBar(cursor, weapon);
		}
		else
		{
			GuiHideMenu(gui_hazard_weapon);
			CancelUpdateHazardWeaponBar();
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
			ammo = {Symbol = Hazard_HUD, GraphicsName = Format("Row%i", ammoid)},
		},
		count = {Text = count},
		icon = { tile = {Symbol = ammoid}},
	};

	GuiUpdate(update, gui_hazard_weapon.ID, nil, this);
}


private func FxUpdateHazardWeaponBarTimer(object target, proplist fx, int timer)
{
	if (fx.weapon)
	{
		var ammoid = fx.weapon->GetFiremode().ammo_id;
		var ammoload = fx.weapon->GetFiremode().ammo_load;
		var ammocount = fx.weapon->GetAmmo(ammoid);
		var infinite = (fx.weapon->GetAmmoSource(ammoid) == AMMO_Source_Infinite);

		// flash the ammo symbol
		var ammodiff = ammocount - fx.ammocount;	
		if (ammodiff)
		{
			fx.ammocount = ammocount;
			AmmoUpdateNotification(ammodiff, 750);
		}

		// reload
		var progress_reload;
		if (fx.weapon->~IsReloading())
		{
			progress_reload = 10 * fx.weapon->GetReloadProgress();
		}
		else
		{
			if (infinite)
				progress_reload = 1000;
			else
				progress_reload = ammocount * 1000 / ammoload;
		}
		DrawHazardWeaponAmmoBar(progress_reload);
		
		// recovery
		var progress_recovery;
		if (fx.weapon->~IsRecovering())
		{
			progress_recovery = BoundBy(fx.weapon->GetRecoveryProgress(), 0, 100) * 10;
		}
		else
		{
			progress_recovery = 1000;
		}
		DrawHazardWeaponRecoveryBar(progress_recovery);

		return FX_OK;
	}
	else
	{
		return FX_Execute_Kill;
	}
}


private func DrawHazardWeaponAmmoBar(int progress)
{
	// Compose the update!
	var update =
	{
		bar = {
			ammo = { Right = ToPercentString(BoundBy(progress, 0, 1000))},
		},
	};

	GuiUpdate(update, gui_hazard_weapon.ID, nil, this);
}


private func DrawHazardWeaponRecoveryBar(int progress)
{
	// Compose the update!
	var width = 20;
	var update =
	{
		bar = {
			recharge = { Left = ToPercentString(BoundBy(progress - width, 0, 1000)),  Right = ToPercentString(BoundBy(progress, 0, 1000))},
		},
	};

	GuiUpdate(update, gui_hazard_weapon.ID, nil, this);
}


private func OnAmmoUpdateNotification(proplist position, proplist info)
{
	var update =
	{
		icon = {tile = position,},
	};

	GuiUpdate(update, gui_hazard_weapon.ID, nil, this);
}
