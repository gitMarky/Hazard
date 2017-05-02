#include Library_DefaultScript

func Initialize()
{
	SetGoal(SCENPAR_HAZARD_GOAL);

	_inherited(...);
}

func CreateBackground()
{
	SetSkyParallax(0, 150, 20);
}

func CreateDeco()
{
	// filler
	CreateObjectAbove(_REF, 1110, 1, NO_OWNER);
	CreateObjectAbove(_REF, 1445, 65, NO_OWNER);
	CreateObjectAbove(_REF, 1565, 135, NO_OWNER);
	CreateObjectAbove(_REF, 1390, 12, NO_OWNER);
	CreateObjectAbove(_REF, 590, 581, NO_OWNER);
	
	// deco
	/* TODO
	CreateObjectAbove(SHEL, 378, 700, NO_OWNER);
	CreateObjectAbove(SHEL, 1850, 521, NO_OWNER);
	CreateObjectAbove(SHEL, 1770, 430, NO_OWNER);
	CreateObjectAbove(IDOL, 671, 474, NO_OWNER)->SetR(-45);
	CreateObjectAbove(SUBB, 439, 1171, NO_OWNER)->SetR(45);
	*/
	CreateObjectAbove(PLNT, 135, 309, NO_OWNER);
	CreateObjectAbove(CCP2, 436, 922, NO_OWNER);
	CreateObjectAbove(CCP1, 401, 920, NO_OWNER);
	CreateObjectAbove(LTBL, 246, 489, NO_OWNER);
	CreateObjectAbove(BED2, 97, 179, NO_OWNER)->SetCon(50);
	CreateObjectAbove(BED2, 56, 179, NO_OWNER);
	CreateObjectAbove(BED2, 37, 99, NO_OWNER);
	CreateObjectAbove(CON1, 29, 490, NO_OWNER);
	CreateObjectAbove(CGLO, 2223, 479, NO_OWNER);
	CreateObjectAbove(OTBL, 515, 179, NO_OWNER);
	CreateObjectAbove(OTBL, 1874, 929, NO_OWNER);
	CreateObjectAbove(TELE, 2338, 701, NO_OWNER)->Deactivate();
	var pCrane = CreateObjectAbove(CRN1, 1850, 599, NO_OWNER);
	pCrane->SetCraneLength(15);
	CreateObjectAbove(Console, 1957, 642, NO_OWNER)->Set(pCrane);
	CreateObjectAbove(GADG, 2151, 1237, NO_OWNER);
	CreateObjectAbove(MONI, 2132, 1225, NO_OWNER);
	CreateObjectAbove(MPPJ, 30, 970, NO_OWNER);
	CreateObjectAbove(OCHR, 510, 179, NO_OWNER);
	CreateObjectAbove(OCHR, 2142, 1239, NO_OWNER);
	CreateObjectAbove(PLT2, 74, 181, NO_OWNER);
	CreateObjectAbove(PLT2, 2187, 1241, NO_OWNER);
	CreateObjectAbove(GTBL, 82, 310, NO_OWNER);
	CreateObjectAbove(GTBL, 2140, 1240, NO_OWNER);
	CreateObjectAbove(GSBO, 198, 490, NO_OWNER);
	CreateObjectAbove(GSBO, 190, 490, NO_OWNER);
	CreateObjectAbove(GSBO, 2333, 850, NO_OWNER);
	CreateObjectAbove(GSBO, 2327, 850, NO_OWNER);
	CreateObjectAbove(GSTA, 2300, 849, NO_OWNER);
	CreateObjectAbove(FLGH, 64, 841, NO_OWNER)->SetRotation(20, 135);
	CreateObjectAbove(FLGH, 273, 991, NO_OWNER)->SetRotation(0, 180);
	CreateObjectAbove(FLGH, 231, 180, NO_OWNER)->SetRotation(48);
	CreateObjectAbove(FLGH, 2394, 692, NO_OWNER)->SetRotation(-80);
	CreateObjectAbove(FLGH, 2482, 1014, NO_OWNER)->SetRotation(-45, -90);
	CreateObjectAbove(CHAR, 54, 309, NO_OWNER);
	CreateObjectAbove(CHAR, 179, 99, NO_OWNER);
	CreateObjectAbove(CHAR, 2191, 1129, NO_OWNER);
	CreateObjectAbove(LCKR, 117, 310, NO_OWNER);
	CreateObjectAbove(LCKR, 133, 750, NO_OWNER);
	CreateObjectAbove(LCKR, 118, 750, NO_OWNER);
	CreateObjectAbove(LCKR, 95, 100, NO_OWNER);
	CreateObjectAbove(LCKR, 112, 100, NO_OWNER);
	CreateObjectAbove(LCKR, 2396, 1240, NO_OWNER);
	CreateObjectAbove(LCKR, 2164, 420, NO_OWNER);
	CreateObjectAbove(LCKR, 2290, 420, NO_OWNER);
	CreateObjectAbove(LCKR, 2275, 420, NO_OWNER);
	CreateObjectAbove(LCKR, 1910, 930, NO_OWNER);
	CreateObjectAbove(LCKR, 1890, 937, NO_OWNER)->SetR(92);
	CreateObjectAbove(LCKR, 1844, 931, NO_OWNER)->SetR(-9);
	CreateObjectAbove(LCKR, 2254, 1130, NO_OWNER);
	CreateObjectAbove(LCKR, 2240, 1130, NO_OWNER);
	CreateObjectAbove(TABL, 203, 100, NO_OWNER);
	CreateObjectAbove(TABL, 151, 749, NO_OWNER);
	CreateObjectAbove(TABL, 2214, 1129, NO_OWNER);
	CreateObjectAbove(TABL, 2367, 1239, NO_OWNER);
	CreateObjectAbove(CRAT, 91, 490, NO_OWNER);
	CreateObjectAbove(CRAT, 1735, 700, NO_OWNER);
	CreateObjectAbove(CRAT, 1706, 700, NO_OWNER);
	CreateObjectAbove(CRAT, 1864, 750, NO_OWNER);
	CreateObjectAbove(CRAT, 1887, 723, NO_OWNER);
	CreateObjectAbove(CRAT, 1895, 750, NO_OWNER);
	CreateObjectAbove(CRAT, 1935, 703, NO_OWNER);
	CreateObjectAbove(CRAT, 1984, 701, NO_OWNER);
	CreateObjectAbove(CRAT, 1076, 710, NO_OWNER);
	CreateObjectAbove(CRAT, 752, 601, NO_OWNER);
	CreateObjectAbove(CRAT, 745, 630, NO_OWNER);
	CreateObjectAbove(CRAT, 774, 630, NO_OWNER);
	CreateObjectAbove(DEB1, 429, 486, NO_OWNER)->SetR(-50);
	CreateObjectAbove(DEB1, 458, 491, NO_OWNER)->SetR(20);
	CreateObjectAbove(DEB1, 407, 491, NO_OWNER);
	CreateObjectAbove(DEB1, 1945, 724, NO_OWNER)->SetR(173);
	CreateObjectAbove(DEB1, 1938, 709, NO_OWNER);
	CreateObjectAbove(DEB1, 1975, 706, NO_OWNER)->SetR(-13);
	CreateObjectAbove(DEB1, 1948, 712, NO_OWNER)->SetR(-13);
	
	CreateObjectAbove(CRN1, 2181, 730, NO_OWNER)->SetCraneLength(18);
	CreateObjectAbove(LBDR, 305, 490, NO_OWNER);
	CreateObjectAbove(LBDR, 574, 110, NO_OWNER);
	CreateObjectAbove(SBBA, 314, 138, NO_OWNER);
	CreateObjectAbove(SPVM, 114, 380, NO_OWNER);
	CreateObjectAbove(SPVM, 1609, 610, NO_OWNER);
	CreateObjectAbove(TOIC, 2479, 1240, NO_OWNER);
	CreateObjectAbove(CLVM, 145, 380, NO_OWNER);
	CreateObjectAbove(CLVM, 2211, 1240, NO_OWNER);
	CreateObjectAbove(STDR, 135, 490, NO_OWNER);
	CreateObjectAbove(STDR, 2197, 1060, NO_OWNER);
	CreateObjectAbove(STDR, 2432, 1240, NO_OWNER);
	CreateObjectAbove(STDR, 2068, 1239, NO_OWNER);
	CreateObjectAbove(STDR, 2252, 1240, NO_OWNER);
	CreateObjectAbove(SLDR, 456, 380, NO_OWNER);
	CreateObjectAbove(SLDR, 2132, 700, NO_OWNER);
	CreateObjectAbove(SLDR, 2135, 480, NO_OWNER);
	CreateObjectAbove(LFTP, 285, 933, NO_OWNER);
	CreateObjectAbove(LFTP, 235, 393, NO_OWNER);
	CreateObjectAbove(LFTP, 425, 354, NO_OWNER);
	CreateObjectAbove(LFTP, 2090, 394, NO_OWNER);
	CreateObjectAbove(LFTP, 2145, 1153, NO_OWNER);
	CreateObjectAbove(LFTP, 1955, 1253, NO_OWNER);
	CreateObjectAbove(AIRL, 950, 420, NO_OWNER)->SetLeft();
	CreateObjectAbove(AIRL, 521, 663, NO_OWNER)->SetRight();
	CreateObjectAbove(AIRL, 791, 232, NO_OWNER)->SetRight();
	CreateObjectAbove(AIRL, 810, 773, NO_OWNER)->SetLeft();
	CreateObjectAbove(AIRL, 1200, 851, NO_OWNER)->SetRight();
	CreateObjectAbove(AIRL, 1330, 782, NO_OWNER)->SetRight();
	CreateObjectAbove(AIRL, 1591, 753, NO_OWNER)->SetLeft();
	CreateObjectAbove(SCR4, 185, 368, NO_OWNER);
	CreateObjectAbove(ALGH, 505, 358, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 695, 178, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 286, 28, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 319, 258, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 566, 868, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 330, 1238, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 392, 638, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 112, 828, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 1638, 718, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 2089, 358, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 1847, 1109, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 1739, 928, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 2144, 948, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 2424, 998, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 1790, 548, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 2266, 558, NO_OWNER)->SetR(180);
	var pRail = CreateObjectAbove(RAI1, 377, 850, NO_OWNER);
	pRail->SetRail([1, 3, 1, 3, 1, 3, 1, 3]);
	pRail->AdjustPart(9, 2);
	CreateObjectAbove(SCR3, 511, 162, NO_OWNER)->SetClrModulation(RGB(0, 200, 0));
	CreateObjectAbove(BLGH, 78, 279, NO_OWNER);
	CreateObjectAbove(LLGH, 215, 484, NO_OWNER);
	CreateObjectAbove(BLGH, 423, 230, NO_OWNER);
	CreateObjectAbove(CLGH, 71, 21, NO_OWNER);
	CreateObjectAbove(CLGH, 158, 641, NO_OWNER);
	CreateObjectAbove(BLGH, 370, 892, NO_OWNER);
	CreateObjectAbove(LCOM, 512, 111, NO_OWNER);
	CreateObjectAbove(LCOM, 527, 111, NO_OWNER);
	CreateObjectAbove(FRAM, 487, 100, NO_OWNER);
	CreateObjectAbove(FRAM, 552, 101, NO_OWNER);
	CreateObjectAbove(MVNT, 132, 709, NO_OWNER);
	CreateObjectAbove(SCR2, 1274, 715, NO_OWNER)->RemoveFrame();
	CreateObjectAbove(PSTR, 72, 91, NO_OWNER);
	CreateObjectAbove(FENC, 439, 976, NO_OWNER);
	CreateObjectAbove(FENC, 379, 976, NO_OWNER);
	CreateObjectAbove(STRP, 236, 457, NO_OWNER)->SetWidth(100)->SetColor(RGB(0, 200, 0));
	CreateObjectAbove(FENC, 319, 976, NO_OWNER);
	CreateObjectAbove(FENC, 259, 976, NO_OWNER);
	CreateObjectAbove(ESGN, 299, 437, NO_OWNER);
	CreateObjectAbove(FIEX, 298, 480, NO_OWNER);
	CreateObjectAbove(FENC, 286, 140, NO_OWNER);
	var pScreen = CreateObjectAbove(SCR3, 180, 850, NO_OWNER);
	pScreen->SetClrModulation(65535);
	pScreen->RemoveFrame();
	pScreen = CreateObjectAbove(SCR3, 180, 961, NO_OWNER);
	pScreen->SetClrModulation(65535);
	pScreen->RemoveFrame();
	CreateObjectAbove(RAI2, 36, 311, NO_OWNER)->SetRail([1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1]);
	CreateObjectAbove(MVNT, 161, 432, NO_OWNER)->SetCon(50);
	CreateObjectAbove(ENGT, 520, 45, NO_OWNER)->SetCon(75);
	CreateObjectAbove(RAI1, 375, 180, NO_OWNER)->SetRail([1, 3, 2, 2, 2, 3, 1]);
	CreateObjectAbove(HSGN, 274, 1136, NO_OWNER);
	CreateObjectAbove(FENC, 362, 493, NO_OWNER);
	CreateObjectAbove(CLGH, 2076, 1001, NO_OWNER);
	CreateObjectAbove(CLGH, 2225, 371, NO_OWNER);
	CreateObjectAbove(FRAM, 1866, 916, NO_OWNER);
	CreateObjectAbove(CLGH, 1872, 881, NO_OWNER);
	var pPipe = CreateObjectAbove(PMP2, 2224, 693, NO_OWNER)->Up(2);
	pPipe->Right(0, 0, 1)->Down(2);
	CreateObjectAbove(FENC, 2173, 659, NO_OWNER);
	CreateObjectAbove(FENC, 2233, 660, NO_OWNER);
	CreateObjectAbove(FENC, 2350, 663, NO_OWNER);
	CreateObjectAbove(FENC, 2350, 704, NO_OWNER);
	CreateObjectAbove(FENC, 2233, 701, NO_OWNER);
	CreateObjectAbove(FENC, 2173, 700, NO_OWNER);
	CreateObjectAbove(FIEX, 1986, 642, NO_OWNER);
	CreateObjectAbove(BLGH, 1812, 682, NO_OWNER);
	CreateObjectAbove(FRAM, 2113, 1219, NO_OWNER);
	pScreen = CreateObjectAbove(SCR3, 180, 882, NO_OWNER);
	pScreen->SetClrModulation(65535);
	pScreen->RemoveFrame();
	pScreen = CreateObjectAbove(SCR1, 180, 930, NO_OWNER);
	pScreen->SetClrModulation(65535);
	pScreen->RemoveFrame();
	CreateObjectAbove(LBGH, 2109, 723, NO_OWNER);
	CreateObjectAbove(RAI1, 2037, 812, NO_OWNER);
	CreateObjectAbove(RAI1, 2014, 812, NO_OWNER);
	CreateObjectAbove(RAI1, 1990, 812, NO_OWNER);
	CreateObjectAbove(RAI2, 2043, 892, NO_OWNER)->SetRailLength(5);
	CreateObjectAbove(HSGN, 2105, 853, NO_OWNER)->SetClrModulation(9856050);
	CreateObjectAbove(FENC, 2338, 851, NO_OWNER);
	CreateObjectAbove(FENC, 2290, 851, NO_OWNER);
	pPipe = CreateObjectAbove(PIPL, 2373, 895, NO_OWNER)->Left(2)->Up();
	pPipe->Up(2);
	pPipe->Left()->Up()->Right(2)->Up();
	CreateObjectAbove(WSHB, 2450, 1241, NO_OWNER);
	CreateObjectAbove(VENT, 2427, 1101, NO_OWNER)->SetCon(45);
	CreateObjectAbove(STRP, 2188, 1213, NO_OWNER)->SetWidth(80);
	CreateObjectAbove(STRP, 2161, 1229, NO_OWNER)->SetWidth(140);
	CreateObjectAbove(CLGH, 2144, 1161, NO_OWNER);
	CreateObjectAbove(GAT2, 876, 766, NO_OWNER);
	CreateObjectAbove(GAT2, 1127, 845, NO_OWNER);
	CreateObjectAbove(CLGH, 855, 501, NO_OWNER);
	CreateObjectAbove(BLGH, 1200, 735, NO_OWNER);
	CreateObjectAbove(CLGH, 1100, 551, NO_OWNER);
	CreateObjectAbove(ESGN, 1985, 627, NO_OWNER);
	CreateObjectAbove(FIEX, 2179, 1124, NO_OWNER);
	CreateObjectAbove(VENT, 1136, 670, NO_OWNER)->SetCon(30);
	CreateObjectAbove(FENC, 823, 631, NO_OWNER);
	CreateObjectAbove(FENC, 760, 631, NO_OWNER);
	CreateObjectAbove(VENT, 2186, 854, NO_OWNER)->SetCon(30);
/* TODO
	CreateObjectAbove(HNG2, 2495, 821, NO_OWNER);
	CreateObjectAbove(STLC, 0, 0, NO_OWNER);
	CreateObjectAbove(DPIP, 0, 0, NO_OWNER);
	CreateObjectAbove(STLC, 0, 0, NO_OWNER);
	CreateObjectAbove(SWD1, 1370, 1080, NO_OWNER);
	CreateObjectAbove(SWD1, 660, 1180, NO_OWNER);
	CreateObjectAbove(SWD1, 1360, 470, NO_OWNER);
	CreateObjectAbove(SWD2, 1610, 530, NO_OWNER);
	CreateObjectAbove(SWD1, 740, 470, NO_OWNER);
	CreateObjectAbove(SWD2, 10, 720, NO_OWNER);
*/
}

func CreateLadders()
{
/* TODO
	CreateObjectAbove(LADR, 315, 1181, NO_OWNER)->Set(23);
	CreateObjectAbove(LADR, 476, 1025, NO_OWNER)->Set(14);
	CreateObjectAbove(LADR, 375, 958, NO_OWNER)->Set(14);
	CreateObjectAbove(LADR, 214, 942, NO_OWNER)->Set(19);
	CreateObjectAbove(LADR, 86, 795, NO_OWNER)->Set(6);
	CreateObjectAbove(LADR, 186, 737, NO_OWNER)->Set(6);
	CreateObjectAbove(LADR, 338, 461, NO_OWNER)->Set(10);
	CreateObjectAbove(LADR, 127, 142, NO_OWNER)->Set(5);
	CreateObjectAbove(LADR, 596, 201, NO_OWNER)->Set(12);
	CreateObjectAbove(LADR, 546, 215, NO_OWNER)->Set(5);
	CreateObjectAbove(LADR, 17, 380, NO_OWNER)->Set(26);
	CreateObjectAbove(LADR, 76, 427, NO_OWNER)->Set(6);
	CreateObjectAbove(LADR, 2298, 1207, NO_OWNER)->Set(10);
	CreateObjectAbove(LADR, 2029, 1201, NO_OWNER)->Set(24);
	CreateObjectAbove(LADR, 1835, 974, NO_OWNER)->Set(5);
	CreateObjectAbove(LADR, 1794, 969, NO_OWNER)->Set(14);
	CreateObjectAbove(LADR, 1877, 851, NO_OWNER)->Set(5);
	CreateObjectAbove(LADR, 2255, 456, NO_OWNER)->Set(4);
	CreateObjectAbove(LADR, 2197, 455, NO_OWNER)->Set(4);
	CreateObjectAbove(LADR, 2296, 524, NO_OWNER)->Set(5);
	CreateObjectAbove(LADR, 2165, 667, NO_OWNER)->Set(18);
	CreateObjectAbove(LADR, 1667, 730, NO_OWNER)->Set(15);
	CreateObjectAbove(LADR, 2067, 881, NO_OWNER)->Set(10);
	CreateObjectAbove(LADR, 2258, 934, NO_OWNER)->Set(10);
	CreateObjectAbove(LADR, 2365, 1105, NO_OWNER)->Set(24);
	CreateObjectAbove(LADR, 820, 548, NO_OWNER)->Set(5);
	CreateObjectAbove(LADR, 876, 580, NO_OWNER)->Set(9);
	CreateObjectAbove(LADR, 1035, 651, NO_OWNER)->Set(8);
	CreateObjectAbove(LADR, 937, 746, NO_OWNER)->Set(30);
	CreateObjectAbove(LADR, 1108, 821, NO_OWNER)->Set(14);
	CreateObjectAbove(LADR, 1167, 749, NO_OWNER)->Set(20);
	CreateObjectAbove(LADR, 1229, 762, NO_OWNER)->Set(9);
*/
}

func CreateSpawnPoints()
{
	// configure spawn points
	var config = GetSpawnPointTemplates();

	// place spawn points
	CopySpawnPoint(config.weapon_energy, 100, 170);
	CopySpawnPoint(config.ammo_energy, 80, 170);
	CopySpawnPoint(config.weapon_pumpgun, 280, 380);
	CopySpawnPoint(config.ammo_standard, 300, 380);
	CopySpawnPoint(config.upgrade_rifle, 770, 190);
	//TODO CopySpawnPoint(config.AIRT, 1070, 660);
	CopySpawnPoint(config.weapon_grenade, 1200, 680);
	CopySpawnPoint(config.ammo_grenade, 1180, 680);
	CopySpawnPoint(config.item_armor, 1170, 1200);
	CopySpawnPoint(config.weapon_energy, 200, 740);
	CopySpawnPoint(config.ammo_energy, 220, 740);
	CopySpawnPoint(config.weapon_pumpgun, 590, 1010);
	CopySpawnPoint(config.ammo_standard, 610, 1010);
	CopySpawnPoint(config.upgrade_slime, 290, 1170);
	CopySpawnPoint(config.weapon_energy, 2170, 1230);
	CopySpawnPoint(config.ammo_energy, 2150, 1230);
	CopySpawnPoint(config.weapon_pumpgun, 2070, 880);
	CopySpawnPoint(config.ammo_standard, 2090, 880);
	CopySpawnPoint(config.upgrade_laser, 1900, 800);
	CopySpawnPoint(config.weapon_energy, 2170, 410);
	CopySpawnPoint(config.ammo_energy, 2150, 410);
	CopySpawnPoint(config.weapon_pumpgun, 1610, 600);
	CopySpawnPoint(config.item_drone, 1980, 640);
	CopySpawnPoint(config.item_medipack, 1090, 350);
	CopySpawnPoint(config.weapon_mine, 660, 550);
	CopySpawnPoint(config.weapon_mine, 1430, 840);
	CopySpawnPoint(config.ammo_grenade, 760, 680);
	CopySpawnPoint(config.ammo_grenade, 1540, 270);
	CopySpawnPoint(config.ammo_energy, 1100, 20);
	CopySpawnPoint(config.ammo_standard, 990, 930);
	CopySpawnPoint(config.weapon_minigun, 160, 590);
	CopySpawnPoint(config.ammo_standard, 180, 590);
	CopySpawnPoint(config.weapon_motegun, 410, 1190);
	CopySpawnPoint(config.ammo_energy, 430, 1190);
	CopySpawnPoint(config.weapon_bazooka, 1780, 1260);
	CopySpawnPoint(config.ammo_missile, 1800, 1260);
	CopySpawnPoint(config.weapon_motegun, 1580, 640);
	CopySpawnPoint(config.ammo_energy, 1560, 640);
	// TODO PlaceBonusSpawnpoint([AMPB, BSKB, HELB, INVB, KAMB, RPFB], 740, 530);
	/* TODO
	aHivePos =
	[
		[[550, 940], [120, 910], [330, 880]],
		[[2400, 1100], [2080, 1100], [2200, 900]],
		[[2300, 600], [2050, 600], [1800, 700]],
		[[300, 333], [280, 100]],
		[[1100, 800], [850, 600], [1000, 600]]
	];
	*/
	// remove template spawn points
	RemoveSpawnPointTemplates(config);
}


//func AddWares(object wp)
//{
//	// und begrenzte Waren...
//	wp->RemoveWare();
//	wp->AddWare(weapon_pistol, -1); // Pistole
//	wp->AddWare(weapon_energy, -1); // Energiegewehr
//	wp->AddWare(weapon_pumpgun, -1); // Pumpgun
//	wp->AddWare(weapon_motegun, -1); // Partikelkanone
//	wp->AddWare(weapon_bazooka, -1); // Bazooka
//	wp->AddWare(weapon_minigun, -1); // Minigun
//	wp->AddWare(upgrade_rifle, -1); // Waffenteile
//	wp->AddWare(KSLM, -1); // Schleim
//	wp->AddWare(FLSH, -1); // Taschenlampe
//	wp->AddWare(AIRT, -1); // Luft!
//	wp->AddWare(item_armor, -1); // R�stung
//	wp->AddWare(DRSU, -1); // Drone
//	wp->AddWare(item_medipack, -1); // Medipack
//	//wp->SortWare();
//}


/* Relaunch */

func RelaunchLocations()
{
	return 
	[
		{x =   30, y =   80, team = 1},
		{x = 2400, y = 1220, team = 2},
		{x =  120, y =  720, team = 3},
		{x = 2280, y =  400, team = 4},
	];
}

