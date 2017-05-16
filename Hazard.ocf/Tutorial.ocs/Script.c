static screen, doc, door1, door2, drone, tele, tele2, killcounter;
static screen_dlg;
static scenario_progress;
static intro_init;


func Initialize()
{
	scenario_progress = [];

	CreateMainHall();
	CreateHallwayToLift();
	CreateDoc();
	CreateConsoleRoom();
	CreateBathRoom();
	CreateLockerRoom();
	CreateStaffRoom();
	CreateInaccessibleBase();
	CreateSteelDoors();
	CreateMissileBase();
	CreateOutdoorArea();
	CreateTeleporters();
	CreateCaveStuff();
	CreateStoreRoom();
}

func CreateMainHall()
{
//	door2 = CreateObjectAbove(HNG2, 60, 910, NO_OWNER);
//	door2->~Opened();

	// large screen
	screen = CreateObject(CommunicationScreen, 283, 788, NO_OWNER);
	screen->SetColor(RGB(225, 195, 80));
	screen_dlg = screen->SetDialogue("CommanderIntro", false);

	// small screen
	CreateObjectAbove(SCR2, 283, 860, NO_OWNER);

	CreateObject(BLGH, 210, 840, NO_OWNER)->TurnOn();
	CreateObject(BLGH, 352, 840, NO_OWNER)->TurnOn();

	// other
//	CreateObjectAbove(RAI1, 918,  80, NO_OWNER)->SetRail([0, 1, 4],1);
//	CreateObjectAbove(LADR,1880, 220, NO_OWNER)->Set(10);
//	CreateObjectAbove(RAI1, 490, 240, NO_OWNER)->SetRail([0, 1, 1, 1, 1, 1, 4],1);
//	CreateObjectAbove(CONS, 500, 322, NO_OWNER);

//	CreateObjectAbove(LADR, 560, 570, NO_OWNER)->Set(4);
	CreateObjectAbove(LFTP, 675, 550, NO_OWNER);
//	CreateObjectAbove(SLDR, 587, 600, NO_OWNER)->Lock();
//	CreateObjectAbove(PKEY, 609, 594, NO_OWNER);
//	
//	CreateObjectAbove(VENT,  25, 669, NO_OWNER)->SetCon(35);
//	CreateObjectAbove(VENT, 505, 669, NO_OWNER)->SetCon(35);
//	CreateObjectAbove(LADR, 315, 710, NO_OWNER)->Set(4);
//	CreateObjectAbove(CCP1, 570, 690, NO_OWNER);
//	
//	
//	CreateObjectAbove(LADR, 398, 910, NO_OWNER)->Set(15);
//	CreateObjectAbove(LBDR, 452, 791, NO_OWNER);
//	CreateObjectAbove(GLST, 499, 790, NO_OWNER);
//	CreateObjectAbove(GLST, 474, 790, NO_OWNER);
//	CreateObjectAbove(LLGH, 539, 774, NO_OWNER);
//	CreateObjectAbove(MONI, 587, 778, NO_OWNER);
//	CreateObjectAbove(LTBL, 593, 789, NO_OWNER);
	CreateObjectAbove(LFTP, 905, 785, NO_OWNER);
//	CreateObjectAbove(BLGH, 210, 839, NO_OWNER);
//	CreateObjectAbove(BLGH, 352, 840, NO_OWNER);
//	CreateObjectAbove(GAT2, 736, 842, NO_OWNER);
//	CreateObjectAbove(GAT2, 832, 844, NO_OWNER);

	CreateObjectAbove(LFTP, 675, 920, NO_OWNER);

}

func CreateHallwayToLift()
{
	CreateObject(CLGH, 506, 851, NO_OWNER)->TurnOn();
	CreateObject(CLGH, 602, 851, NO_OWNER)->TurnOn();
	CreateObject(PLT2, 558, 886, NO_OWNER); // plant
	CreateObject(CLVM, 528, 890, NO_OWNER); // vending machine
	CreateObject(SPVM, 497, 890, NO_OWNER); // vending machine
	CreateObject(STRP, 550, 867, NO_OWNER)->SetWidth(200)->SetSkew(-1)->SetColor(RGB(255, 0, 0));
}

func CreateConsoleRoom()
{
	// main console room
	CreateObject(GAT2, 732, 834, NO_OWNER);
	CreateObject(GAT2, 832, 834, NO_OWNER);
	CreateObject(CCP2, 734, 894, NO_OWNER);
	CreateObject(CCP1, 779, 898, NO_OWNER);
	CreateObject(CCP1, 814, 898, NO_OWNER);
	CreateObject(PLT2, 848, 886, NO_OWNER);
	CreateObject(SEDR, 710, 895, NO_OWNER)->Lock();
	CreateObject(STDR, 876, 896, NO_OWNER);
	
	// small console room
	CreateObject(SEDR, 640, 675, NO_OWNER)->Lock();
	CreateObject(CCP1, 570, 678, NO_OWNER);
}

func CreateBathRoom()
{
	CreateObject(CLGH,1005, 871, NO_OWNER)->TurnOn();
	CreateObject(STDR, 937, 905, NO_OWNER);
	CreateObject(WSHB, 959, 906, NO_OWNER);
	CreateObject(WSHB, 979, 906, NO_OWNER);
	CreateObject(TOIC,1009, 905, NO_OWNER);
	CreateObject(TOIC,1049, 905, NO_OWNER);
	CreateObject(TOIC,1029, 905, NO_OWNER)->SetDir(1);
}

func CreateLockerRoom()
{
	CreateObject(CLGH, 1005, 811, NO_OWNER)->TurnOn();

	CreateObject(STDR, 935, 846, NO_OWNER);
	CreateObject(TABL, 968, 853, NO_OWNER);
	CreateObject(FIEX, 993, 847, NO_OWNER);
	CreateObject(LCKR,1039, 845, NO_OWNER);
	CreateObject(LCKR,1024, 845, NO_OWNER);
	CreateObject(LCKR,1009, 845, NO_OWNER);
	CreateObject(LCKR,1054, 845, NO_OWNER);
}

func CreateStaffRoom()
{
	// first room with table
	CreateObject(SEDR, 710, 785, NO_OWNER)->Lock();
	CreateObject(CLGH, 790, 741, NO_OWNER)->TurnOn();
	CreateObject(CLVM, 753, 780, NO_OWNER);
	CreateObject(CHAR, 796, 791, NO_OWNER);
	CreateObject(CHAR, 844, 791, NO_OWNER)->SetDir(1);
	CreateObject(TABL, 820, 793, NO_OWNER);
	CreateObject(PSTR, 802, 766, NO_OWNER)->Set(0, 2);
	CreateObjectAbove(STDR, 875, 786, NO_OWNER);


	// beds
	CreateObject(SEDR, 710, 675, NO_OWNER)->Lock();
	CreateObject(CLGH, 783, 641, NO_OWNER)->TurnOn();
	CreateObject(CLGH, 904, 641, NO_OWNER)->TurnOn();
	CreateObject(PSTR, 811, 683, NO_OWNER)->Set(2, 3);
	CreateObject(BED2, 836, 689, NO_OWNER);
	CreateObject(BED2, 879, 689, NO_OWNER);
	CreateObject(BED2, 921, 689, NO_OWNER);
	
}

func CreateStoreRoom()
{
	CreateObject(GSBO, 1017, 759, NO_OWNER);
	CreateObject(GSBO, 1026, 759, NO_OWNER);
	CreateObject(ENGT, 1057, 746, NO_OWNER);
}

func CreateInaccessibleBase()
{
	CreateObjectAbove(WNDW,1608, 231, NO_OWNER);

//	CreateObjectAbove(HNG2, 705, 910, NO_OWNER);
//	CreateObjectAbove(LFTP, 895, 920, NO_OWNER);
//	CreateObjectAbove(PMP2, 820, 920, NO_OWNER);
//	CreateObjectAbove(TABL, 980, 770, NO_OWNER);
//	CreateObjectAbove(CHAR, 1020, 770, NO_OWNER);
//	CreateObjectAbove(GAT2, 1050, 760, NO_OWNER);
	CreateObjectAbove(LADR, 316, 710, NO_OWNER)->LadderHeight(672, 710);
	CreateObjectAbove(LADR, 566, 570, NO_OWNER)->LadderHeight(542, 574);
	CreateObjectAbove(LADR, 1888, 220, NO_OWNER)->LadderHeight(141, 221);
//	CreateObjectAbove(LLGH, 920, 710, NO_OWNER);
//	CreateObjectAbove(LFTP, 685, 550, NO_OWNER);
//	CreateObjectAbove(PSTR, 810, 690, NO_OWNER);
//	CreateObjectAbove(CONS, 500, 320, NO_OWNER);
//	CreateObjectAbove(RAI1, 490, 240, NO_OWNER)->SetRailLength(5);
	CreateObjectAbove(ENGT, 640, 70, NO_OWNER);
	CreateObjectAbove(SCR1, 860, 60, NO_OWNER);
//	CreateObjectAbove(LCKR, 950, 860, NO_OWNER);
//	CreateObjectAbove(LCOM, 950, 910, NO_OWNER);
//	CreateObjectAbove(RAI1, 918, 80, NO_OWNER)->SetRailLength(1);
//	CreateObjectAbove(RADR, 1633, 160, NO_OWNER);
//	CreateObjectAbove(LFTP, 180, 600, NO_OWNER)->EnableHorizontal();
//	CreateObjectAbove(GLST, 860, 710, NO_OWNER);
}

func CreateSteelDoors()
{
	var door = CreateObject(SLDR, 597, 585, NO_OWNER);
	door->Lock();
	door->SetMaxDamage(-1);
	//CreateObject(PKEY, 620, 589, NO_OWNER)->Set(door, 1337);
	door1 = CreateObject(SLDR, 726, 585, NO_OWNER);
	door1->Lock();
	var wl = CreateObject(ALGH, 710, 575, NO_OWNER);
	wl->SetR(180);
	wl->TurnOn();
}

func CreateMissileBase()
{
	CreateObject(X5RK, 280, 400, NO_OWNER);
	CreateObject(X5ST, 282, 431, NO_OWNER)->SetDir(0);
}


func CreateOutdoorArea()
{
	CreateObjectAbove(FENC, 965, 600, NO_OWNER);
	CreateObjectAbove(FENC, 904, 600, NO_OWNER);
	CreateObjectAbove(FENC, 843, 600, NO_OWNER);
	CreateObjectAbove(FENC, 782, 600, NO_OWNER);
	CreateObjectAbove(FENC, 1120, 600, NO_OWNER);
		
	CreateObject(Arena_JumpPad, 1107, 586, NO_OWNER)->SetStrength(70)->SetPadR(-5);
	CreateObject(SBBA, 1407, 592, NO_OWNER);
	
	CreateObject(Tree_Coniferous2, 1775, 420, NO_OWNER)->SetR(3);
	CreateObject(Tree_Coniferous, 1821, 406, NO_OWNER);
	CreateObject(Tree_Coniferous_Burned, 1846, 406, NO_OWNER)->SetR(2);
	CreateObject(Tree_Coniferous, 1874, 460, NO_OWNER)->SetR(7);
	CreateObject(Tree_Coniferous, 1521, 477, NO_OWNER);
	CreateObject(Tree_Coniferous2, 1650, 452, NO_OWNER)->SetR(-5);
	CreateObject(Tree_Coniferous4_Burned, 1680, 456, NO_OWNER);
	CreateObject(Tree_Deciduous_Burned, 1762, 433, NO_OWNER)->SetR(-8);
	CreateObject(Tree_Coniferous4, 1920, 438, NO_OWNER);
	CreateObject(Tree_Coniferous2, 1417, 496, NO_OWNER);
	CreateObject(Tree_Coniferous4, 1508, 493, NO_OWNER)->SetR(-10);
	CreateObject(Tree_Coniferous, 1703, 433, NO_OWNER)->SetR(5);
}


func CreateTeleporters()
{
	tele = CreateObject(TELE, 1045, 574, NO_OWNER);	
	tele2 = CreateObject(TELE, 1367, 945, NO_OWNER);
	tele->Deactivate();
	tele->SetTarget(tele2);
	tele2->Activate();
	tele2->SetTarget(tele);
}

func CreateCaveStuff()
{
	CreateObjectAbove(Weapon_GrenadeLauncher, 1600, 970, NO_OWNER);

	CreateObject(Arena_JumpPad, 1511, 925, NO_OWNER)->SetStrength(50)->SetPadR(250)->SetBaseR(180);
	CreateObject(Arena_JumpPad, 1510, 967, NO_OWNER)->SetStrength(50)->SetPadR(-70);
	CreateObject(Arena_JumpPad, 1490, 967, NO_OWNER)->SetStrength(30)->SetPadR(-45);

	CreateObject(FLGH, 1470, 962, NO_OWNER)->SetRotation(-45)->GetLight()->TurnOn();
	CreateObject(FLGH, 1550, 962, NO_OWNER)->SetRotation(35)->GetLight()->TurnOn();
}


func CreateDoc()
{
	//THE DOC! and his lab
	doc = CreateObject(Clonk, 521, 780, NO_OWNER);
	doc->SetName("Doc");
	doc->RemoveBackpack();
	doc->SetGraphics(nil, Local_Characters);
	doc->SetMeshMaterial("Clonk_HazardDoctor");
	doc->SetMeshMaterial("Clonk_HazardDoctor", 1);
	doc->SetColor(RGB(230, 230, 230));
	doc->SetLightRange(80, 80);
	doc.portrait = {Source = Local_Characters, Name = Format("PortraitDoc")};
	doc->SetAction("Jump");
	doc->SetDir(DIR_Left);


	CreateObjectAbove(LADR, 397, 910, NO_OWNER)->LadderHeight(790, 910);
	CreateObject(STDR, 454, 775, NO_OWNER);
	CreateObject(LTBL, 519, 779, NO_OWNER);  
	CreateObject(MONI, 511, 773, NO_OWNER);
	CreateObject(PLNT, 477, 787, NO_OWNER);
	CreateObject(GSBO, 544, 779, NO_OWNER);
	CreateObject(GSBO, 552, 779, NO_OWNER);
	CreateObject(FRAM, 524, 752, NO_OWNER);
	
	CreateObject(LLGH, 490, 768, NO_OWNER)->TurnOn();
	CreateObject(LLGH, 578, 768, NO_OWNER)->TurnOn();
	CreateObject(GLST, 601, 768, NO_OWNER);
	CreateObject(GLST, 627, 768, NO_OWNER);
}


func InitializePlayer(int player)
{
	_inherited(...);
	var crew = GetCrew(player);
	crew->SetPosition(50, 899);
	
	// Initialize the intro sequence if not yet started.
	if (!intro_init)
	{
		StartSequence("Tutorial", 0);
		intro_init = true;
	}
}
