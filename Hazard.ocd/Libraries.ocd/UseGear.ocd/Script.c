/* Context Use equipment functionality */

/*
   Objects that want to access the full functionality have to ensure the following
   conditions... the first condition is required, the others are optional:
   
   * Call "_inherited(...)" in "Construction" if the function is overloaded
   
   * Call "_inherited(...)" in "OnDmg" as to handle the damage correctly

   * Call "_inherited(...)" in "OnHit" for additional effects
     (for example the shield generator flashes here)
     
   * Call "_inherited(...)" in "Death"
     (for example if the Clonk should drop equipment on death)

*/


local lib_gear;


// Create array
func Initialize()
{
	lib_gear = [];
	_inherited(...);
}


func RejectCollect(id type, object item)
{
	var rejected = _inherited(type, item, ...);
	if (rejected) return rejected;
	
	// prevent collection of equipped gear
	for (var gear in lib_gear)
	{
		if (gear && gear->GetID() == type)
		{
			return true;
		}
	}
	
	// allow collection
	return false;
}

public func HasInteractionMenu()
{
	var has_interaction;
	if (this.HasInteractionMenu == nil)
	{
		has_interaction = true;
	}
	else
	{
		has_interaction = _inherited(...);
	}
	
	return has_interaction;
}


// Drop the equipment
func Death()
{
	if (HasGear())
		TakeOffGear();
	_inherited(...);
}

// Allows modification of the damage
// TODO: This has to be synchronized with the system in Shooter Library
func OnDmg(int iDamage, int iType)
{
	var before = _inherited(iDamage, iType);
	
	var add = before;
	var gear;
	for (gear in lib_gear) 
	{
		// not null...
		if (gear)
		{
			add += (gear->~OnClonkDmg(iDamage, iType, this));
		}
	}
	return add;
}

// Show effects on hit?
func OnHit(int iDmg, int iType, object pFrom)
{
	_inherited(iDmg, iType, pFrom);
	
	// forward the call...
	for (var gear in lib_gear) 
		if (gear)
			gear->~OnClonkHit(iDmg, iType, this);
}

/* Context menu */

// Using the equipment
func ContextUseEquipment(object caller)
{
// TODO	[$CtxUseEquipmentDesc$|Image=HARM|Condition=HasUsableGear]
	if (!HasUsableGear()) return;
	CreateMenu(HARM, this, nil, nil, nil, C4MN_Style_Context);
	// display all usable items
	for (var i = 0; i < GetLength(lib_gear); ++i)
	{
		var gear = lib_gear[i];
		if (gear)
			if (gear->~ConUseable())
				AddMenuItem(gear->ConDesc(), "UseEquipment", gear->GetID(), nil, i);
	}
	return true;
}

// Drop equipment
func ContextUnbuckle(object caller)
{
// TODO	[$CtxUnbuckleDesc$|Image=HARM|Condition=FunnyBug]
	if (!HasGear()) return;
	CreateMenu(HARM, this, nil, nil, nil, C4MN_Style_Context);
	// display all droppable items
	for (var i; i < GetLength(lib_gear); ++i)
	{
		var gear = lib_gear[i];
		if (gear)
			AddMenuItem("$CtxUnbuckleItem$", Format("TakeOffGear(0,%d)", i), gear->GetID());
	}
	return true;
}


/* Status functions */

// Object has gear that can be used
func HasUsableGear()
{
	// returns true if there is at least one usable piece of equipment
	var gear;
	for (gear in lib_gear) 
	{
		if (gear)
			if (gear->~ConUseable())
				return true;
	}
}

// Does the object wear a certain piece of equipment?
// Alternatively you can search for certain equipment by passing gear_type.
// Passing nil searches for any gear
func HasGear(gear_type)
{
	// look for a certain ID
	var gear;
	if (GetType(gear_type) == C4V_Def)
	{
		for (gear in lib_gear)
		{ 
			if (gear && gear->GetID() == gear_type)
					return gear;
		}
		return false;
	}
	
	// look for a certain type
	if (GetType(gear_type) == C4V_Int)
	{
		if (lib_gear[gear_type])
			return true;
		return false;
	}

	// no parameter: is anything equipped?
	if (gear_type == nil)
	{
		for (gear in lib_gear) 
			if (gear)
				return true;
	}
	return false;
}

func CanUse(id def)
{
	if (def->~IsHazardGear())
		return true;
	return _inherited(def);
}



/* Use */

func UseEquipment(id bla, int i)
{
	if (lib_gear[i])
		lib_gear[i]->ConUse(this);
}


func TakeOffGear(object pGear, int iGearType)
{
	var geartype = iGearType;
	
	// since you can pass a certain object
	if (!geartype)
	{
		// no paramter => take off everything
		if (!pGear)
		{
			var i;
			for (var i = 0; i < GetLength(lib_gear); ++i)
				if (lib_gear[i])
					TakeOffGear(nil, i);
			return true;
		}
		
		geartype = pGear->GetGearType();
		// object is not equipped?
		if (lib_gear[geartype] != pGear)
			return false;
	}
	else
	{
		// object is not equipped?
		if (!HasGear(geartype))
			return false;
	}

	// take off the gear
	lib_gear[geartype]->GearUnbuckle(this);
	
	// collect it, if possible
	if (lib_gear[geartype])
		Collect(lib_gear[geartype]);
	
	// delete from the array
	lib_gear[geartype] = 0;
	return true;
}


func EquipGear(object pGear)
{
	// Is it even usable?
	if (!pGear) return false;
	if (!CanUse(pGear)) return false;
	// Already wearing such a thing?
	var geartype = pGear->GetGearType();
	if (HasGear(geartype)) return false;

	// save it
	lib_gear[geartype] = pGear;
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GUI

static const GUI_PRIORITY_EQUIPMENT = 20;

public func GetInteractionMenus(object crew)
{
	var menus = _inherited(crew) ?? [];		

	var equipment_menu =
	{
		title = "$GUI_Manage_Equipment$",
		entries_callback = this.GetGUIEquipmentMenuEntries,
		callback = "OnGUIClickEquipment",
		callback_hover = "OnGUIHoverEquipment",
		callback_target = this,
		BackgroundColor = GetGUIEquipmentMenuColor(),
		Priority = GUI_PRIORITY_EQUIPMENT,
	};

	PushBack(menus, equipment_menu);
	return menus;
}


public func GetGUIEquipmentMenuColor(){ return RGB(100, 100, 100);}

public func GetGUIEquipmentMenuEntries(object crew)
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
	for (var equipped_gear in lib_gear)
	{
		if (!equipped_gear) continue;
	
		var gear_symbol = equipped_gear;

		PushBack(menu_entries,
		{
		    symbol = gear_symbol,
		    extra_data = equipped_gear->GetName(),
			custom = 
			{
				Prototype = custom_entry,
				Priority = GUI_PRIORITY_EQUIPMENT,
				text = {Prototype = custom_entry.text, Text = equipped_gear->GetName()},
				image = {Prototype = custom_entry.image, Symbol = gear_symbol},
			}
		});
	}

	return menu_entries;
}

public func OnGUIHoverEquipment(id symbol, string action, desc_menu_target, menu_id)
{
	// do nothing at the moment
}

public func OnGUIClickEquipment(id symbol, string action, bool alt)
{
	// do nothing on click
}

