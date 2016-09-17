local Name = "HUD";

local 	ammo_icons,			// array of Hazard_HUD2-objects that show the crew member's ammo.
	    icon_status,		// Hazard_HUD2 helper object that shows the ammo count for weapons.
		icon_info;       	// Hazard_HUD2 helper object that shows the description of items that are not weapons.

local 	ammo_types,			// all definitions that are ammo
		ammo_values,        // fill levels of all ammo types of the crew member
      	progress_reload,	// progress of reloading (0 - 100)
      	progress_recovery,	// progress of recovery (0 - 100)
		current_weapon,	    // current weapon
		current_ammo_id,    // current ammo ID
		current_ammo_count, // current ammo count in the weapon
		current_crew;       // currently selected crew member

static const HUD_Layer_AmmoBase = 1;
static const HUD_Layer_Recharge = 2;
static const HUD_Layer_AmmoHighlight = 3;
static const HUD_Bar_OffsetX = 10000;

global func GetHazardHUD(id theID)
{
	if (!this)
	{
		FatalError("This function has to be called from object context");
	}

	var owner = GetOwner();
	if (owner <= NO_OWNER)
		return;

	// script players get no HUD
	if (GetPlayerType(owner) == C4PT_Script)
		return;

	theID = theID ?? Hazard_HUD;

	var hud = FindObject(Find_ID(theID), Find_Owner(owner));
	if (!hud)
	{
		hud = CreateObject(theID, 0, 0, owner);
	}
	return hud;
}


func Initialize()
{
	ammo_types = [];
	ammo_values = [];
	
	// Main Hud (Ammo progress bar)
	var yoffset = -55;
	SetPosition(105, yoffset);
	SetGraphics("Row", GetID(), HUD_Layer_AmmoBase, GFXOV_MODE_Base);
	SetGraphics("RowHighlight", GetID(), HUD_Layer_AmmoHighlight, GFXOV_MODE_Base);
	SetObjDrawTransform(1000, 0, HUD_Bar_OffsetX, 0, 1000, 0, 0);
	SetObjDrawTransform(1000, 0, HUD_Bar_OffsetX, 0, 1000, 0, HUD_Layer_AmmoBase);
	SetObjDrawTransform(1000, 0, HUD_Bar_OffsetX, 0, 1000, 0, HUD_Layer_AmmoHighlight);
	this.Visibility = VIS_None;

	// Ammo Hud
	icon_status = CreateObject(Hazard_HUD2, 0, 0, GetOwner());
	icon_status->SetPosition(50, yoffset);
	icon_status->SetGraphics(nil, GetID(), 1, GFXOV_MODE_IngamePicture);
	icon_status->SetObjDrawTransform(750, 0, 0, 0, 750, 0, 1);
	icon_status.Visibility = VIS_None;

	// Item Hud
	icon_info = CreateObject(Hazard_HUD2, 0, 0, GetOwner());
	icon_info->SetPosition(140, yoffset + 30);
	
	// Ammobag
	InitAmmoDisplayHUD();
}

func Destruction()
{
	if (icon_status)
		icon_status->RemoveObject();

	if (icon_info)
		icon_info->RemoveObject();

	for (var obj in ammo_icons)
	{
		if (obj)
			obj->RemoveObject();
	}
}

func InitAmmoDisplayHUD()
{
	// remove ammobag display
	var def = 0;
	ammo_types = [];
	ammo_values = [];
	var arrI = 0;

	// get all ammo
	for (var i = 0; def = GetDefinition(i, C4D_StaticBack); ++i)
	{
		if (def->~IsAmmo())
		{
			ammo_types[arrI] = def;
			ammo_values[arrI] = 0;
			arrI++;
		}
	}
	ammo_icons = [];
	
	// place all ammo objects
	for (var i = 0; i < GetLength(ammo_types); ++i)
	{
		// ...now
		ammo_icons[i] = CreateObject(Hazard_HUD2, 0, 0, GetOwner());
		ammo_icons[i]->SetPosition(50, 200 + i * 32);
		ammo_icons[i]->SetGraphics(nil, ammo_types[i], 1, GFXOV_MODE_IngamePicture);
		ammo_icons[i]->SetObjDrawTransform(750, 0, 0, 0, 750, 0, 0, 1);
		ammo_icons[i].visibility = VIS_None;
	}
}

/* Timer */

func Timer()
{
	// player left?
	if (GetOwner() == NO_OWNER || !GetPlayerName(GetOwner()))
	{
		RemoveObject();
		return;
	}
}

/* Calls */

func Update(object weapon, object ammobag, object who)
{
	// Update cursor
	if (who)
	{
		if (GetCursor(who->GetOwner()) == who)
		{
			UpdateWeapon(weapon);
			
			if (ammobag)
				UpdateAmmoDisplay(ammobag, weapon);
		}
	}
}


// Updaten weapon HUD
func UpdateWeapon(object weapon)
{
	if (!weapon || !weapon->~IsHazardWeapon())
	{
		this.Visibility = VIS_None;
		icon_status.Visibility = VIS_None;
		this->Message("");
		icon_status->Message("");
		progress_reload = 0;
		progress_recovery = 0;
		SetCurrentWeapon(nil);

		// no inventory
		if (!weapon)
		{
			icon_info.Visibility = VIS_None;
			icon_info->Message("");
		}
		else
		{
			icon_info.Visibility = VIS_Owner;
			CustomMessage
			(
				Format("@<c ffff00>%s</c>|%s", weapon->GetName(), weapon.Description),
				icon_info,
				GetOwner()
			);
		}
	}
	else
	{
		// get some basic values
		this.Visibility = VIS_Owner;
		icon_status.Visibility = VIS_Owner;
		icon_info.Visibility = VIS_None;
		icon_info->Message("");
		
		var ammoid = weapon->GetFiremode().ammo_id;
		var ammoload = weapon->GetFiremode().ammo_load;
		var modusname = weapon->GetFiremode().name;
		var ammocount = weapon->GetAmmo(ammoid);
		
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
			progress_reload = BoundBy(ammocount * 100 / ammoload, 0, 100);
		}
		
		
		// draw the stuff
		
		SetCurrentWeapon(weapon);
		
		current_ammo_count = ammocount;
		if (ammodiff) AddEffect("AmmoUpdateNotification", icon_status, 300, 1, this, nil, ammodiff, 750);
		
		var color = "ffff00";
		if (!ammocount) color = "ff0000";
		CustomMessage(Format("@%s", modusname), this, GetOwner(), 5, 7);
		CustomMessage
		(
			Format("@<c %s>%d/%d</c>", color, ammocount, ammoload),
			icon_status,
			GetOwner(),
			130 + GetNumberCount(ammoload) * 6,
			31
		);
		
		if (!SetGraphics(Format("Row%i", ammoid), GetID(), HUD_Layer_AmmoBase, GFXOV_MODE_Base))
		{
			SetGraphics("Row", GetID(), HUD_Layer_AmmoBase, GFXOV_MODE_Base);
		}
		icon_status->SetGraphics(nil, ammoid, 1, GFXOV_MODE_IngamePicture);
	}
	
	UpdateReloadProgress();
	UpdateRecoveryProgress();
}

// set new active weapon and start graphics effects
func SetCurrentWeapon(object weapon)
{
	if (weapon == current_weapon)
	{
		var ammoid = nil;
		if (weapon)
			ammoid = weapon->GetFiremode().ammo_id;
		if (ammoid == current_ammo_id)
			return;
	}
	
	if (current_weapon)
	{
		RemoveEffect(Format("Animation%i", current_ammo_id), this);
		SetGraphics("RowHighlight", GetID(), HUD_Layer_AmmoHighlight, GFXOV_MODE_Base, nil, GFX_BLIT_Additive);
	}
	
	if (weapon)
	{
		var ammoid = weapon->GetFiremode().ammo_id;
		AddEffect(Format("Animation%i", ammoid), this, 300, 1, this);
		current_ammo_id = ammoid;
	}
	else
	{
		current_ammo_id = nil;
	}
	
	current_weapon = weapon;
}

// gets the number of, well... numbers ^^
func GetNumberCount(int value)
{
	var result = 0;
	var bigNumba = 1;
	while (value >= bigNumba)
	{
		bigNumba *= 10;
		result++;
	}
	return result;
}


// reload, bar goes to the right
func UpdateReloadProgress()
{
	this->SetObjDrawTransform(GetBarWidth(progress_reload), 0, HUD_Bar_OffsetX - GetBarXOffset(progress_reload), 0, 1000, 0, HUD_Layer_AmmoBase);
}

// progress_recovery, bar goes from right to left
func UpdateRecoveryProgress()
{
	if (progress_recovery)
	{
		SetGraphics("Red", GetID(), GFXOV_MODE_Action, HUD_Layer_Recharge, "Red");
		SetObjDrawTransform(1000, 0, HUD_Bar_OffsetX + 50000 - GetBarXOffset(progress_recovery) * 2, 0, 1000, 0, HUD_Layer_Recharge);
	}
	else
	{
		SetGraphics(nil, GetID(), 0, HUD_Layer_Recharge);
	}
}


// update current ammo display
func UpdateAmmoDisplay(object ammobag, object weapon)
{
	var ammoid = nil;
	if (weapon && weapon->~IsHazardWeapon())
		ammoid = weapon->GetFiremode().ammo_id;
	
	var clonk = GetCursor();

	for (var i = 0; i < GetLength(ammo_icons); ++i)
	{
		var icon = ammo_icons[i];
		
		// invisible if there is no ammo
		if (!ammobag)
		{
			icon.Visibility = VIS_None;
			icon->Message("");
			continue;
		}

		// show ammo
		icon.Visibility = VIS_Owner;
		
		var amount = 0;
		if (ammobag)
			amount = ammobag->GetAmmo(ammo_types[i]);
	
		var infinite = (ammobag->GetAmmoSource(ammo_types[i]) == AMMO_Source_Infinite);

		var ammodiff = 0;
		if (clonk == current_crew)
		{
			ammodiff = amount - ammo_values[i];
		}
		ammo_values[i] = amount;
		if (ammodiff) AddEffect("AmmoUpdateNotification", icon, 300, 1, this, nil, ammodiff, 750);
		
		var color = "eeeeee";
		if (!amount) color = "777777";
		if (ammo_types[i] == ammoid)
		{
			color = "ffff00";
			if (!amount) color = "ff0000";
		}
		
		var overlay_infinity = 2;
		if (infinite)
		{
			icon->SetGraphics("Inf", Icon_Number, overlay_infinity, GFXOV_MODE_Base);
			icon->SetObjDrawTransform(375, 0, 28000, 0, 375, 0, overlay_infinity);
			icon->SetClrModulation(0xffeeeeee, overlay_infinity);
		}
		else
		{
			icon->CustomMessage(Format("@<c %s>%d</c>", color, amount), icon, GetOwner(), 25, 31);
			icon->SetGraphics(nil, icon->GetID(), overlay_infinity);
		}
	}
	
	current_crew = clonk;
}


/* Changed ammo count effect - the ammo icon bounces a little whenever ammo is increased or decreased */
func FxAmmoUpdateNotificationStart(object target, proplist number, int temp, int ammodiff, int size)
{
	if (temp) return;
	
	number.diff = 3 * size * ammodiff / Abs(ammodiff) / 4 + size / 4; // size ... -size/2
	number.size = size;
}


func FxAmmoUpdateNotificationAdd(object target, proplist number, string name, int timer, int ammodiff, int size)
{
	number.diff = 3 * size * ammodiff / Abs(ammodiff) / 4 + size / 4; // size ... -size/2
}


func FxAmmoUpdateNotificationEffect(string name, object target, proplist number, int newNumber)
{
	if (name == "AmmoUpdateNotification")
		return -2;
}


func FxAmmoUpdateNotificationTimer(object target, proplist number, int timer)
{
	var diff = number.diff;
	var size = number.size;
	
	target->SetObjDrawTransform(size + diff, 0, 0, 0, size + diff, 0, 1);
	
	if (!diff) return FX_Execute_Kill;
	
	var sqrtDiff = diff / Abs(diff) * Sqrt(Abs(diff));
	number.diff -= sqrtDiff;
}


/* Nice overlay effects */
func FxAnimationAmmo_EnergyTimer(object target, proplist number, int timer)
{
	var lightning = number.diff;
	SetGraphics
	(
		Format("Row%iHighlight%d", Ammo_Energy, Random(4) + 1),
		GetID(),
		HUD_Layer_AmmoHighlight,
		GFXOV_MODE_Base,
		nil,
		GFX_BLIT_Additive
	);
	if (!Random(35))
		lightning -= 60;
	else
		lightning += 5;
	lightning = BoundBy(lightning, 120, 240);
	SetClrModulation(RGBa(255, 255, 255, 255 - lightning), HUD_Layer_AmmoHighlight);
	this->SetObjDrawTransform(GetBarWidth(progress_reload), 0, HUD_Bar_OffsetX - GetBarXOffset(progress_reload), 0, 1000, 0, HUD_Layer_AmmoHighlight);
	number.diff = lightning;
}


func FxAnimationAmmo_GasolineTimer(object target, proplist number, int timer)
{
	SetGraphics
	(
		Format("Row%iHighlight", Ammo_Gasoline),
		target->GetID(),
		HUD_Layer_AmmoHighlight,
		GFXOV_MODE_Base,
		nil,
		GFX_BLIT_Additive
	);
	SetClrModulation(RGBa(255, 255, 255, 235), HUD_Layer_AmmoHighlight);
	var xSkew = Cos(FrameCounter() * 12, 200);
	var plusHeight = Cos(FrameCounter() * 9, 100) + Sin(FrameCounter() * 22, 35);
	var yOffset = 500 - target->GetID()->GetDefHeight() * plusHeight / 4;
	this->SetObjDrawTransform(GetBarWidth(progress_reload), xSkew, HUD_Bar_OffsetX - GetBarXOffset(progress_reload),	0, 800 + plusHeight, yOffset, HUD_Layer_AmmoHighlight);
}

func GetBarXOffset(int percent)
{
	return 1000 * (100 - percent) / 2;
}

func GetBarWidth(int percent)
{
	return percent * 10;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap =
{
	Red =
	{
		Prototype = Action,
		Name = "Red",
		X = 0,
		Y = 0,
		Wdt = 5,
		Hgt = 10
	}
};

