#appendto Dialogue

/////////////////////////////////////////////////////////////////////
//
// Doc

public func Dlg_Doc_Init(object clonk)
{
	return true;
}

public func Dlg_Doc_1(object clonk)
{
	MessageBox("$Doc1$", clonk, dlg_target, nil, false, ["$DocWeapon$"]);
	return true;
}

public func Dlg_Doc_2(object clonk)
{
	MessageBox("$Doc2$", clonk, dlg_target, nil, false, ["$DocThx$"]);
	StopDialogue();
	return true;
}

//public func Dlg_Doc_3(object clonk)
//{
//	StopDialogue();
//	return true;
//}

public func Dlg_Doc_Closed(object clonk)
{
	SetDialogueProgress(5);
	
	if (!IsValueInArray(scenario_progress, TUTORIAL_HAS_PISTOL))
	{
		clonk->CreateContents(Weapon_Pistol);
		PushBack(scenario_progress, TUTORIAL_HAS_PISTOL);
	}
	return true;
}

public func Dlg_Doc_5(object clonk)
{
	MessageBox("$DocEasterEgg$", clonk, dlg_target, nil, true);
	SetDialogueProgress(5);
	StopDialogue();
	return true;
}
