#include Library_DefaultScript

static switchright, switchleft;

func Initialize()
{
	SetGoal(SCENPAR_HAZARD_GOAL);

	_inherited(...);

	CreateLadders();
}

func CreateBackground()
{
	SetSkyParallax(0, 45, 24, 0, 0, 0, 0);
	CreateObjectAbove(_DCK, 220, 360, NO_OWNER);
	CreateObjectAbove(_DCK, 727, 360, NO_OWNER);
}

func CreateLadders()
{
	CreateObject(LADR, 1304, 174, NO_OWNER)->LadderHeight(110, 174);
	CreateObject(LADR, 1207, 600, NO_OWNER)->LadderHeight(480, 600);
	CreateObject(LADR, 1420, 472, NO_OWNER)->LadderHeight(440, 472);
	CreateObject(LADR, 1176, 462, NO_OWNER)->LadderHeight(365, 462);
	CreateObject(LADR,  916, 210, NO_OWNER)->LadderHeight(114, 210);
	CreateObject(LADR, 1026, 350, NO_OWNER)->LadderHeight(294, 350);
	CreateObject(LADR,  781, 350, NO_OWNER)->LadderHeight(230, 350);

	CreateObject(LADR,  721, 350, NO_OWNER)->LadderHeight(230, 350);
	CreateObject(LADR,  476, 350, NO_OWNER)->LadderHeight(294, 350);
	CreateObject(LADR,  587, 210, NO_OWNER)->LadderHeight(114, 210);
	CreateObject(LADR,  326, 462, NO_OWNER)->LadderHeight(365, 462);
	CreateObject(LADR,   82, 472, NO_OWNER)->LadderHeight(440, 472);
	CreateObject(LADR,  295, 600, NO_OWNER)->LadderHeight(480, 600);
	CreateObject(LADR,  196, 174, NO_OWNER)->LadderHeight(110, 174);
}

func CreateDeco()
{
	CreateObject(CRAT, 750, 235, NO_OWNER);

	CreateObject(CRAT, 850, 295, NO_OWNER);
	CreateObject(CRAT, 979, 295, NO_OWNER);
	CreateObject(CRAT, 521, 295, NO_OWNER);
	CreateObject(CRAT, 650, 295, NO_OWNER);

	CreateObject(PLT2, 1473, 96, NO_OWNER);
	CreateObject(PLT2, 27, 96, NO_OWNER);
	CreateObject(TABL, 1438, 113, NO_OWNER);
	CreateObject(TABL, 62, 113, NO_OWNER);
	CreateObject(GSBO, 823, 129, NO_OWNER);
	CreateObject(GSBO, 881, 199, NO_OWNER);
	CreateObject(GSBO, 803, 299, NO_OWNER);
	CreateObject(GSBO, 814, 299, NO_OWNER);
	CreateObject(GSBO, 686, 299, NO_OWNER);
	CreateObject(GSBO, 697, 299, NO_OWNER);
	CreateObject(GSBO, 619, 199, NO_OWNER);
	CreateObject(GSBO, 677, 129, NO_OWNER);
	CreateObject(FLGH, 1092, 634, NO_OWNER)->SetRotation(-70)->GetLight()->TurnOn();
	CreateObject(FLGH, 412, 634, NO_OWNER)->SetRotation(70)->GetLight()->TurnOn();
	CreateObject(SPVM, 1403, 100, NO_OWNER);
	CreateObject(SBBA, 866, 371, NO_OWNER);
	CreateObject(SBBA, 635, 370, NO_OWNER);
	CreateObject(CON1, 897, 291, NO_OWNER);
	CreateObject(CON1, 603, 291, NO_OWNER);
	CreateObject(LFTP, 1415, 347, NO_OWNER);
	CreateObject(LFTP, 85, 347, NO_OWNER);
	CreateObject(CLVM, 98, 100, NO_OWNER);
	CreateObject(GSTA, 1344, 340, NO_OWNER);
	CreateObject(GSTA, 156, 340, NO_OWNER);
	CreateObject(SEDR, 762, 366, NO_OWNER);
	CreateObject(SEDR, 739, 366, NO_OWNER);
	switchright = CreateObject(SLDR, 968, 235, NO_OWNER)->SetSwitchLock(DIR_Right);
	switchleft = CreateObject(SLDR, 525, 235, NO_OWNER)->SetSwitchLock(DIR_Left);
	CreateObject(DEB1, 1027, 628, NO_OWNER)->SetDir(DIR_Right);
	CreateObject(DEB1, 471, 627, NO_OWNER);
	CreateObject(VENT, 749, 417, NO_OWNER)->SetCon(40);
	CreateObject(BART, 773, 83, NO_OWNER);
	CreateObject(BART, 701, 83, NO_OWNER);
	CreateObject(LBGH, 1356, 22, NO_OWNER)->GetLight()->TurnOn();
	CreateObject(ALGH, 1343, 268, NO_OWNER)->SetR(180);
	CreateObject(BLGH, 917, 235, NO_OWNER)->TurnOn();
	CreateObject(BLGH, 1174, 290, NO_OWNER)->TurnOn();
	CreateObject(AWRP, 922, 80, NO_OWNER)->SetDestination(1260, 640);
	CreateObject(RAI1, 1130, 214, NO_OWNER)->SetRailLength(4);
	CreateObject(VENT, 1365, 412, NO_OWNER)->SetCon(30);
	CreateObject(FENC, 1100, 356, NO_OWNER);
	CreateObject(GAT2, 806, 485, NO_OWNER);
	CreateObject(GAT2, 918, 485, NO_OWNER);
	CreateObject(GAT2, 1028, 485, NO_OWNER);
	CreateObject(FIEX, 1259, 105, NO_OWNER);

	CreateObject(ESGN, 1258, 86, NO_OWNER);
	CreateObject(MVNT, 1448, 64, NO_OWNER);
	CreateObject(ENGT, 882, 79, NO_OWNER)->SetCon(75);
	CreateObject(ENGT, 618, 79, NO_OWNER)->SetCon(75);
	CreateObject(MVNT, 49, 64, NO_OWNER);
	CreateObject(ESGN, 241, 86, NO_OWNER);

	CreateObject(FIEX, 242, 105, NO_OWNER);
	CreateObject(GAT2, 472, 485, NO_OWNER);
	CreateObject(GAT2, 582, 485, NO_OWNER);
	CreateObject(GAT2, 694, 485, NO_OWNER);
	CreateObject(FENC, 400, 356, NO_OWNER);
	CreateObject(VENT, 136, 412, NO_OWNER)->SetCon(30);
	CreateObject(RAI1, 291, 214, NO_OWNER)->SetRailLength(4);
	CreateObject(AWRP, 579, 80, NO_OWNER)->SetDestination(240, 640);
	CreateObject(AWRP, 750, 583, NO_OWNER)->SetDestination(750, 200);
	CreateObject(BLGH, 326, 290, NO_OWNER)->TurnOn();
	CreateObject(BLGH, 583, 235, NO_OWNER)->TurnOn();
	CreateObject(ALGH, 157, 267, NO_OWNER)->SetR(180);
	CreateObject(LBGH, 144, 22, NO_OWNER)->GetLight()->TurnOn();
	for (var lift in FindObjects(Find_ID(LFTP))) 
		lift->SetYTop(245);
}

func CreateSpawnPoints()
{
	// configure spawn points
	var config = GetSpawnPointTemplates();

	// place spawn points
	CopySpawnPoint(config.weapon_energy, 220, 110);
	CopySpawnPoint(config.ammo_energy, 250, 110);
	CopySpawnPoint(config.upgrade_rifle, 60, 100);
	CopySpawnPoint(config.item_novodekan, 160, 230);
	CopySpawnPoint(config.weapon_mine, 50, 430);
	CopySpawnPoint(config.ammo_standard, 670, 370);
	CopySpawnPoint(config.weapon_grenade, 685, 190);
	CopySpawnPoint(config.ammo_grenade, 700, 190);
	CopySpawnPoint(config.weapon_flame, 620, 670);
	CopySpawnPoint(config.ammo_gasoline, 640, 670);
	CopySpawnPoint(config.ammo_missile, 730, 480);
	CopySpawnPoint(config.ammo_energy, 720, 30);
	
	CopySpawnPoint(config.weapon_motegun, 750, 30);
	CopySpawnPoint(config.upgrade_laser, 750, 170);
	CopySpawnPoint(config.weapon_pumpgun, 750, 370);
	CopySpawnPoint(config.weapon_bazooka, 750, 480);
	CopySpawnPoint(config.item_armor, 750, 640);
	
	CopySpawnPoint(config.weapon_energy, 1280, 110);
	CopySpawnPoint(config.ammo_energy, 1250, 110);
	CopySpawnPoint(config.upgrade_rifle, 1440, 100);
	CopySpawnPoint(config.item_novodekan, 1340, 230);
	CopySpawnPoint(config.weapon_mine, 1450, 430);
	CopySpawnPoint(config.ammo_standard, 830, 370);
	CopySpawnPoint(config.weapon_grenade, 815, 190);
	CopySpawnPoint(config.ammo_grenade, 800, 190);
	CopySpawnPoint(config.weapon_flame, 880, 670);
	CopySpawnPoint(config.ammo_gasoline, 860, 670);
	CopySpawnPoint(config.ammo_missile, 770, 480);
	CopySpawnPoint(config.ammo_energy, 780, 30);
	
	// remove template spawn points
	RemoveSpawnPointTemplates(config);
}

func CreateWaypoints()
{
	var wp1 = CreateWP(750, 208);
	var wp2 = CreateWP(750, 71);
	var wp3 = CreateWP(750, 290);
	var wp4 = CreateWP(1360, 110);
	var wp5 = CreateWP(1138, 208);
	var wp6 = CreateWP(1061, 239);
	var wp7 = CreateWP(1480, 197);
	var wp8 = CreateWP(878, 270);
	var wp9 = CreateWP(881, 126);
	var wp10 = CreateWP(798, 369);
	var wp11 = CreateWP(893, 198);
	var wp12 = CreateWP(1005, 241);
	var wp13 = CreateWP(1377, 348);
	var wp14 = CreateWP(805, 624);
	var wp15 = CreateWP(1348, 228);
	var wp16 = CreateWP(1197, 208);
	var wp17 = CreateWP(996, 499);
	var wp18 = CreateWP(1098, 490);
	var wp19 = CreateWP(1157, 602);
	var wp20 = CreateWP(999, 298);
	var wp21 = CreateWP(1102, 368);
	var wp22 = CreateWP(1041, 605);
	var wp23 = CreateWP(771, 478);
	var wp24 = CreateWP(848, 498);
	var wp25 = CreateWP(977, 499);
	var wp26 = CreateWP(875, 498);
	var wp27 = CreateWP(1236, 476);
	var wp28 = CreateWP(1252, 110);
	var wp29 = CreateWP(140, 110);
	var wp30 = CreateWP(362, 208);
	var wp31 = CreateWP(439, 239);
	var wp32 = CreateWP(20, 199);
	var wp33 = CreateWP(622, 270);
	var wp34 = CreateWP(619, 126);
	var wp35 = CreateWP(702, 369);
	var wp36 = CreateWP(607, 198);
	var wp37 = CreateWP(495, 241);
	var wp38 = CreateWP(123, 348);
	var wp39 = CreateWP(695, 622);
	var wp40 = CreateWP(152, 228);
	var wp41 = CreateWP(303, 208);
	var wp42 = CreateWP(504, 499);
	var wp43 = CreateWP(402, 490);
	var wp44 = CreateWP(338, 607);
	var wp45 = CreateWP(503, 297);
	var wp46 = CreateWP(398, 368);
	var wp47 = CreateWP(458, 600);
	var wp48 = CreateWP(729, 478);
	var wp49 = CreateWP(652, 498);
	var wp50 = CreateWP(523, 499);
	var wp51 = CreateWP(625, 498);
	var wp52 = CreateWP(264, 476);
	var wp53 = CreateWP(253, 110);
	wp1->AddPath(wp8, Path_MoveTo, 1);
	wp1->AddPath(wp33, Path_MoveTo, -1);
	wp2->AddPath(wp9, Path_MoveTo, 1);
	wp2->AddPath(wp34, Path_MoveTo, -1);
	wp3->AddPath(wp10, Path_MoveTo, 1);
	wp3->AddPath(wp8, Path_MoveTo, 1);
	wp3->AddPath(wp35, Path_MoveTo, -1);
	wp3->AddPath(wp33, Path_MoveTo, -1);
	wp4->AddPath(wp15, Path_MoveTo, 1);
	wp4->AddPath(wp28, Path_Jump, -1);
	wp5->AddPath(wp6, Path_Jump, -1);
	wp5->AddPath(wp16, Path_MoveTo, 1);
	wp6->AddPath(wp12, Path_MoveTo, -1);
	wp6->AddPath(wp5, Path_Backflip, 1);
	wp7->AddPath(wp15, Path_MoveTo, -1);
	wp8->AddPath(wp20, Path_MoveTo, 1);
	wp8->AddPath(wp3, Path_MoveTo, -1);
	wp8->AddPath(wp11, Path_Jump, -1);
	wp8->AddPath(wp1, Path_MoveTo, -1);
	wp9->AddPath(wp11, Path_MoveTo, 1);
	wp9->AddPath(wp19, Path_Jump, 1);
	wp9->AddPath(wp2, Path_MoveTo, -1);
	wp10->AddPath(wp21, Path_MoveTo, 1);
	wp10->AddPath(wp3, Path_MoveTo, -1);
	wp10->AddPath(wp35, Path_MoveTo, -1);
	wp11->AddPath(wp8, Path_MoveTo, -1);
	wp11->AddPath(wp9, Path_Jump, 1);
	wp12->AddPath(wp21, Path_MoveTo, 1);
	wp12->AddPath(wp8, Path_MoveTo, -1);
	wp12->SetArriveCommand(1, 0, {Prototype = Command, command = "Grab", target = switchright});
	wp12->SetArriveCommand(1, 1, {Prototype = Command, command = "Call", target = switchright, data = "ControlThrow"});
	wp12->SetArriveCommand(1, 2, {Prototype = Command, command = "Ungrab"});
	wp12->AddPath(wp6, Path_MoveTo, 1);
	wp13->AddPath(wp21, Path_MoveTo, -1);
	wp13->AddPath(wp15, Path_MoveTo, -1);
	wp14->AddPath(wp22, Path_MoveTo, 1);
	wp14->AddPath(wp1, Path_Jump, -1);
	wp14->AddPath(wp39, Path_MoveTo, -1);
	wp15->AddPath(wp13, Path_MoveTo, 1);
	wp15->AddPath(wp7, Path_MoveTo, 1);
	wp16->AddPath(wp15, Path_Backflip, 1);
	wp16->AddPath(wp5, Path_MoveTo, -1);
	wp17->AddPath(wp18, Path_Backflip, 1);
	wp17->AddPath(wp25, Path_MoveTo, -1);
	wp18->AddPath(wp17, Path_Backflip, -1);
	wp18->AddPath(wp27, Path_MoveTo, 1);
	wp18->AddPath(wp19, Path_MoveTo, 1);
	wp19->AddPath(wp27, Path_Jump, 1);
	wp19->AddPath(wp22, Path_MoveTo, -1);
	wp20->AddPath(wp21, Path_MoveTo, 1);
	wp20->AddPath(wp8, Path_MoveTo, -1);
	wp21->AddPath(wp27, Path_MoveTo, 1);
	wp21->AddPath(wp13, Path_MoveTo, 1);
	wp21->AddPath(wp20, Path_MoveTo, -1);
	wp21->AddPath(wp12, Path_Jump, -1);
	wp21->AddPath(wp10, Path_MoveTo, -1);
	wp21->AddPath(wp6, Path_Jump, -1);
	wp22->AddPath(wp19, Path_MoveTo, 1);
	wp22->AddPath(wp14, Path_MoveTo, -1);
	wp23->AddPath(wp24, Path_Jump, 1);
	wp23->AddPath(wp48, Path_MoveTo, -1);
	wp24->AddPath(wp26, Path_MoveTo, 1);
	wp24->AddPath(wp23, Path_Jump, -1);
	wp25->AddPath(wp26, Path_Backflip, -1);
	wp25->AddPath(wp17, Path_MoveTo, 1);
	wp26->AddPath(wp25, Path_Backflip, 1);
	wp26->AddPath(wp24, Path_MoveTo, -1);
	wp27->AddPath(wp18, Path_MoveTo, -1);
	wp27->AddPath(wp19, Path_MoveTo, -1);
	wp27->AddPath(wp21, Path_Jump, -1);
	wp28->AddPath(wp4, Path_Jump, 1);
	wp28->AddPath(wp16, Path_MoveTo, -1);
	wp29->AddPath(wp40, Path_MoveTo, -1);
	wp29->AddPath(wp53, Path_Jump, 1);
	wp30->AddPath(wp31, Path_Jump, 1);
	wp30->AddPath(wp41, Path_MoveTo, -1);
	wp31->AddPath(wp37, Path_MoveTo, 1);
	wp31->AddPath(wp30, Path_Backflip, -1);
	wp32->AddPath(wp40, Path_MoveTo, 1);
	wp33->AddPath(wp45, Path_MoveTo, -1);
	wp33->AddPath(wp3, Path_MoveTo, 1);
	wp33->AddPath(wp36, Path_Jump, 1);
	wp33->AddPath(wp1, Path_MoveTo, 1);
	wp34->AddPath(wp36, Path_MoveTo, -1);
	wp34->AddPath(wp44, Path_Jump, -1);
	wp34->AddPath(wp2, Path_MoveTo, 1);
	wp35->AddPath(wp46, Path_MoveTo, -1);
	wp35->AddPath(wp3, Path_MoveTo, 1);
	wp35->AddPath(wp10, Path_MoveTo, 1);
	wp36->AddPath(wp33, Path_MoveTo, 1);
	wp36->AddPath(wp34, Path_Jump, -1);
	wp37->AddPath(wp46, Path_MoveTo, -1);
	wp37->AddPath(wp33, Path_MoveTo, 1);
	wp37->SetArriveCommand(1, 0, {Prototype = Command, command = "Grab", target = switchleft});
	wp37->SetArriveCommand(1, 1, {Prototype = Command, command = "Call", target = switchleft, data = "ControlThrow"});
	wp37->SetArriveCommand(1, 2, {Prototype = Command, command = "Ungrab"});
	wp37->AddPath(wp31, Path_MoveTo, -1);
	wp38->AddPath(wp46, Path_MoveTo, 1);
	wp38->AddPath(wp40, Path_MoveTo, 1);
	wp39->AddPath(wp1, Path_Jump, 1);
	wp39->AddPath(wp14, Path_MoveTo, 1);
	wp39->AddPath(wp47, Path_MoveTo, -1);
	wp40->AddPath(wp38, Path_MoveTo, -1);
	wp40->AddPath(wp32, Path_MoveTo, -1);
	wp41->AddPath(wp40, Path_Backflip, -1);
	wp41->AddPath(wp30, Path_MoveTo, 1);
	wp42->AddPath(wp43, Path_Backflip, -1);
	wp42->AddPath(wp50, Path_MoveTo, 1);
	wp43->AddPath(wp42, Path_Backflip, 1);
	wp43->AddPath(wp52, Path_MoveTo, -1);
	wp43->AddPath(wp44, Path_MoveTo, -1);
	wp44->AddPath(wp52, Path_Jump, -1);
	wp44->AddPath(wp47, Path_MoveTo, 1);
	wp45->AddPath(wp46, Path_MoveTo, -1);
	wp45->AddPath(wp33, Path_MoveTo, 1);
	wp46->AddPath(wp52, Path_MoveTo, -1);
	wp46->AddPath(wp38, Path_MoveTo, -1);
	wp46->AddPath(wp45, Path_MoveTo, 1);
	wp46->AddPath(wp37, Path_Jump, 1);
	wp46->AddPath(wp35, Path_MoveTo, 1);
	wp46->AddPath(wp31, Path_Jump, 1);
	wp47->AddPath(wp44, Path_MoveTo, -1);
	wp47->AddPath(wp39, Path_MoveTo, 1);
	wp48->AddPath(wp49, Path_Jump, -1);
	wp48->AddPath(wp23, Path_MoveTo, 1);
	wp49->AddPath(wp51, Path_MoveTo, -1);
	wp49->AddPath(wp48, Path_Jump, 1);
	wp50->AddPath(wp51, Path_Backflip, 1);
	wp50->AddPath(wp42, Path_MoveTo, -1);
	wp51->AddPath(wp50, Path_Backflip, -1);
	wp51->AddPath(wp49, Path_MoveTo, 1);
	wp52->AddPath(wp43, Path_MoveTo, 1);
	wp52->AddPath(wp44, Path_MoveTo, 1);
	wp52->AddPath(wp46, Path_Jump, 1);
	wp53->AddPath(wp29, Path_Jump, -1);
	wp53->AddPath(wp41, Path_MoveTo, 1);
}


func RelaunchLocations()
{
	return [{x =  110, y = 100, team = 1},
	    	{x = 1390, y = 100, team = 2}];
}
