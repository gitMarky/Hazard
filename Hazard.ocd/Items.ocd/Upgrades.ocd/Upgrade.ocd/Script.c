
local active_menu;

func ControlUse(object user, int x, int y)
{
	CreateUpgradeMenu(user);
	return true;
}

func CreateUpgradeMenu(object user)
{
	CloseUpgradeMenu();
	
	// if the menu is already open, don't open another instance.
	if (user->~GetMenu()) return;	
	
	var description_top = "70%";
	var header_size = "+2em";
	
	// create a menu
	var main_menu = 
	{
		Decoration = GUI_MenuDeco,
		Left = "30%", Right = "70%", Top = "20%", Bottom = "80%",
		header = {Bottom = header_size, Text = "$ChooseUpgradeable$", Style = GUI_TextHCenter | GUI_TextVCenter, BackgroundColor = GUI_MenuDeco->SolidBackClr(), icon = {Left = "0.1em", Right = Format("0.1em %s", header_size), actual_icon = { Symbol = this, Left = "20%", Right = "80%", Top = "20%", Bottom = "80%"}}},
		body = {Top = header_size, 
		        list_display = {Left = "0.2em", Bottom = description_top},
		        description_display = {Top = description_top, BackgroundColor = GUI_MenuDeco->SolidBackClr(), text_field = {ID = 9999, Left = "0.6em", Right = "100%-0.5em"}}},
	};
	GuiAddCloseButton(main_menu, this, "CloseUpgradeMenu");
	active_menu = {};
	
	// fill with contents
	var available_items = GetUpgradeable(user);
	if (GetLength(available_items) == 0)
	{
		main_menu.body.list_display.Style = GUI_TextHCenter | GUI_TextVCenter;
		main_menu.body.list_display.Text = "$NothingUpgradeable$";
	}
	else
	{
		var upgrades_list = CreateObject(MenuStyle_List);
		main_menu.body.list_display.list = upgrades_list;
		
		upgrades_list->SetMouseOverCallback(this, "UpgradeMenuOnHover");

		for (var upgradeable in available_items) 
		{
			var name = Format("$Upgrade$", upgradeable->GetName());
			var description = upgradeable->~GetUpgradeDescription(GetID()) ?? Format("$UpgradeDefault$", this->GetName());
	
			upgrades_list->AddItem(upgradeable->GetID(), name, nil, this, this.UpgradeObject, {Target = upgradeable, Info = description});
		}
	}
	
	active_menu.user = user;
	active_menu.ID = GuiOpen(main_menu);
	active_menu.user->~SetMenu(active_menu.ID);
}

func CloseUpgradeMenu()
{
	if (active_menu)
	{
		GuiClose(active_menu.ID);
		if (active_menu.upgrade_list) active_menu.upgrade_list->RemoveObject();
		if (active_menu.user) active_menu.user->MenuClosed();
	}
	active_menu = nil;
}	

func UpgradeMenuOnHover(proplist upgrade, int ID)
{
	GuiUpdateText(upgrade.Info, active_menu.ID, 9999);
}

func GetUpgradeable(object user)
{
	return FindObjects(Find_Or(Find_Container(user), Find_And(Find_Category(C4D_Vehicle), Find_AtPoint(0, -1))), Find_Func("IsUpgradeable", this->GetID()));
}

func UpgradeObject(proplist upgrade)
{
	DoUpgrade(upgrade.Target);
}

func DoUpgrade(object target)
{
	if (target->~Upgrade(GetID()))
	{
		Sound("UI::Select");
		return RemoveObject();
	}
}

func Destruction()
{
	CloseUpgradeMenu();
	_inherited(...);
}
