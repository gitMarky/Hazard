#appendto Dialogue

/////////////////////////////////////////////////////////////////////
//
// Intro

public func Dlg_CommanderIntro_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderIntro_1(object clonk)
{
	MessageBox("$Intro1$", clonk, dlg_target);
	return true;
}

public func Dlg_CommanderIntro_2(object clonk)
{
	MessageBox("$Intro2$", clonk, dlg_target);
	return true;
}

public func Dlg_CommanderIntro_3(object clonk)
{
	MessageBox("$Intro3$", clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderIntro_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	PushBack(scenario_progress, TUTORIAL_FINISHED_INTRO);
	doc->SetDialogue("Doc", true);
	return true;
}

/////////////////////////////////////////////////////////////////////
//
// Ammo

public func Dlg_CommanderAmmo_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderAmmo_1(object clonk)
{
	MessageBox("$Tutor1$", clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderAmmo_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}

/////////////////////////////////////////////////////////////////////
//
// Target drone with aiming

public func Dlg_CommanderDrone1_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderDrone1_1(object clonk)
{
	MessageBox("$Tutor2$", clonk, dlg_target);
	return true;
}

public func Dlg_CommanderDrone1_2(object clonk)
{
	MessageBox("$Tutor2b$", clonk, dlg_target);
	return true;
}

public func Dlg_CommanderDrone1_3(object clonk)
{
	MessageBox(Format("$Tutor3$", GetButtonText(CON_Use)), clonk, dlg_target);
	return true;
}

public func Dlg_CommanderDrone1_4(object clonk)
{
	MessageBox(Format("$Tutor4$", GetButtonText(CON_Use), GetButtonText(CON_UseAlt)), clonk, dlg_target); // TODO: insert button for actual reloading as second placeholder
	StopDialogue();
	return true;
}

public func Dlg_CommanderDrone1_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}

/////////////////////////////////////////////////////////////////////
//
// Target drone that moves

public func Dlg_CommanderDrone2_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderDrone2_1(object clonk)
{
	MessageBox("$Tutor5$", clonk, dlg_target);
	return true;
}

public func Dlg_CommanderDrone2_2(object clonk)
{
	MessageBox("$Tutor6$", clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderDrone2_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}

/////////////////////////////////////////////////////////////////////
//
// Move to teleporter

public func Dlg_CommanderTeleporter_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderTeleporter_1(object clonk)
{
	MessageBox("$Tutor7$", clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderTeleporter_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}

/////////////////////////////////////////////////////////////////////
//
// Get the grenade launcher

public func Dlg_CommanderGLauncher_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderGLauncher_1(object clonk)
{
	MessageBox("$Tutor8$", clonk, dlg_target);
	return true;
}

public func Dlg_CommanderGLauncher_2(object clonk)
{
	MessageBox("$Tutor9$", clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderGLauncher_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}

/////////////////////////////////////////////////////////////////////
//
// Hit the drone with a grenade

public func Dlg_CommanderDrone3_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderDrone3_1(object clonk)
{
	MessageBox("$Tutor10$", clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderDrone3_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}

/////////////////////////////////////////////////////////////////////
//
// Hit the next drone

public func Dlg_CommanderDrone4_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderDrone4_1(object clonk)
{
	MessageBox("$Tutor11$", clonk, dlg_target);
	return true;
}

public func Dlg_CommanderDrone4_2(object clonk)
{
	MessageBox("$Tutor11b$", clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderDrone4_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}

/////////////////////////////////////////////////////////////////////
//
// Explain upgrades

public func Dlg_CommanderUpgrade_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderUpgrade_1(object clonk)
{
	MessageBox("$Tutor12$", clonk, dlg_target);
	return true;
}

public func Dlg_CommanderUpgrade_2(object clonk)
{
	MessageBox("$Tutor13$", clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderUpgrade_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}

/////////////////////////////////////////////////////////////////////
//
// Explain firemodes

public func Dlg_CommanderFiremode_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderFiremode_1(object clonk)
{
	MessageBox("$Tutor14$", clonk, dlg_target);
	return true;
}

public func Dlg_CommanderFiremode_2(object clonk)
{
	MessageBox("$Tutor15$", clonk, dlg_target);
	return true;
}

public func Dlg_CommanderFiremode_3(object clonk)
{
	MessageBox("$Tutor16$", clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderFiremode_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}

/////////////////////////////////////////////////////////////////////
//
// Explain jetpack

public func Dlg_CommanderJetpack1_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderJetpack1_1(object clonk)
{
	MessageBox("$Tutor17$", clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderJetpack1_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}

public func Dlg_CommanderJetpack2_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderJetpack2_1(object clonk)
{
	MessageBox("$Tutor18$", clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderJetpack2_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}

/////////////////////////////////////////////////////////////////////
//
// Hit another drone

public func Dlg_CommanderDrone5_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderDrone5_1(object clonk)
{
	MessageBox("$Tutor19$", clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderDrone5_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}

/////////////////////////////////////////////////////////////////////
//
// Hit another drone

public func Dlg_CommanderDrone6_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderDrone6_1(object clonk)
{
	MessageBox("$Tutor20$", clonk, dlg_target);
	return true;
}

public func Dlg_CommanderDrone6_2(object clonk)
{
	MessageBox("$Tutor21$", clonk, dlg_target);
	return true;
}

public func Dlg_CommanderDrone6_3(object clonk)
{
	MessageBox("$Tutor22$", clonk, dlg_target);
	return true;
}

public func Dlg_CommanderDrone6_4(object clonk)
{
	MessageBox("$Tutor23$", clonk, dlg_target);
	return true;
}

public func Dlg_CommanderDrone6_5(object clonk)
{
	MessageBox("$Tutor24$", clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderDrone6_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}

/////////////////////////////////////////////////////////////////////
//
// Explain homing missiles

public func Dlg_CommanderHoming_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderHoming_1(object clonk)
{
	MessageBox("$Tutor25$", clonk, dlg_target);
	return true;
}

public func Dlg_CommanderHoming_2(object clonk)
{
	MessageBox("$Tutor26$", clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderHoming_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}


/////////////////////////////////////////////////////////////////////
//
// Go to the warehouse

public func Dlg_CommanderWarehouse_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderWarehouse_1(object clonk)
{
	MessageBox("$Tutor27$", clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderWarehouse_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}

/////////////////////////////////////////////////////////////////////
//
// Explain mote gun

public func Dlg_CommanderMoteGun_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderMoteGun_1(object clonk)
{
	MessageBox("$Tutor28$", clonk, dlg_target);
	return true;
}

public func Dlg_CommanderMoteGun_2(object clonk)
{
	MessageBox("$Tutor29$", clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderMoteGun_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}
/////////////////////////////////////////////////////////////////////
//
// Explain minigun

public func Dlg_CommanderMinigun_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderMinigun_1(object clonk)
{
	MessageBox("$Tutor30$", clonk, dlg_target);
	return true;
}

public func Dlg_CommanderMinigun_2(object clonk)
{
	MessageBox("$Tutor31$", clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderMinigun_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}


/////////////////////////////////////////////////////////////////////
//
// Hit another drone

public func Dlg_CommanderEnd_Init(object clonk)
{
	return true;
}

public func Dlg_CommanderEnd_1(object clonk)
{
	MessageBox(Format("$TutorEND$", clonk->GetName()), clonk, dlg_target);
	StopDialogue();
	return true;
}

public func Dlg_CommanderEnd_Closed(object clonk)
{
	clonk->Sound(SOUND_ACK);
	return true;
}

private func GetButtonText(int button)
{
	return Format("<c %s>[%s]</c>", GUI_COLOR_TEXT, GetPlayerControlAssignment(0, button, true));
}