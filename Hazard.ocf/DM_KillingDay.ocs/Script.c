#include Library_DefaultScript

func Initialize()
{
	SetGoal(SCENPAR_HAZARD_GOAL);

	_inherited(...);

	CreateLights();
	CreateLadders();
}

func CreateLights()
{
	CreateObject(FLGH,  782, 732, NO_OWNER)->GetLight()->TurnOn();
	CreateObject(BLGH, 1105, 320, NO_OWNER)->TurnOn();
	CreateObject(BLGH,  955, 535, NO_OWNER)->TurnOn();
	CreateObject(CLGH,  332, 580, NO_OWNER)->TurnOn();
	CreateObject(CLGH,  300, 450, NO_OWNER)->TurnOn();
	CreateObject(CLGH,  389, 450, NO_OWNER)->TurnOn();
	CreateObject(BLGH,   86, 110, NO_OWNER)->TurnOn();
	CreateObject(BLGH,  216, 110, NO_OWNER)->TurnOn();
}

func CreateDeco()
{
	CreateObject(CON1, 601, 56, NO_OWNER);
	CreateObjectAbove(ENGT, 287, 285, NO_OWNER)->SetCon(50);
	CreateObjectAbove(CCP2, 924, 632, NO_OWNER);
	CreateObject(GSTA, 1033, 410, NO_OWNER);
	CreateObject(GSTA,  997, 410, NO_OWNER);
	CreateObject(LCKR, 319, 385, NO_OWNER);
	CreateObject(LCKR, 337, 385, NO_OWNER);
	CreateObject(LCKR, 944, 415, NO_OWNER);
	CreateObject(CHAR, 319, 620, NO_OWNER);
	CreateObject(GSBO, 212, 389, NO_OWNER);
	CreateObject(GSBO, 223, 389, NO_OWNER);
	CreateObject(CRN1, 522, 90, NO_OWNER)->SetCraneLength(5);
	CreateObjectAbove(CCP1, 253, 180, NO_OWNER);
	CreateObject(CRAT, 401, 385, NO_OWNER);
	CreateObject(CRAT, 478, 385, NO_OWNER);
	CreateObject(TABB, 1085, 125, NO_OWNER);
	CreateObject(TABL, 346, 624, NO_OWNER);
	CreateObject(JMPD, 302, 166, NO_OWNER)->Set(75, 35);
	CreateObject(SBBA, 797, 253, NO_OWNER);
	CreateObject(CLVM, 293, 610, NO_OWNER);
	CreateObject(SPVB, 1117, 110, NO_OWNER);
	CreateObject(SLDR, 1075, 155, NO_OWNER);
	CreateObject(SLDR, 175, 205, NO_OWNER);
	CreateObject(SLDR, 215, 205, NO_OWNER);
	CreateObjectAbove(STDR, 232, 300, NO_OWNER);
	CreateObjectAbove(LBDR, 843, 581, NO_OWNER);
	CreateObjectAbove(LBDR, 242, 631, NO_OWNER);
	CreateObjectAbove(LBDR, 414, 630, NO_OWNER);
	CreateObjectAbove(LFTP, 1105, 291, NO_OWNER)->SetAutoLimits();
	CreateObjectAbove(LFTP, 35, 190, NO_OWNER)->SetAutoLimits();
	CreateObject(RAI3, 759, 183, NO_OWNER);
	CreateObject(HSGN, 1005, 255, NO_OWNER)->SetCon(50);
	CreateObject(AWRP, 271, 280, NO_OWNER)->SetDestination(1091, 94);
	CreateObject(AWRP, 755, 560, NO_OWNER)->SetDestination(66, 466);
	CreateObject(FIEX, 422, 299, NO_OWNER);
	CreateObject(VENT, 1002, 326, NO_OWNER)->SetCon(25);
	CreateObject(GAT2, 199, 705, NO_OWNER);
	CreateObjectAbove(LCOM, 385, 615, NO_OWNER);
	CreateObjectAbove(LCOM, 385, 629, NO_OWNER);
	CreateObject(RAI1, 129, 144, NO_OWNER)->SetRailLength(2);
	CreateObject(VENT, 280, 6, NO_OWNER)->SetCon(25);
	CreateObject(RAI1, 169, 174, NO_OWNER)->SetRailLength(3);
	CreateObject(WSHB, 871, 115, NO_OWNER);
	CreateObjectAbove(Console, 490, 60, NO_OWNER)->Set(CreateObject(_GNC, 1, 1, NO_OWNER));
	CreateObject(SEGU, 430, 108, NO_OWNER)->Arm(MGSA);
	CreateObject(SEGU, 630, 108, NO_OWNER)->Arm(MGSA);
}

func CreateLadders()
{
	CreateObject(LADR, 123, 740, NO_OWNER)->LadderHeight(620, 740);
	CreateObject(LADR, 136, 470, NO_OWNER)->LadderHeight(285, 470);
	CreateObject(LADR, 526, 630, NO_OWNER)->LadderHeight(495, 630);
	CreateObject(LADR, 541, 387, NO_OWNER)->LadderHeight(305, 385);
	CreateObject(LADR, 584, 491, NO_OWNER)->LadderHeight(370, 490);
	CreateObject(LADR, 692, 471, NO_OWNER)->LadderHeight(390, 470);
	CreateObject(LADR, 701, 631, NO_OWNER)->LadderHeight(490, 630);
	CreateObject(LADR, 916, 430, NO_OWNER)->LadderHeight(260, 430);
	CreateObject(LADR, 956, 745, NO_OWNER)->LadderHeight(585, 745);
	CreateObject(LADR, 1157, 610, NO_OWNER)->LadderHeight(415, 610);
}

func CreateSpawnPoints()	
{
	// configure spawn points
	var config = GetSpawnPointTemplates();

	// place spawn points
	CopySpawnPoint(config.weapon_energy, 240, 170);
	CopySpawnPoint(config.ammo_energy, 225, 170);
	CopySpawnPoint(config.ammo_standard, 190, 50);
	CopySpawnPoint(config.upgrade_slime, 230, 290);
	CopySpawnPoint(config.ammo_grenade, 210, 290);
	CopySpawnPoint(config.ammo_grenade, 360, 500);
	CopySpawnPoint(config.weapon_grenade, 380, 500);
	CopySpawnPoint(config.ammo_missile, 60, 470);
	CopySpawnPoint(config.weapon_bazooka, 320, 750);
	CopySpawnPoint(config.ammo_missile, 340, 750);
	CopySpawnPoint(config.ammo_standard, 890, 740);
	CopySpawnPoint(config.weapon_pumpgun, 1030, 420);
	CopySpawnPoint(config.ammo_standard, 1050, 420);
	CopySpawnPoint(config.upgrade_laser, 810, 570);
	CopySpawnPoint(config.weapon_motegun, 540, 60);
	CopySpawnPoint(config.ammo_energy, 560, 60);
	CopySpawnPoint(config.weapon_flame, 1070, 120);
	CopySpawnPoint(config.ammo_gasoline, 1090, 120);
	CopySpawnPoint(config.ammo_gasoline, 1180, 90);
	CopySpawnPoint(config.item_jetpack, 1060, 280);
	CopySpawnPoint(config.item_medipack, 640, 250);
	CopySpawnPoint(config.weapon_mine, 430, 260);
	CopySpawnPoint(config.upgrade_rifle, 300, 390);
	CopySpawnPoint(config.item_shield, 710, 370);
	CopySpawnPoint(config.weapon_chainsaw, 670, 639);
	CopySpawnPoint(config.ammo_gasoline, 655, 639);	
	
	// remove template spawn points
	RemoveSpawnPointTemplates(config);
}

func CreateWaypoints()
{
	var wp1 = CreateWP(1055, 746);
	var wp2 = CreateWP(914, 492);
	var wp3 = CreateWP(1118, 116);
	var wp4 = CreateWP(1071, 277);
	var wp5 = CreateWP(1074, 418);
	var wp6 = CreateWP(945, 419);
	var wp7 = CreateWP(882, 490);
	var wp8 = CreateWP(802, 239);
	var wp9 = CreateWP(876, 190);
	var wp10 = CreateWP(1176, 158);
	var wp11 = CreateWP(1055, 160);
	var wp12 = CreateWP(1140, 597);
	var wp13 = CreateWP(761, 564);
	var wp14 = CreateWP(1009, 674);
	var wp15 = CreateWP(919, 618);
	var wp16 = CreateWP(542, 730);
	var wp17 = CreateWP(420, 751);
	var wp18 = CreateWP(936, 693);
	var wp19 = CreateWP(95, 617);
	var wp20 = CreateWP(183, 616);
	var wp21 = CreateWP(938, 749);
	var wp22 = CreateWP(866, 736);
	var wp23 = CreateWP(481, 707);
	var wp24 = CreateWP(152, 751);
	var wp25 = CreateWP(166, 553);
	var wp26 = CreateWP(124, 483);
	var wp27 = CreateWP(66, 466);
	var wp28 = CreateWP(230, 479);
	var wp29 = CreateWP(504, 500);
	var wp30 = CreateWP(551, 501);
	var wp31 = CreateWP(511, 620);
	var wp32 = CreateWP(521, 394);
	var wp33 = CreateWP(70, 286);
	var wp34 = CreateWP(263, 284);
	var wp35 = CreateWP(160, 288);
	var wp36 = CreateWP(161, 390);
	var wp37 = CreateWP(854, 280);
	var wp38 = CreateWP(724, 369);
	var wp39 = CreateWP(561, 391);
	var wp40 = CreateWP(333, 229);
	var wp41 = CreateWP(141, 207);
	var wp42 = CreateWP(70, 207);
	var wp43 = CreateWP(639, 250);
	var wp44 = CreateWP(338, 80);
	var wp45 = CreateWP(71, 60);
	var wp46 = CreateWP(268, 169);
	var wp47 = CreateWP(431, 257);
	var wp48 = CreateWP(557, 58);
	var wp49 = CreateWP(526, 307);
	var wp50 = CreateWP(399, 303);
	var wp51 = CreateWP(603, 499);
	var wp52 = CreateWP(666, 470);
	var wp53 = CreateWP(673, 641);
	var wp54 = CreateWP(724, 502);
	var wp55 = CreateWP(583, 709);
	wp1->AddPath(wp21, Path_MoveTo, -1);
	wp2->AddPath(wp15, Path_MoveTo, -1);
	wp3->AddPath(wp10, Path_MoveTo, 1);
	wp3->AddPath(wp9, Path_MoveTo, -1);
	wp4->AddPath(wp11, Path_MoveTo, -1);
	wp4->AddPath(wp10, Path_MoveTo, 1);
	wp4->AddPath(wp5, Path_MoveTo, 1);
	wp4->AddPath(wp37, Path_MoveTo, -1);
	wp5->AddPath(wp6, Path_MoveTo, -1);
	wp5->AddPath(wp4, Path_MoveTo, -1);
	wp5->AddPath(wp12, Path_MoveTo, 1);
	wp6->AddPath(wp5, Path_MoveTo, 1);
	wp6->AddPath(wp7, Path_MoveTo, -1);
	wp6->AddPath(wp37, Path_Jump, -1);
	wp6->AddPath(wp4, Path_Jump, -1);
	wp6->AddPath(wp52, Path_MoveTo, -1);
	wp6->AddPath(wp54, Path_MoveTo, -1);
	wp7->AddPath(wp2, Path_MoveTo, 1);
	wp8->AddPath(wp37, Path_MoveTo, -1);
	wp8->AddPath(wp43, Path_MoveTo, 1);
	wp8->AddPath(wp9, Path_Jump, 1);
	wp9->AddPath(wp11, Path_MoveTo, 1);
	wp9->AddPath(wp8, Path_MoveTo, -1);
	wp10->AddPath(wp4, Path_MoveTo, -1);
	wp10->AddPath(wp3, Path_Jump, -1);
	wp10->AddPath(wp11, Path_MoveTo, -1);
	wp11->AddPath(wp9, Path_MoveTo, -1);
	wp11->AddPath(wp4, Path_MoveTo, 1);
	wp11->AddPath(wp10, Path_MoveTo, 1);
	wp12->AddPath(wp14, Path_MoveTo, -1);
	wp12->AddPath(wp5, Path_Jump, 1);
	wp13->AddPath(wp27, Path_MoveTo, -1);
	wp14->AddPath(wp12, Path_Jump, 1);
	wp14->AddPath(wp21, Path_MoveTo, -1);
	wp14->AddPath(wp18, Path_MoveTo, -1);
	wp14->AddPath(wp1, Path_MoveTo, 1);
	wp15->AddPath(wp13, Path_Jump, -1);
	wp15->AddPath(wp13, Path_MoveTo, -1);
	wp16->AddPath(wp23, Path_Jump, -1);
	wp16->AddPath(wp17, Path_MoveTo, -1);
	wp16->AddPath(wp55, Path_MoveTo, 1);
	wp17->AddPath(wp24, Path_MoveTo, -1);
	wp17->AddPath(wp23, Path_Jump, 1);
	wp17->AddPath(wp16, Path_MoveTo, 1);
	wp18->AddPath(wp15, Path_Jump, 1);
	wp18->AddPath(wp14, Path_MoveTo, 1);
	wp19->AddPath(wp24, Path_MoveTo, 1);
	wp19->AddPath(wp25, Path_Jump, 1);
	wp19->AddPath(wp20, Path_MoveTo, 1);
	wp20->AddPath(wp24, Path_MoveTo, -1);
	wp20->AddPath(wp31, Path_MoveTo, 1);
	wp20->AddPath(wp28, Path_Jump, 1);
	wp20->AddPath(wp19, Path_MoveTo, -1);
	wp21->AddPath(wp15, Path_Jump, 1);
	wp21->AddPath(wp22, Path_MoveTo, -1);
	wp21->AddPath(wp14, Path_Jump, 1);
	wp22->AddPath(wp18, Path_Jump, 1);
	wp22->AddPath(wp55, Path_MoveTo, -1);
	wp22->AddPath(wp21, Path_MoveTo, 1);
	wp23->AddPath(wp17, Path_MoveTo, -1);
	wp23->AddPath(wp16, Path_MoveTo, 1);
	wp24->AddPath(wp17, Path_MoveTo, 1);
	wp24->AddPath(wp20, Path_Jump, -1);
	wp24->AddPath(wp19, Path_Jump, -1);
	wp25->AddPath(wp19, Path_MoveTo, 1);
	wp25->AddPath(wp20, Path_MoveTo, 1);
	wp26->AddPath(wp27, Path_MoveTo, -1);
	wp26->AddPath(wp28, Path_Backflip, 1);
	wp26->AddPath(wp25, Path_MoveTo, 1);
	wp26->AddPath(wp36, Path_Jump, 1);
	wp26->AddPath(wp35, Path_Jump, 1);
	wp26->AddPath(wp33, Path_Jump, 1);
	wp27->AddPath(wp26, Path_MoveTo, 1);
	wp28->AddPath(wp29, Path_MoveTo, 1);
	wp28->AddPath(wp26, Path_Backflip, -1);
	wp28->AddPath(wp25, Path_MoveTo, 1);
	wp29->AddPath(wp31, Path_MoveTo, 1);
	wp29->AddPath(wp28, Path_MoveTo, -1);
	wp29->AddPath(wp30, Path_MoveTo, 1);
	wp30->AddPath(wp31, Path_MoveTo, -1);
	wp30->AddPath(wp29, Path_MoveTo, -1);
	wp30->AddPath(wp39, Path_Jump, 1);
	wp30->AddPath(wp51, Path_MoveTo, 1);
	wp31->AddPath(wp20, Path_MoveTo, -1);
	wp31->AddPath(wp30, Path_Jump, 1);
	wp31->AddPath(wp29, Path_Jump, 1);
	wp31->AddPath(wp55, Path_MoveTo, 1);
	wp32->AddPath(wp36, Path_MoveTo, -1);
	wp32->AddPath(wp49, Path_Jump, 1);
	wp32->AddPath(wp39, Path_MoveTo, 1);
	wp33->AddPath(wp36, Path_MoveTo, 1);
	wp33->AddPath(wp26, Path_MoveTo, 1);
	wp33->AddPath(wp42, Path_MoveTo, 1);
	wp33->AddPath(wp45, Path_MoveTo, 1);
	wp33->AddPath(wp42, Path_MoveTo, 0);
	wp33->AddPath(wp35, Path_MoveTo, 1);
	wp34->AddPath(wp3, Path_MoveTo, 1);
	wp35->AddPath(wp26, Path_MoveTo, -1);
	wp35->AddPath(wp36, Path_MoveTo, 1);
	wp35->AddPath(wp34, Path_MoveTo, 1);
	wp35->AddPath(wp33, Path_MoveTo, -1);
	wp36->AddPath(wp33, Path_Jump, -1);
	wp36->AddPath(wp35, Path_Jump, -1);
	wp36->AddPath(wp32, Path_MoveTo, 1);
	wp37->AddPath(wp38, Path_MoveTo, -1);
	wp37->AddPath(wp8, Path_Jump, -1);
	wp37->AddPath(wp4, Path_MoveTo, 1);
	wp37->AddPath(wp6, Path_MoveTo, 1);
	wp38->AddPath(wp37, Path_Jump, 1);
	wp38->AddPath(wp52, Path_MoveTo, -1);
	wp38->AddPath(wp51, Path_MoveTo, -1);
	wp39->AddPath(wp49, Path_Jump, -1);
	wp39->AddPath(wp32, Path_MoveTo, -1);
	wp39->AddPath(wp30, Path_MoveTo, -1);
	wp40->AddPath(wp47, Path_Jump, 1);
	wp40->AddPath(wp41, Path_MoveTo, -1);
	wp40->AddPath(wp50, Path_MoveTo, 1);
	wp41->AddPath(wp42, Path_MoveTo, -1);
	wp41->AddPath(wp40, Path_MoveTo, 1);
	wp41->AddPath(wp46, Path_Jump, 1);
	wp42->AddPath(wp33, Path_MoveTo, -1);
	wp42->AddPath(wp41, Path_MoveTo, 1);
	wp42->AddPath(wp45, Path_MoveTo, 1);
	wp42->AddPath(wp33, Path_MoveTo, 0);
	wp43->AddPath(wp8, Path_MoveTo, 1);
	wp43->AddPath(wp49, Path_MoveTo, -1);
	wp44->AddPath(wp45, Path_MoveTo, -1);
	wp44->AddPath(wp48, Path_Jump, 1);
	wp44->AddPath(wp48, Path_Backflip, 1);
	wp45->AddPath(wp33, Path_MoveTo, -1);
	wp45->AddPath(wp44, Path_MoveTo, 1);
	wp45->AddPath(wp42, Path_MoveTo, -1);
	wp46->AddPath(wp48, Path_MoveTo, 1);
	wp46->AddPath(wp41, Path_MoveTo, -1);
	wp47->AddPath(wp40, Path_Jump, -1);
	wp47->AddPath(wp50, Path_MoveTo, -1);
	wp48->AddPath(wp40, Path_MoveTo, -1);
	wp48->AddPath(wp43, Path_MoveTo, 1);
	wp49->AddPath(wp50, Path_Jump, -1);
	wp49->AddPath(wp50, Path_Backflip, -1);
	wp49->AddPath(wp32, Path_MoveTo, -1);
	wp49->AddPath(wp39, Path_MoveTo, 1);
	wp49->AddPath(wp43, Path_MoveTo, 1);
	wp50->AddPath(wp47, Path_Jump, 1);
	wp50->AddPath(wp32, Path_MoveTo, 1);
	wp50->AddPath(wp40, Path_MoveTo, -1);
	wp51->AddPath(wp52, Path_Jump, 1);
	wp51->AddPath(wp30, Path_MoveTo, -1);
	wp51->AddPath(wp39, Path_Jump, -1);
	wp51->AddPath(wp53, Path_MoveTo, 1);
	wp52->AddPath(wp6, Path_MoveTo, 1);
	wp52->AddPath(wp38, Path_Jump, 1);
	wp52->AddPath(wp38, Path_Jump, 1);
	wp52->AddPath(wp51, Path_MoveTo, -1);
	wp52->AddPath(wp39, Path_Jump, -1);
	wp52->AddPath(wp54, Path_MoveTo, 1);
	wp53->AddPath(wp13, Path_Jump, 1);
	wp53->AddPath(wp54, Path_Jump, 1);
	wp53->AddPath(wp55, Path_MoveTo, -1);
	wp54->AddPath(wp53, Path_MoveTo, -1);
	wp54->AddPath(wp52, Path_MoveTo, -1);
	wp54->AddPath(wp6, Path_MoveTo, 1);
	wp55->AddPath(wp22, Path_MoveTo, 1);
	wp55->AddPath(wp16, Path_MoveTo, -1);
	wp55->AddPath(wp53, Path_Jump, 1);
	wp55->AddPath(wp31, Path_Jump, -1);
}

// TODO
//public func ChooserFinished()
//{
//  Arena_ChooserFinished();
//
//  var wp = FindObject(WPCH);
//  if(wp)
//  {
//    // und begrenzte Waren...
//    wp->RemoveWare();
//    wp->AddWare(PIWP);  // Pistole
//    wp->AddWare(PGWP);  // Pumpgun
//    wp->AddWare(FTWP);  // Flammenwerfer
//    wp->AddWare(MIWP);  // Minigun
//    wp->AddWare(MEZL);  // Mezl
//    wp->AddWare(KLAS);  // Laser
//    wp->AddWare(KRFL);  // Waffenteile
//
//    wp->AddWare(FLSH);  // Taschenlampe
//    wp->AddWare(HARM);  // R�stung
//    wp->AddWare(MINE);  // Mine
//    //wp->SortWare();
//  }
//}

func RelaunchLocations()
{
	return
	[
		{ x =  270, y =  150, team = NO_OWNER},
		{ x =  170, y =  280, team = NO_OWNER},
		{ x =   60, y =  460, team = NO_OWNER},
		{ x =  380, y =  620, team = NO_OWNER},
		{ x =   50, y =  730, team = NO_OWNER},
		{ x =  600, y =  680, team = NO_OWNER},
		{ x =  970, y =  400, team = NO_OWNER},
		{ x = 1120, y =  100, team = NO_OWNER}
	];
}
