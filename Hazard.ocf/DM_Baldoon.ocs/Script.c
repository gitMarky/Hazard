#include Library_DefaultScript

static vent1, vent2;
static light1, light2, light3;
static aTeleporters;

func Initialize()
{
	SetGoal(SCENPAR_HAZARD_GOAL);

	_inherited(...);

	aTeleporters = [];
	
	SetSkyParallax(0, 15);
	
	CreateLights();
	CreateDeco();
	CreateTrees();
	CreateArena();	
	CreateSpawnPoints();
	CreateWaypoints();
}

func CreateLights()
{
	CreateObjectAbove(CLGH, 265, 455, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 585, 405, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 625, 405, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 235, 315, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 565, 495, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 685, 535, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 255, 615, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 305, 615, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 625, 925, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 675, 925, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 725, 925, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 445, 465, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 635, 335, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 635, 265, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 1015, 355, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 1575, 365, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 1785, 315, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 1465, 115, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 1725, 585, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 1725, 655, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 1915, 565, NO_OWNER)->TurnOn();
	CreateObjectAbove(CLGH, 1545, 685, NO_OWNER)->TurnOn();
	CreateObjectAbove(LBGH, 250, 480, NO_OWNER)->SetCableLength(40)->GetLight()->TurnOn();
	CreateObjectAbove(LBGH, 350, 480, NO_OWNER)->SetCableLength(40)->GetLight()->TurnOn();
	CreateObjectAbove(LBGH, 1580, 250, NO_OWNER)->GetLight()->TurnOn();
	CreateObjectAbove(LLGH, 1670, 930, NO_OWNER)->TurnOn();
	CreateObjectAbove(LLGH, 1890, 930, NO_OWNER)->TurnOn();
	CreateObjectAbove(LLGH, 1615, 390, NO_OWNER)->TurnOn();
	CreateObjectAbove(LLGH, 1635, 390, NO_OWNER)->TurnOn();
	CreateObjectAbove(LLGH, 1615, 450, NO_OWNER)->TurnOn();
	CreateObjectAbove(LLGH, 1635, 450, NO_OWNER)->TurnOn();
	CreateObjectAbove(LLGH, 1615, 510, NO_OWNER)->TurnOn();
	CreateObjectAbove(LLGH, 1635, 510, NO_OWNER)->TurnOn();
	CreateObjectAbove(LLGH, 1615, 570, NO_OWNER)->TurnOn();
	CreateObjectAbove(LLGH, 1635, 570, NO_OWNER)->TurnOn();
	CreateObjectAbove(LLGH, 1615, 630, NO_OWNER)->TurnOn();
	CreateObjectAbove(LLGH, 1635, 630, NO_OWNER)->TurnOn();
	CreateObjectAbove(LLGH, 1615, 690, NO_OWNER)->TurnOn();
	CreateObjectAbove(LLGH, 1635, 690, NO_OWNER)->TurnOn();
	
	light1 = CreateObjectAbove(ALGH, 1390, 900, NO_OWNER);
	light2 = CreateObjectAbove(ALGH, 1450, 900, NO_OWNER);
	light3 = CreateObjectAbove(ALGH, 1510, 900, NO_OWNER);
}

func CreateDeco()
{
	CreateObject(Piranha, 20, 810, NO_OWNER); // TODO: Replace with shark
	CreateObject(Piranha, 120, 830, NO_OWNER); // TODO: Replace with shark
	CreateObject(EnvPack_Guidepost2, 1380, 380, NO_OWNER);
//	CreateObjectAbove(VINE, 60, 440, NO_OWNER)->SetCon(110);
//	CreateObjectAbove(VINE, 115, 110, NO_OWNER)->SetCon(120);
//	CreateObjectAbove(VINE, 118, 165, NO_OWNER)->SetCon(87);
//	CreateObjectAbove(VINE, 112, 200, NO_OWNER)->SetCon(104);
//	CreateObjectAbove(VINE, 115, 245, NO_OWNER)->SetCon(124);
//	CreateObjectAbove(VINE, 117, 270, NO_OWNER)->SetCon(98);
//	CreateObjectAbove(VINE, 115, 310, NO_OWNER)->SetCon(105);
//	CreateObjectAbove(VINE, 114, 340, NO_OWNER)->SetCon(109);
//	CreateObjectAbove(VINE, 675, 190, NO_OWNER)->SetCon(120);
//	CreateObjectAbove(VINE, 678, 245, NO_OWNER)->SetCon(87);
//	CreateObjectAbove(VINE, 672, 280, NO_OWNER)->SetCon(104);
//	CreateObjectAbove(VINE, 675, 325, NO_OWNER)->SetCon(124);
//	CreateObjectAbove(VINE, 677, 350, NO_OWNER)->SetCon(98);
//	CreateObjectAbove(VINE, 675, 390, NO_OWNER)->SetCon(105);
//	CreateObjectAbove(VINE, 965, 320, NO_OWNER)->SetCon(120);
//	CreateObjectAbove(VINE, 968, 375, NO_OWNER)->SetCon(87);
//	CreateObjectAbove(VINE, 962, 410, NO_OWNER)->SetCon(104);
//	CreateObjectAbove(VINE, 965, 455, NO_OWNER)->SetCon(124);
//	CreateObjectAbove(VINE, 967, 470, NO_OWNER)->SetCon(78);
//	CreateObjectAbove(VINE, 1055, 320, NO_OWNER)->SetCon(120);
//	CreateObjectAbove(VINE, 1058, 375, NO_OWNER)->SetCon(87);
//	CreateObjectAbove(VINE, 1052, 410, NO_OWNER)->SetCon(104);
//	CreateObjectAbove(VINE, 1055, 455, NO_OWNER)->SetCon(124);
//	CreateObjectAbove(VINE, 1057, 470, NO_OWNER)->SetCon(78);
//	CreateObjectAbove(VINE, 1435, 240, NO_OWNER)->SetCon(120);
//	CreateObjectAbove(VINE, 1438, 295, NO_OWNER)->SetCon(87);
//	CreateObjectAbove(VINE, 1434, 330, NO_OWNER)->SetCon(77);
//	CreateObjectAbove(VINE, 1405, 90, NO_OWNER)->SetCon(120);
//	CreateObjectAbove(VINE, 1408, 145, NO_OWNER)->SetCon(87);
//	CreateObjectAbove(VINE, 1404, 180, NO_OWNER)->SetCon(77);
	CreateObject(_FAK, 1880, 110, NO_OWNER);
	CreateObject(_FAK, 1630, 180, NO_OWNER);
	CreateObject(_FAK, 1390, 390, NO_OWNER);
	CreateObject(_FAK, 1380, 550, NO_OWNER);
	CreateObject(_FAK, 1270, 670, NO_OWNER);
	CreateObject(_FAK, 1240, 420, NO_OWNER);
	CreateObject(_FAK, 1100, 510, NO_OWNER);
	CreateObject(_FAK, 1090, 770, NO_OWNER);
	CreateObject(_FAK,  510, 880, NO_OWNER);
	CreateObject(_FAK,  500, 720, NO_OWNER);
	CreateObject(_FAK,   80, 550, NO_OWNER);
	CreateObject(_FAK,  760, 540, NO_OWNER);
	CreateObject(_FAK,  930, 540, NO_OWNER);
	
//	CreateObjectAbove(_RAN, 10, 0, NO_OWNER);
	CreateObject(Baldoon_Ambience, 165, 550, NO_OWNER);
	CreateObject(Baldoon_Source, 648, 780, NO_OWNER);

	vent1 = CreateObjectAbove(GAT2, 1420, 920, NO_OWNER);
	vent2 = CreateObjectAbove(GAT2, 1480, 920, NO_OWNER);
	
	CreateObject(RADR, 160, 75, NO_OWNER);
	
	//Labor
	CreateObjectAbove(Console, 1820, 920, NO_OWNER);
	CreateObjectAbove(LTBL, 1780, 940, NO_OWNER);
	CreateObject(GADG, 1780, 913, NO_OWNER);
	CreateObject(GADG, 1790, 913, NO_OWNER);
	CreateObject(MONI, 1770, 915, NO_OWNER);
	CreateObjectAbove(OPTB, 1880, 920, NO_OWNER);
	CreateObject(LBPC, 1700, 915, NO_OWNER);
	CreateObject(FRAM, 1760, 902, NO_OWNER);
	CreateObject(FRAM, 1850, 902, NO_OWNER);
	CreateObject(FRAM, 1805, 902, NO_OWNER);
	CreateObject(GSBO, 1860, 609, NO_OWNER);
	CreateObject(GSBO, 1880, 609, NO_OWNER);
	CreateObjectAbove(GLST, 1380, 950, NO_OWNER);
	CreateObjectAbove(VENT, 1800, 900, NO_OWNER)->SetCon(30);
	
	//Office
	CreateObjectAbove(OTBL, 1575, 330, NO_OWNER);
	CreateObjectAbove(OCHR, 1550, 330, NO_OWNER);
	CreateObjectAbove(OCHR, 1600, 330, NO_OWNER);
	CreateObjectAbove(OTBL, 1695, 380, NO_OWNER);
	CreateObjectAbove(OCHR, 1670, 380, NO_OWNER);
	CreateObjectAbove(OCHR, 1720, 380, NO_OWNER);
	CreateObjectAbove(CCP2, 1510, 230, NO_OWNER);
	CreateObjectAbove(DEB1, 1750, 190, NO_OWNER);
	
	//Base
	CreateObject(GSTA, 415, 540, NO_OWNER);
	CreateObject(BED2, 625, 285, NO_OWNER);
	CreateObject(BED2, 625, 355, NO_OWNER);
	CreateObject(CLVM, 230, 540, NO_OWNER);
	CreateObject(SPVM, 1560, 380, NO_OWNER);
	CreateObject(LCOM, 575, 472, NO_OWNER);
	CreateObject(LCOM, 595, 472, NO_OWNER);
	CreateObject(LCOM, 615, 472, NO_OWNER);
	CreateObject(FIEX, 240, 324, NO_OWNER);
	CreateObject(FIEX, 560, 504, NO_OWNER);
	CreateObject(FIEX, 670, 944, NO_OWNER);
	CreateObject(FIEX, 990, 534, NO_OWNER);
	CreateObject(FIEX, 1620, 934, NO_OWNER);
	CreateObject(FIEX, 1540, 234, NO_OWNER);
	CreateObject(FIEX, 1800, 284, NO_OWNER);
	CreateObject(GTBL, 240, 424, NO_OWNER);
	CreateObject(LCKR, 650, 375, NO_OWNER);
	CreateObject(LCKR, 650, 305, NO_OWNER);
	CreateObject(SBBA, 695, 512, NO_OWNER);
	CreateObject(CON1, 480, 256, NO_OWNER);
	CreateObject(PLNT, 330, 427, NO_OWNER);
	CreateObject(PLNT, 320, 547, NO_OWNER);
	CreateObject(PLT2, 630, 536, NO_OWNER);
	CreateObject(PLT2, 1650, 326, NO_OWNER);
	CreateObject(PLNT, 1740, 677, NO_OWNER);
	CreateObject(PLNT, 1700, 607, NO_OWNER);
	CreateObject(LFTP, 1625, 500, NO_OWNER)->SetLimits(395, 745);
	CreateObject(LFTP, 165, 500, NO_OWNER)->SetLimits(155, 545);
	;
	var liftp = CreateObject(LFTP, 870, 805, NO_OWNER);
	liftp->DisableVertical();
	liftp->ContactLeft();
	
	CreateObject(WoodenBridge, 776, 565, NO_OWNER);
	CreateObject(WoodenBridge, 848, 565, NO_OWNER);
	CreateObject(WoodenBridge, 920, 565, NO_OWNER);
	CreateObject(LADR,  592, 390, NO_OWNER)->LadderHeight(295, 390);
	CreateObject(LADR, 1976, 260, NO_OWNER)->LadderHeight(165, 260);
	CreateObject(LADR, 1636, 950, NO_OWNER)->LadderHeight(795, 950);
	CreateObject(LADR, 1471, 400, NO_OWNER)->LadderHeight(270, 400);
	CreateObject(LADR, 1481, 250, NO_OWNER)->LadderHeight( 90, 250);
	CreateObject(LADR, 1001, 410, NO_OWNER)->LadderHeight(315, 410);
	CreateObject(LADR, 1021, 550, NO_OWNER)->LadderHeight(400, 550);
	CreateObject(LADR, 1195, 740, NO_OWNER)->LadderHeight(500, 740);
	CreateObject(LADR,  490, 560, NO_OWNER)->LadderHeight(460, 560);
	CreateObject(LADR,  290, 440, NO_OWNER)->LadderHeight(330, 440);
	CreateObject(LADR,  575, 660, NO_OWNER)->LadderHeight(550, 660);
	CreateObject(TOIC, 340, 465, NO_OWNER);
	CreateObject(TOIC, 320, 465, NO_OWNER);
	CreateObject(TOIC, 300, 465, NO_OWNER);
	CreateObject(TOIC, 280, 465, NO_OWNER);
	CreateObject(WSHB, 240, 465, NO_OWNER);
	CreateObject(WSHB, 220, 465, NO_OWNER);
	
	CreateObject(STDR, 1535, 385, NO_OWNER)->OnDestroyed();
	CreateObject(LBDR, 1650, 935, NO_OWNER)->OnDestroyed();
	CreateObject(SLDR, 1925, 925, NO_OWNER);
	CreateObject(LBDR, 1840, 605, NO_OWNER);
	CreateObject(STDR, 1495, 275, NO_OWNER)->OnDestroyed();
	CreateObject(SLDR, 1435, 385, NO_OWNER);
	CreateObject(STDR, 965, 535, NO_OWNER);
	CreateObject(STDR, 1055, 535, NO_OWNER);
	CreateObject(STDR, 585, 235, NO_OWNER);
	CreateObject(SLDR, 345, 655, NO_OWNER);
	CreateObject(STDR, 1525, 705, NO_OWNER)->OnDestroyed();
	CreateObject(STDR, 1565, 705, NO_OWNER);
	CreateObject(SLDR, 1165, 495, NO_OWNER);
	CreateObject(STDR, 575, 375, NO_OWNER);
	CreateObject(STDR, 705, 545, NO_OWNER);
	CreateObject(STDR, 535, 545, NO_OWNER);
	CreateObject(STDR, 665, 545, NO_OWNER)->OnDestroyed();
	CreateObject(STDR, 545, 465, NO_OWNER);
	CreateObject(STDR, 205, 465, NO_OWNER);
	CreateObject(STDR, 205, 325, NO_OWNER);
	CreateObject(STDR, 205, 145, NO_OWNER);
	
	CreateObject(_WIN, 270, 412, NO_OWNER);
	CreateObject(_WIN, 620, 292, NO_OWNER);
	CreateObject(_WIN, 620, 362, NO_OWNER);
	CreateObject(_WIN, 580, 452, NO_OWNER);
	CreateObject(_WIN, 630, 452, NO_OWNER);
	CreateObject(_WIN, 1940, 592, NO_OWNER);
	CreateObject(_WIN, 1890, 592, NO_OWNER);
	CreateObject(_WIN, 1780, 352, NO_OWNER);
	CreateObject(_WIN, 1720, 372, NO_OWNER);
	CreateObject(_WIN, 1610, 322, NO_OWNER);
	CreateObject(_WIN, 1500, 372, NO_OWNER);
	CreateObject(_WIN, 1500, 332, NO_OWNER);
	CreateObject(_WIN, 1490, 222, NO_OWNER);
	CreateObject(_WIN, 1460, 192, NO_OWNER);
	CreateObject(_WIN, 1460, 142, NO_OWNER);
	CreateObject(_WIN, 280, 642, NO_OWNER);
	CreateObject(_WIN, 1010, 382, NO_OWNER);
	CreateObject(_WIN, 170, 172, NO_OWNER);
	CreateObject(_WIN, 160, 232, NO_OWNER);
	CreateObject(_WIN, 170, 292, NO_OWNER);
	CreateObject(_WIN, 160, 352, NO_OWNER);
	CreateObject(_WIN, 170, 412, NO_OWNER);
	CreateObject(_WIN, 160, 472, NO_OWNER);
	CreateObject(_WIN, 170, 532, NO_OWNER);
	CreateObject(_WIN, 370, 532, NO_OWNER);
	CreateObject(_WIN, 270, 532, NO_OWNER);
	CreateObject(_WIN, 470, 532, NO_OWNER);
	CreateObject(_WIN, 630, 532, NO_OWNER);
}

func CreateTrees()
{
	var area1 = Rectangle(0, 0, 1450, 560);
	var area2 = Rectangle(1440, 0, 650, 250);
	Tree_Coniferous->Place(5, area1);
	Tree_Coniferous2->Place(4, area1);
	Tree_Coniferous3->Place(5, area1);
	Tree_Coniferous4->Place(2, area1);
	
	Tree_Coniferous2->Place(2, area2);
	Tree_Coniferous3->Place(3, area2);
}

func CreateArena()
{
	// artillery
//	CreateObjectAbove(_ART,  480, 220, NO_OWNER);
//	CreateObjectAbove(_ART, 1795, 190, NO_OWNER);
	
	// jump pads
	CreateObject(JMPD, 1420,  86)->Set(100, +45);
	CreateObject(JMPD,  770, 946)->Set( 82, +35);
	CreateObject(JMPD,  980, 316)->Set(140, +18);
	CreateObject(JMPD,  660, 176)->Set(130, -20);
	CreateObject(JMPD,  300, 136)->Set( 80, +30);
	CreateObject(JMPD, 1030, 916)->Set( 85, -40);
	CreateObject(JMPD,  580, 176)->Set(110, +20);
	CreateObject(JMPD, 1040, 316)->Set(113, -28);
	CreateObject(JMPD, 1200, 431)->Set( 98, -15);
	CreateObject(JMPD, 1210, 431)->Set(140, +12);
	
	// teleports
	var teletarget1 = CreateObject(TELE, 625, 225, NO_OWNER);
	var teletarget2 = CreateObject(TELE, 1295, 915, NO_OWNER);
	teletarget1->SetTarget(teletarget2);
	teletarget2->SetTarget(teletarget1);

	aTeleporters[0] = teletarget1;
	aTeleporters[1] = teletarget2;
}

func CreateSpawnPoints()
{
	// configure spawn points
	var ammo_standard = CreateSpawnPoint(0, 0)->SpawnItem(STAP);
	var ammo_grenade = CreateSpawnPoint(0, 0)->SpawnItem(GRAP);
	var ammo_gasoline = CreateSpawnPoint(0, 0)->SpawnItem(GSAP);
	var ammo_energy = CreateSpawnPoint(0, 0)->SpawnItem(ENAP);
	var ammo_missile = CreateSpawnPoint(0, 0)->SpawnItem(MIAP);
	
	var upgrade_laser = CreateSpawnPoint(0, 0)->SpawnItem(Upgrade_Laser);
	var upgrade_slime = CreateSpawnPoint(0, 0)->SpawnItem(Upgrade_Slime);
	var upgrade_rifle = CreateSpawnPoint(0, 0)->SpawnItem(Upgrade_WeaponPart);
	
	var weapon_pumpgun = CreateSpawnPoint(0, 0)->SpawnItem(Weapon_Pumpgun);
	var weapon_grenade = CreateSpawnPoint(0, 0)->SpawnItem(Weapon_GrenadeLauncher);
	var weapon_flame = CreateSpawnPoint(0, 0)->SpawnItem(Weapon_FlameThrower);
	var weapon_bazooka = CreateSpawnPoint(0, 0)->SpawnItem(Weapon_Bazooka);
	var weapon_energy = CreateSpawnPoint(0, 0)->SpawnItem(Weapon_EnergyRifle);
	var weapon_motegun= CreateSpawnPoint(0, 0)->SpawnItem(Weapon_Motegun);
	var weapon_mine = CreateSpawnPoint(0, 0)->SpawnItem(MINE);
	var weapon_minigun= CreateSpawnPoint(0, 0)->SpawnItem(Weapon_Minigun);
	
	var item_jetpack = CreateSpawnPoint(0, 0)->SpawnItem(Gear_Jetpack);
	var item_medipack = CreateSpawnPoint(0, 0)->SpawnItem(MEDI);
	var item_airstrike = CreateSpawnPoint(0, 0)->SpawnItem(AIRS);
	var item_armor = CreateSpawnPoint(0, 0)->SpawnItem(HARM);

	// place spawn points
	CopySpawnPoint(item_airstrike, 80, 848);
	CopySpawnPoint(item_airstrike, 1960, 83);
	CopySpawnPoint(weapon_bazooka, 1500, 238);
	CopySpawnPoint(weapon_bazooka, 140, 88);
	CopySpawnPoint(ammo_missile, 1520, 238);
	CopySpawnPoint(ammo_missile, 160, 88);
	CopySpawnPoint(weapon_energy, 300, 548);
	CopySpawnPoint(ammo_energy, 320, 548);
	CopySpawnPoint(ammo_energy, 1660, 818);
	CopySpawnPoint(weapon_flame, 610, 378);
	CopySpawnPoint(weapon_flame, 1900, 608);
	CopySpawnPoint(ammo_gasoline, 630, 378);
	CopySpawnPoint(ammo_gasoline, 1920, 608);
	CopySpawnPoint(ammo_gasoline, 230, 333);
	CopySpawnPoint(weapon_grenade, 610, 178);
	CopySpawnPoint(weapon_grenade, 660, 948);
	CopySpawnPoint(ammo_grenade, 680, 948);
	CopySpawnPoint(ammo_grenade, 250, 148);
	CopySpawnPoint(ammo_grenade, 630, 178);
	CopySpawnPoint(weapon_minigun, 1880, 313);
	CopySpawnPoint(weapon_minigun, 1440, 958);
	CopySpawnPoint(ammo_standard, 1460, 958);
	CopySpawnPoint(ammo_standard, 1900, 313);
	CopySpawnPoint(weapon_motegun, 280, 778);
	CopySpawnPoint(ammo_energy, 300, 778);
	CopySpawnPoint(weapon_pumpgun, 1370, 548);
	CopySpawnPoint(ammo_standard, 1390, 548);
	CopySpawnPoint(ammo_standard, 1720, 468);
	CopySpawnPoint(weapon_mine, 500, 718);
	CopySpawnPoint(weapon_mine, 1850, 938);
	CopySpawnPoint(item_jetpack, 220, 428);
	CopySpawnPoint(item_jetpack, 1750, 938);
	CopySpawnPoint(upgrade_rifle, 510, 878);
	CopySpawnPoint(upgrade_rifle, 1630, 178);
	CopySpawnPoint(upgrade_laser, 830, 548);
	CopySpawnPoint(upgrade_laser, 1720, 608);
	CopySpawnPoint(upgrade_slime, 1160, 748);
	CopySpawnPoint(item_medipack, 1000, 538);
	CopySpawnPoint(item_armor, 1010, 318);
	CopySpawnPoint(item_airstrike, 1130, 498);
//	PlaceBonusSpawnpoint([AEXB, BSKB, HELB, KAMB], 1510, 798, 2000);
//	PlaceBonusSpawnpoint([AMPB, HSTB, INVB, RPFB], 250, 658, 2000);

	// more stuff if there are 6 or more players
	if (GetPlayerCount() > 5)
	{
		CopySpawnPoint(weapon_energy, 1440, 708);
		CopySpawnPoint(ammo_energy, 1460, 708);
		CopySpawnPoint(weapon_pumpgun, 280, 428);
		CopySpawnPoint(ammo_standard, 300, 428);
		CopySpawnPoint(item_medipack, 550, 238);
		CopySpawnPoint(item_medipack, 1720, 678);
	}

	// remove template spawn points
	ammo_standard->RemoveObject();
	ammo_grenade->RemoveObject();
	ammo_gasoline->RemoveObject();
	ammo_energy->RemoveObject();
	ammo_missile->RemoveObject();
	
	upgrade_laser->RemoveObject();
	upgrade_slime->RemoveObject();
	upgrade_rifle->RemoveObject();

	weapon_pumpgun->RemoveObject();
	weapon_grenade->RemoveObject();
	weapon_flame->RemoveObject();
	weapon_bazooka->RemoveObject();
	weapon_energy->RemoveObject();
	weapon_motegun->RemoveObject();
	weapon_mine->RemoveObject();
	weapon_minigun->RemoveObject();
	
	item_medipack->RemoveObject();
	item_jetpack->RemoveObject();
	item_airstrike->RemoveObject();
	item_armor->RemoveObject();
}

func CreateWaypoints()
{
	var wp1 = CreateWP(1417, 90);
	var wp2 = CreateWP(1839, 610);
	var wp3 = CreateWP(1658, 679);
	var wp4 = CreateWP(1813, 680);
	var wp5 = CreateWP(1918, 609);
	var wp6 = CreateWP(1956, 167);
	var wp7 = CreateWP(1968, 265);
	var wp8 = CreateWP(1502, 238);
	var wp9 = CreateWP(1677, 194);
	var wp10 = CreateWP(1452, 88);
	var wp11 = CreateWP(1959, 82);
	var wp12 = CreateWP(1794, 199);
	var wp13 = CreateWP(1549, 238);
	var wp14 = CreateWP(1658, 607);
	var wp15 = CreateWP(1224, 426);
	var wp16 = CreateWP(1185, 435);
	var wp17 = CreateWP(1484, 391);
	var wp18 = CreateWP(1594, 391);
	var wp19 = CreateWP(1659, 389);
	var wp20 = CreateWP(1489, 282);
	var wp21 = CreateWP(1602, 342);
	var wp22 = CreateWP(1648, 342);
	var wp23 = CreateWP(1766, 274);
	var wp24 = CreateWP(1875, 311);
	var wp25 = CreateWP(1922, 314);
	var wp26 = CreateWP(1657, 513);
	var wp27 = CreateWP(999, 534);
	var wp28 = CreateWP(657, 180);
	var wp29 = CreateWP(638, 548);
	var wp30 = CreateWP(505, 549);
	var wp31 = CreateWP(574, 548);
	var wp32 = CreateWP(464, 548);
	var wp33 = CreateWP(166, 537);
	var wp34 = CreateWP(418, 469);
	var wp35 = CreateWP(620, 378);
	var wp36 = CreateWP(202, 145);
	var wp37 = CreateWP(288, 140);
	var wp38 = CreateWP(641, 180);
	var wp39 = CreateWP(582, 180);
	var wp40 = CreateWP(140, 89);
	var wp41 = CreateWP(231, 326);
	var wp42 = CreateWP(222, 428);
	var wp43 = CreateWP(321, 429);
	var wp44 = CreateWP(515, 468);
	var wp45 = CreateWP(1407, 546);
	var wp46 = CreateWP(1017, 319);
	var wp47 = CreateWP(1540, 388);
	var wp48 = CreateWP(1590, 711);
	var wp49 = CreateWP(1215, 578);
	var wp50 = CreateWP(1215, 653);
	var wp51 = CreateWP(1134, 498);
	var wp52 = CreateWP(1185, 744);
	var wp53 = CreateWP(991, 797);
	var wp54 = CreateWP(249, 656);
	var wp55 = CreateWP(507, 717);
	var wp56 = CreateWP(554, 680);
	var wp57 = CreateWP(764, 947);
	var wp58 = CreateWP(596, 944);
	var wp59 = CreateWP(544, 877);
	var wp60 = CreateWP(463, 912);
	var wp61 = CreateWP(356, 892);
	var wp62 = CreateWP(361, 787);
	var wp63 = CreateWP(752, 796);
	var wp64 = CreateWP(459, 767);
	var wp65 = CreateWP(289, 774);
	var wp66 = CreateWP(197, 819);
	var wp67 = CreateWP(627, 238);
	var wp68 = CreateWP(1036, 319);
	var wp69 = CreateWP(986, 320);
	var wp70 = CreateWP(1651, 752);
	var wp71 = CreateWP(1657, 821);
	var wp72 = CreateWP(1849, 938);
	var wp73 = CreateWP(1818, 936);
	var wp74 = CreateWP(1652, 939);
	var wp75 = CreateWP(1608, 939);
	var wp76 = CreateWP(1297, 941);
	var wp77 = CreateWP(1038, 919);
	wp1->AddPath(wp11, Path_MoveTo, 1);
	wp2->AddPath(wp5, Path_MoveTo, 1);
	wp2->AddPath(wp14, Path_Backflip, -1);
	wp2->AddPath(wp3, Path_MoveTo, -1);
	wp3->AddPath(wp4, Path_MoveTo, 1);
	wp3->AddPath(wp48, Path_MoveTo, -1);
	wp3->AddPath(wp18, Path_Lift, -1);
	wp3->AddPath(wp19, Path_Lift, 1);
	wp3->AddPath(wp26, Path_Lift, -1);
	wp4->AddPath(wp3, Path_MoveTo, -1);
	wp4->AddPath(wp14, Path_Jump, -1);
	wp4->AddPath(wp2, Path_Jump, 1);
	wp4->AddPath(wp2, Path_MoveTo, 1);
	wp5->AddPath(wp2, Path_MoveTo, -1);
	wp6->AddPath(wp12, Path_MoveTo, -1);
	wp8->AddPath(wp10, Path_Jump, -1);
	wp8->AddPath(wp13, Path_MoveTo, 1);
	wp9->AddPath(wp12, Path_Jump, 1);
	wp9->AddPath(wp23, Path_MoveTo, 1);
	wp9->AddPath(wp13, Path_MoveTo, -1);
	wp10->AddPath(wp1, Path_MoveTo, -1);
	wp10->AddPath(wp8, Path_MoveTo, 1);
	wp10->AddPath(wp9, Path_Jump, 1);
	wp10->AddPath(wp13, Path_Jump, 1);
	wp11->AddPath(wp12, Path_MoveTo, -1);
	wp12->AddPath(wp6, Path_Jump, 1);
	wp12->AddPath(wp9, Path_MoveTo, -1);
	wp13->AddPath(wp8, Path_MoveTo, -1);
	wp13->AddPath(wp9, Path_Jump, 1);
	wp14->AddPath(wp48, Path_Lift, -1);
	wp14->AddPath(wp18, Path_Lift, -1);
	wp14->AddPath(wp19, Path_Lift, 1);
	wp15->AddPath(wp17, Path_MoveTo, 1);
	wp17->AddPath(wp20, Path_Jump, 1);
	wp17->AddPath(wp15, Path_MoveTo, -1);
	wp18->AddPath(wp47, Path_MoveTo, -1);
	wp18->AddPath(wp19, Path_Backflip, 1);
	wp18->AddPath(wp48, Path_Lift, -1);
	wp18->AddPath(wp26, Path_Lift, 1);
	wp18->AddPath(wp14, Path_Lift, 1);
	wp18->AddPath(wp3, Path_Lift, 1);
	wp19->AddPath(wp24, Path_MoveTo, 1);
	wp19->AddPath(wp18, Path_Backflip, -1);
	wp19->AddPath(wp26, Path_Lift, -1);
	wp19->AddPath(wp48, Path_Lift, -1);
	wp19->AddPath(wp14, Path_Lift, -1);
	wp19->AddPath(wp3, Path_Lift, -1);
	wp21->AddPath(wp22, Path_Jump, 1);
	wp21->AddPath(wp20, Path_Jump, -1);
	wp22->AddPath(wp21, Path_Jump, -1);
	wp22->AddPath(wp23, Path_MoveTo, 1);
	wp22->AddPath(wp23, Path_Jump, 1);
	wp23->AddPath(wp9, Path_Jump, -1);
	wp23->AddPath(wp22, Path_MoveTo, -1);
	wp24->AddPath(wp23, Path_Jump, -1);
	wp24->AddPath(wp19, Path_MoveTo, -1);
	wp24->AddPath(wp25, Path_MoveTo, 1);
	wp25->AddPath(wp7, Path_Jump, 1);
	wp25->AddPath(wp24, Path_MoveTo, -1);
	wp26->AddPath(wp18, Path_Lift, -1);
	wp26->AddPath(wp19, Path_Lift, 1);
	wp26->AddPath(wp48, Path_Lift, -1);
	wp26->AddPath(wp3, Path_Lift, 1);
	wp27->AddPath(wp29, Path_MoveTo, -1);
	wp27->AddPath(wp51, Path_MoveTo, 1);
	wp27->AddPath(wp46, Path_Jump, 1);
	wp28->AddPath(wp40, Path_MoveTo, -1);
	wp29->AddPath(wp30, Path_Jump, -1);
	wp29->AddPath(wp27, Path_MoveTo, 1);
	wp30->AddPath(wp29, Path_Jump, 1);
	wp30->AddPath(wp31, Path_MoveTo, 1);
	wp31->AddPath(wp30, Path_MoveTo, -1);
	wp31->AddPath(wp56, Path_MoveTo, -1);
	wp32->AddPath(wp30, Path_MoveTo, 1);
	wp32->AddPath(wp33, Path_MoveTo, -1);
	wp32->AddPath(wp44, Path_Jump, 1);
	wp33->AddPath(wp36, Path_Lift, 1);
	wp33->AddPath(wp41, Path_Lift, 1);
	wp33->AddPath(wp32, Path_MoveTo, 1);
	wp34->AddPath(wp32, Path_MoveTo, 1);
	wp35->AddPath(wp32, Path_MoveTo, -1);
	wp36->AddPath(wp41, Path_Lift, 1);
	wp36->AddPath(wp33, Path_Lift, -1);
	wp36->AddPath(wp37, Path_MoveTo, 1);
	wp37->AddPath(wp38, Path_MoveTo, 1);
	wp38->AddPath(wp28, Path_MoveTo, 1);
	wp38->AddPath(wp39, Path_MoveTo, -1);
	wp38->AddPath(wp27, Path_Jump, 1);
	wp39->AddPath(wp46, Path_MoveTo, 1);
	wp41->AddPath(wp36, Path_Lift, -1);
	wp41->AddPath(wp33, Path_Lift, -1);
	wp41->AddPath(wp43, Path_MoveTo, 1);
	wp42->AddPath(wp43, Path_MoveTo, 1);
	wp43->AddPath(wp34, Path_MoveTo, 1);
	wp43->AddPath(wp42, Path_MoveTo, -1);
	wp43->AddPath(wp41, Path_Jump, -1);
	wp44->AddPath(wp35, Path_Jump, 1);
	wp45->AddPath(wp49, Path_MoveTo, -1);
	wp45->AddPath(wp47, Path_Jump, 1);
	wp46->AddPath(wp29, Path_Jump, -1);
	wp46->AddPath(wp51, Path_Jump, 1);
	wp46->AddPath(wp68, Path_MoveTo, 1);
	wp46->AddPath(wp69, Path_MoveTo, -1);
	wp47->AddPath(wp17, Path_Jump, -1);
	wp47->AddPath(wp45, Path_MoveTo, -1);
	wp47->AddPath(wp18, Path_MoveTo, 1);
	wp47->AddPath(wp17, Path_Backflip, -1);
	wp48->AddPath(wp50, Path_MoveTo, -1);
	wp48->AddPath(wp18, Path_Lift, 1);
	wp48->AddPath(wp19, Path_Lift, 1);
	wp48->AddPath(wp26, Path_Lift, 1);
	wp48->AddPath(wp14, Path_Lift, 1);
	wp48->AddPath(wp3, Path_Jump, 1);
	wp48->AddPath(wp70, Path_MoveTo, 1);
	wp49->AddPath(wp51, Path_MoveTo, -1);
	wp49->AddPath(wp52, Path_MoveTo, -1);
	wp49->AddPath(wp45, Path_MoveTo, 1);
	wp50->AddPath(wp48, Path_MoveTo, 1);
	wp51->AddPath(wp49, Path_MoveTo, 1);
	wp51->AddPath(wp50, Path_MoveTo, 1);
	wp51->AddPath(wp52, Path_MoveTo, 1);
	wp51->AddPath(wp27, Path_MoveTo, -1);
	wp51->AddPath(wp16, Path_Jump, 1);
	wp52->AddPath(wp50, Path_Jump, 1);
	wp52->AddPath(wp49, Path_Jump, 1);
	wp52->AddPath(wp51, Path_Jump, 1);
	wp52->AddPath(wp53, Path_MoveTo, -1);
	wp53->AddPath(wp63, Path_Lift, -1);
	wp53->AddPath(wp52, Path_MoveTo, 1);
	wp54->AddPath(wp55, Path_MoveTo, 1);
	wp55->AddPath(wp54, Path_Jump, -1);
	wp55->AddPath(wp56, Path_MoveTo, 1);
	wp55->AddPath(wp64, Path_MoveTo, -1);
	wp56->AddPath(wp55, Path_MoveTo, -1);
	wp56->AddPath(wp31, Path_Jump, 1);
	wp57->AddPath(wp53, Path_MoveTo, 1);
	wp58->AddPath(wp57, Path_MoveTo, 1);
	wp59->AddPath(wp58, Path_MoveTo, 1);
	wp60->AddPath(wp59, Path_MoveTo, 1);
	wp61->AddPath(wp60, Path_MoveTo, 1);
	wp62->AddPath(wp61, Path_MoveTo, -1);
	wp63->AddPath(wp64, Path_MoveTo, -1);
	wp63->AddPath(wp53, Path_Lift, 1);
	wp64->AddPath(wp55, Path_Jump, 1);
	wp64->AddPath(wp65, Path_MoveTo, -1);
	wp64->AddPath(wp62, Path_MoveTo, -1);
	wp64->AddPath(wp63, Path_MoveTo, 1);
	wp65->AddPath(wp62, Path_MoveTo, 1);
	wp65->AddPath(wp64, Path_MoveTo, 1);
	wp66->AddPath(wp65, Path_MoveTo, 1);
	wp67->AddPath(wp76, Path_MoveTo, 1);
	wp67->SetArriveCommand(0, 0, {Prototype = Command, command = "Enter", target = aTeleporters[0]});
	wp68->AddPath(wp38, Path_MoveTo, -1);
	wp69->AddPath(wp10, Path_MoveTo, 1);
	wp70->AddPath(wp48, Path_Jump, -1);
	wp71->AddPath(wp75, Path_MoveTo, -1);
	wp71->AddPath(wp74, Path_MoveTo, -1);
	wp71->AddPath(wp70, Path_Jump, 1);
	wp72->AddPath(wp73, Path_MoveTo, -1);
	wp73->AddPath(wp72, Path_MoveTo, 1);
	wp73->AddPath(wp74, Path_MoveTo, -1);
	wp74->AddPath(wp73, Path_MoveTo, 1);
	wp74->AddPath(wp75, Path_MoveTo, -1);
	wp74->AddPath(wp71, Path_Jump, -1);
	wp75->AddPath(wp74, Path_MoveTo, 1);
	wp75->AddPath(wp71, Path_Jump, 1);
	wp75->AddPath(wp76, Path_MoveTo, -1);
	wp76->AddPath(wp67, Path_MoveTo, -1);
	wp76->SetArriveCommand(0, 0,  {Prototype = Command, command = "Enter", target = aTeleporters[1]});
	wp76->AddPath(wp75, Path_MoveTo, 1);
	wp76->AddPath(wp77, Path_MoveTo, -1);
	wp77->AddPath(wp63, Path_MoveTo, -1);
	wp77->AddPath(wp76, Path_MoveTo, 1);
}

/* TODO: Regelwaehler */

//func ChooserFinished()
//{
//	Arena_ChooserFinished();
//	
//	if (FindObject(WPCH))
//		FindObject(WPCH)->RemoveWare(AIRT);
//}


func RelaunchLocations()
{
	return [{x = 190,  y =  90, team = NO_OWNER},
			{x = 90,   y = 430, team = NO_OWNER},
			{x = 610,  y = 380, team = NO_OWNER},
			{x = 450,  y = 770, team = NO_OWNER},
			{x = 990,  y = 400, team = NO_OWNER},
			{x = 1140, y = 940, team = NO_OWNER},
			{x = 1320, y = 560, team = NO_OWNER},
			{x = 1870, y = 610, team = NO_OWNER},
			{x = 1650, y = 340, team = NO_OWNER},
			{x = 1440, y =  90, team = NO_OWNER}];
}
