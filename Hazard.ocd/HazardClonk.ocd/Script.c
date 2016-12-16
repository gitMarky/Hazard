#include Clonk
#include Library_AmmoManager
#include Library_Agility
#include Library_UseGear


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Properties

local MaxWeaponsCount = 3; // this many weapons can be collected
local MaxEquipmentCount = 2; // this many equipment items can be collected

public func GetAmmoSource(id ammo)
{
	return AMMO_Source_Local;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Callbacks


func Initialize()
{
    _inherited(...);
    var hud = this->GetHazardHUD();
    if (hud) ScheduleCall(this, this.UpdateHazardHUD, 1);
}


func RejectCollect(id type, object item)
{
	var rejected = _inherited(type, item, ...);
	if (rejected) return rejected;
	
	if (item)
	{
		// always allow at least 1 ammo packet
		if (item->~IsAmmoPacket() && CustomContentsCount("IsAmmoPacket") == 0)
		{
			return false;
		}
		
		// certain items can be collected only once per type
		if (ContentsCount(type) > 0
		&& (item->~IsHazardWeapon()
		 || item->~IsHazardEquipment()))
		{
			return true; // do not collect
		}

		// allow not more than 3 weapons in total
		if (item->~IsHazardWeapon()
		&& (CustomContentsCount("IsHazardWeapon") >= this.MaxWeaponsCount))
		{
			return true; // do not collect
		}
	
		// allow 2 equipment items
		if (item->~IsHazardEquipment()
		&& (CustomContentsCount("IsHazardEquipment") >= this.MaxEquipmentCount))
		{
			return true; // do not collect
		}
	}
	
	// allow collection
	return false;
}


func CustomContentsCount(string qualifier)
{
	var contents = FindObjects(Find_Container(this), Find_Func(qualifier, this));
	return GetLength(contents);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Appearance


func SetSkin(int new_skin)
{
	// Remember skin
	skin = new_skin;
	
	//Steampunk
	SetGraphics(skin_name = "Alchemist", Clonk);
	gender = 0;
	
	SetHazardSkin();

	RemoveBackpack(); // remove the backpack

	//refreshes animation (whatever that means?)
	// Go back to original action afterwards and hope
	// that noone calls SetSkin during more complex activities
	var prev_action = GetAction();
	SetAction("Jump");
	SetAction(prev_action);
	SetOwner(GetOwner()); // somehow the color did not get updated after setting the color

	return skin;
}

func SetHazardSkin()
{
	SetMeshMaterial("HazardClonk");
	SetMeshMaterial("HazardClonkTunic", 1);
}

func SetHazardArmorSkin()
{
	SetMeshMaterial("HazardClonkArmor");
	SetMeshMaterial("HazardClonkArmorTunic", 1);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HUD


public func UpdateHazardHUD()
{
    var weapon = this->GetHandItem(0);

    var hud = this->GetHazardHUD();
    if (hud)
    {
    	hud->~Update(weapon, this, this);
    	ScheduleCall(this, this.UpdateHazardHUD, 1);
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Actions

local ActMap = {

JetpackFlight = {
	Prototype = ActMap.Jump,
	Name = "JetpackFlight",
},

Backflip = {
	Prototype = ActMap.Jump,
	Name = "Backflip",
	Delay = ANIM_BACKFLIP_Length,
	NextAction = "Jump",
}

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GUI

public func HasInteractionMenu(){ return true;}

public func GetInteractionMenus(object crew)
{
	var menus = _inherited(crew) ?? [];		

	var priority_base = 50;

	// add menus from contents
	if (crew == this) // TODO: maybe let friendly clonks access this, too?
	{
		for (var item in FindObjects(Find_Container(this)))
		{
			if (item && item->~HasInteractionMenu())
			{
				var other = item->GetInteractionMenus(crew);

				// shift priority
				for (var menu in other)
				{
					menu.Priority += priority_base;
					PushBack(menus, menu);
				}
			}
		}
	}

	return menus;
}


public func GetGUIFiremodeMenuColor(){ return RGB(0, 50, 50);}


public func GetGUIFiremodeMenuEntries(object crew)
{
	var menu_entries = [];

	// default design of a control menu item
	var custom_entry = 
	{
		Right = "100%", Bottom = "2em",
		BackgroundColor = {Std = 0, OnHover = 0x50ff0000},
		image = {Right = "2em"},
		text = {Left = "2em"}
	};
	
		
	// Add info message for every defender
	for (var firemode in this->~GetFiremodes())
	{
		var is_available = firemode.condition == nil || Call(firemode.condition);
		
		if (!is_available) continue;
		
		var firemode_symbol = firemode.icon ?? this;

		PushBack(menu_entries,
		{
		    symbol = firemode_symbol,
		    extra_data = firemode.name,
			custom = 
			{
				Prototype = custom_entry,
				Priority = GUI_PRIORITY_FIREMODE,
				text = {Prototype = custom_entry.text, Text = firemode.name},
				image = {Prototype = custom_entry.image, Symbol = firemode_symbol},
			}
		});
	}

	return menu_entries;
}

public func OnGUIHoverFiremode(id symbol, string action, desc_menu_target, menu_id)
{
	// do nothing at the moment
}

public func OnGUIChangeFiremode(id symbol, string action, bool alt)
{
	// do nothing on click, or maybe let the clonk play an idle animation :p
}

