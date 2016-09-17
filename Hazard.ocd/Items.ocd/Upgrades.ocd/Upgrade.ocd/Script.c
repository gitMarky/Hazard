
func ControlUse(object user, int x, int y)
{
	CreateUpgradeMenu(user);
	return true;
}

func CreateUpgradeMenu(object user)
{
	// create menu
	user->CreateMenu(GetID(), this, 4, "$NothingUpgradeable$");
	
	for (var upgradeable in GetUpgradeable(user)) 
	{
		var name = Format("$Upgrade$", upgradeable->GetName());
		// fill the menu with menu items
		var description = upgradeable->~GetUpgradeDescription(GetID()) ?? Format("$UpgradeDefault$", this->GetName());
		user->AddMenuItem(name, "UpgradeObject", upgradeable->GetID(), nil, upgradeable, description);
	}
}


func GetUpgradeable(object user)
{
	return FindObjects(Find_Or(Find_Container(user), Find_And(Find_Category(C4D_Vehicle), Find_AtPoint(0, -1))), Find_Func("IsUpgradeable", this->GetID()));
}

func UpgradeObject(id def, object target)
{
	DoUpgrade(target);
}

func DoUpgrade(object target)
{
	if (target->~Upgrade(GetID()))
	{
		Sound("UI::Select");
		return RemoveObject();
	}
}
