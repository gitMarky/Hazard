#include Clonk
#include Library_AmmoManager
#include Library_Agility
#include Library_UseGear


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Properties

local MaxWeaponsCount = 3; // this many weapons can be collected
local MaxEquipmentCount = 2; // this many equipment items can be collected
local MaxEnergy = 150000; // 150 HP

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
	
	gender = 0;
	
	SetHazardSkin();

	RemoveBackpack(); // remove the backpack
}

func SetSkinUpdateModel()
{
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
	SetGraphics(nil);
	SetSkinUpdateModel();
}

func SetHazardArmorSkin()
{
	SetGraphics("Armor");
	SetSkinUpdateModel();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HUD


public func UpdateHazardHUD()
{
    var weapon = GetCurrentItem();

    var hud = this->GetHazardHUD();
    if (hud)
    {
    	hud->~Update(weapon, this, this);
    	ScheduleCall(this, this.UpdateHazardHUD, 1);
    }
}


public func GetCurrentItem()
{
	return this->GetHandItem(0);
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

func HasActionProcedure(bool force_landscape_letgo)
{
	var has_action_procedure = _inherited(force_landscape_letgo, ...);
	
	if (has_action_procedure)
	{
		return true;
	}
	else
	{
		// Check if the clonk is currently in an action where he could use his hands
		// if force_landscape_letgo is true, also allow during scale/hangle assuming the clonk will let go
		var action = GetAction();
		return (action == "JetpackFlight");
	}
}


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
