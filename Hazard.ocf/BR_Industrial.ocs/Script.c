#include Library_DefaultScript

func Initialize()
{
	SetGoal(SCENPAR_HAZARD_GOAL);

    _inherited(...);
    
	CreateLights();
}

func CreateBackground()
{
	SetSkyParallax(0, 12, 12, 0, 0, 0, 0);
}

func CreateDeco()
{
	CreateObject(AWRP, 750, 491, NO_OWNER)->SetDestination(747, 373);
	CreateObject(AWRP, 160, 521, NO_OWNER)->SetDestination(613, 51);
	CreateObject(AWRP, 1340, 521, NO_OWNER)->SetDestination(884, 52);
	CreateObjectAbove(SEGU, 748, 108, NO_OWNER)->Arm(RGSA);

	CreateObjectAbove(LADR, 965, 108, NO_OWNER)->LadderHeight(60, 108);
	CreateObjectAbove(LADR, 539, 108, NO_OWNER)->LadderHeight(60, 108);
	CreateObjectAbove(LADR, 699, 230, NO_OWNER)->LadderHeight(180, 230);
	CreateObjectAbove(LADR, 802, 230, NO_OWNER)->LadderHeight(180, 230);
	CreateObjectAbove(LADR, 808, 144, NO_OWNER)->LadderHeight(54, 144);
	CreateObjectAbove(LADR, 696, 144, NO_OWNER)->LadderHeight(54, 144);
	CreateObjectAbove(LADR,1467, 537, NO_OWNER)->LadderHeight(140, 537);
	CreateObjectAbove(LADR,  37, 537, NO_OWNER)->LadderHeight(140, 537);
	CreateObjectAbove(LADR, 864, 550, NO_OWNER)->LadderHeight(390, 550);
	CreateObjectAbove(LADR, 638, 550, NO_OWNER)->LadderHeight(390, 550);

	CreateObject(GSTA, 749, 171, NO_OWNER);
	CreateObject(GSBO, 704, 389, NO_OWNER);
	CreateObject(GSBO, 802, 389, NO_OWNER);
	CreateObject(GSBO, 1088, 408, NO_OWNER);
	CreateObject(GSBO, 1097, 408, NO_OWNER);
	CreateObject(GSBO, 374, 429, NO_OWNER);
	CreateObject(GSBO, 365, 429, NO_OWNER);

	CreateObject(JMPD, 1324, 316, NO_OWNER)->Set(100, -40);
	CreateObject(JMPD, 177, 316, NO_OWNER)->Set(100, 40);
	CreateObject(JMPD, 831, 306, NO_OWNER)->Set(70, 10);
	CreateObject(JMPD, 670, 306, NO_OWNER)->Set(70, -10);
	CreateObject(CON1, 1370, 176, NO_OWNER);
	CreateObject(CON1, 1045, 407, NO_OWNER);
	CreateObject(CON1, 130, 176, NO_OWNER);
	CreateObject(CON1, 448, 407, NO_OWNER);
	CreateObject(LFTP, 965, 185, NO_OWNER)->DisableVertical();
	CreateObject(LFTP, 533, 185, NO_OWNER)->DisableVertical();

	CreateObject(FIEX, 1374, 450, NO_OWNER);
	CreateObject(FIEX, 86, 450, NO_OWNER);

	CreateObject(RAI1, 880, 184, NO_OWNER)->SetRailLength(3);
	CreateObject(RAI1, 560, 184, NO_OWNER)->SetRailLength(3);
	CreateObject(RAI2, 816, 64, NO_OWNER)->SetRailLength(7);
	CreateObject(RAI2, 546, 64, NO_OWNER)->SetRailLength(7);

	CreateObject(ENGT, 1396, 376, NO_OWNER);
	CreateObject(ENGT, 105, 376, NO_OWNER);
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
	var weapon_minigun = CreateSpawnPoint(0, 0)->SpawnItem(Weapon_Minigun);
	var weapon_grenade = CreateSpawnPoint(0, 0)->SpawnItem(Weapon_GrenadeLauncher);
	var weapon_flame = CreateSpawnPoint(0, 0)->SpawnItem(Weapon_FlameThrower);
	var weapon_bazooka = CreateSpawnPoint(0, 0)->SpawnItem(Weapon_Bazooka);
	var weapon_energy = CreateSpawnPoint(0, 0)->SpawnItem(Weapon_EnergyRifle);
	var weapon_mine= CreateSpawnPoint(0, 0)->SpawnItem(MINE);
	
	var item_novodekan = CreateSpawnPoint(0, 0)->SpawnItem(NVDN);
	var item_armor = CreateSpawnPoint(0, 0)->SpawnItem(HARM);

	// place spawn points
	
	CopySpawnPoint(ammo_standard, 1384, 147);
	CopySpawnPoint(ammo_standard, 1367, 147);
	CopySpawnPoint(weapon_pumpgun, 1352, 147);
	CopySpawnPoint(upgrade_rifle, 1423, 251);
	CopySpawnPoint(upgrade_laser, 1159, 182);
	CopySpawnPoint(upgrade_slime, 1397, 401);
	CopySpawnPoint(ammo_grenade, 1387, 462);
	CopySpawnPoint(ammo_grenade, 1374, 463);
	CopySpawnPoint(weapon_grenade, 1395, 462);
	CopySpawnPoint(ammo_gasoline, 1453, 111);
	CopySpawnPoint(ammo_gasoline, 1463, 110);
	CopySpawnPoint(weapon_flame, 1439, 110);
	CopySpawnPoint(ammo_energy, 1437, 321);
	CopySpawnPoint(ammo_energy, 1422, 322);
	CopySpawnPoint(weapon_energy, 1407, 322);
	CopySpawnPoint(item_armor, 751, 279);
	CopySpawnPoint(item_novodekan, 911, 185);
	CopySpawnPoint(item_novodekan, 590, 185);
	CopySpawnPoint(ammo_standard, 739, 524);
	CopySpawnPoint(ammo_standard, 765, 524);
	CopySpawnPoint(weapon_minigun, 751, 524);
	CopySpawnPoint(weapon_mine, 938, 61);
	CopySpawnPoint(weapon_mine, 561, 62);
	CopySpawnPoint(ammo_missile, 732, 61);
	CopySpawnPoint(ammo_missile, 768, 62);
	CopySpawnPoint(weapon_bazooka, 751, 61);
	CopySpawnPoint(upgrade_rifle, 84, 258);
	CopySpawnPoint(upgrade_laser, 391, 179);
	CopySpawnPoint(upgrade_slime, 105, 401);
	CopySpawnPoint(ammo_grenade, 137, 464);
	CopySpawnPoint(ammo_grenade, 124, 464);
	CopySpawnPoint(weapon_grenade, 113, 463);
	CopySpawnPoint(ammo_gasoline, 61, 112);
	CopySpawnPoint(ammo_gasoline, 48, 112);
	CopySpawnPoint(weapon_flame, 35, 112);
	CopySpawnPoint(ammo_standard, 116, 149);
	CopySpawnPoint(ammo_standard, 133, 149);
	CopySpawnPoint(weapon_pumpgun, 148, 148);
	CopySpawnPoint(ammo_energy, 63, 322);
	CopySpawnPoint(ammo_energy, 78, 322);
	CopySpawnPoint(weapon_energy, 93, 322);
	
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
	weapon_minigun->RemoveObject();
	weapon_grenade->RemoveObject();
	weapon_flame->RemoveObject();
	weapon_bazooka->RemoveObject();
	weapon_energy->RemoveObject();
	weapon_mine->RemoveObject();
	
	item_armor->RemoveObject();
	item_novodekan->RemoveObject();
}


func CreateLights()
{
	CreateObject(BLGH, 576, 105, NO_OWNER)->TurnOn();
	CreateObject(BLGH, 926, 105, NO_OWNER)->TurnOn();
	CreateObject(BLGH, 1300, 375, NO_OWNER)->TurnOn();
	CreateObject(BLGH, 201, 375, NO_OWNER)->TurnOn();
	CreateObject(FLGH, 136, 390, NO_OWNER)->SetRotation(-10)->GetLight()->TurnOn();
	CreateObject(FLGH, 1364, 390, NO_OWNER)->SetRotation(+10)->GetLight()->TurnOn();
	CreateObject(FLGH, 893, 174, NO_OWNER)->SetRotation(-90)->GetLight()->TurnOn();
	CreateObject(FLGH, 609, 174, NO_OWNER)->SetRotation(+90)->GetLight()->TurnOn();
	CreateObject(CLGH, 749, 420, NO_OWNER)->TurnOn();
	CreateObject(CLGH, 674, 338, NO_OWNER)->TurnOn();
	CreateObject(CLGH, 823, 338, NO_OWNER)->TurnOn();
	CreateObject(CLGH, 65, 141, NO_OWNER)->TurnOn();
	CreateObject(CLGH, 1435, 141, NO_OWNER)->TurnOn();
}


func CreateWaypoints()
{
	var spec1, spec2;
	var wp1, wp5, wp16;

	for (var i = 0; i < 2; i++)
	{
		var dir;
		if (i == 0)
		{
			dir = 1;
		}
		else
		{
			dir = -1;
		}
		
		if (i == 0)
		{
			wp1 = CreateWP(1500 * i + dir * 750, 480);
			wp5 = CreateWP(1500 * i + dir * 750, 60);
			wp16 = CreateWP(1500 * i + dir * 750, 387);
			wp1->AddPath(wp16, Path_MoveTo, -1);
		}
		var wp2 = CreateWP(1500 * i + dir * 725, 517);
		var wp3 = CreateWP(1500 * i + dir * 661, 518);
		var wp4 = CreateWP(1500 * i + dir * 728, 178);
		var wp6 = CreateWP(1500 * i + dir * 66, 318);
		var wp7 = CreateWP(1500 * i + dir * 127, 294);
		var wp8 = CreateWP(1500 * i + dir * 178, 313);
		var wp9 = CreateWP(1500 * i + dir * 572, 175);
		var wp10 = CreateWP(1500 * i + dir * 200, 177);
		var wp11 = CreateWP(1500 * i + dir * 65, 454);
		var wp12 = CreateWP(1500 * i + dir * 62, 525);
		var wp13 = CreateWP(1500 * i + dir * 159, 517);
		var wp14 = CreateWP(1500 * i + dir * 625, 55);
		var wp15 = CreateWP(1500 * i + dir * 510, 398);
		var wp17 = CreateWP(1500 * i + dir * 669, 301);
		var wp18 = CreateWP(1500 * i + dir * 576, 398);
		var wp19 = CreateWP(1500 * i + dir * 661, 387);
		var wp20 = CreateWP(1500 * i + dir * 61, 179);
		wp2->AddPath(wp3, Path_MoveTo);
		wp2->AddPath(wp1, Path_Jump);
		wp3->AddPath(wp19, Path_MoveTo);
		wp3->AddPath(wp2, Path_MoveTo);
		wp4->AddPath(wp4, Path_Jump);
		wp4->AddPath(wp14, Path_Jump);
		wp4->AddPath(wp9, Path_Backflip, 0, 0, 0, true);
		wp4->AddPath(wp16, Path_MoveTo);
		wp5->AddPath(wp14, Path_MoveTo);
		wp6->AddPath(wp7, Path_MoveTo);
		wp6->AddPath(wp11, Path_MoveTo);
		wp6->AddPath(wp20, Path_MoveTo);
		wp7->AddPath(wp6, Path_MoveTo);
		wp7->AddPath(wp8, Path_MoveTo);
		wp7->AddPath(wp15, Path_Jump);
		wp8->AddPath(wp9, Path_MoveTo);
		wp9->AddPath(wp10, Path_Lift);
		wp9->AddPath(wp16, Path_MoveTo);
		wp10->AddPath(wp9, Path_Lift);
		wp10->AddPath(wp20, Path_MoveTo);
		wp11->AddPath(wp6, Path_MoveTo);
		wp11->AddPath(wp12, Path_MoveTo);
		wp11->AddPath(wp15, Path_MoveTo);
		wp12->AddPath(wp11, Path_MoveTo);
		wp12->AddPath(wp13, Path_MoveTo);
		wp13->AddPath(wp14, Path_MoveTo);
		wp14->AddPath(wp15, Path_MoveTo);
		wp14->AddPath(wp16, Path_MoveTo);
		wp14->AddPath(wp5, Path_MoveTo);
		wp14->AddPath(wp4, Path_MoveTo);
		wp15->AddPath(wp15, Path_MoveTo);
		wp15->AddPath(wp15, Path_MoveTo);
		wp15->AddPath(wp18, Path_MoveTo);
		wp15->AddPath(wp11, Path_MoveTo);
		wp16->AddPath(wp17, Path_Jump);
		wp16->AddPath(wp19, Path_MoveTo);
		wp17->AddPath(wp9, Path_MoveTo);
		wp18->AddPath(wp19, Path_Jump);
		wp18->AddPath(wp15, Path_MoveTo);
		wp19->AddPath(wp16, Path_MoveTo);
		wp19->AddPath(wp18, Path_Jump);
		wp19->AddPath(wp3, Path_MoveTo);
		wp20->AddPath(wp10, Path_MoveTo);
		wp20->AddPath(wp6, Path_MoveTo);
		if (i == 0)
		{
			spec1 = wp2;
			spec2 = wp4;
		}
		else
		{
			wp2->AddPath(spec1, Path_MoveTo, 0, 0, 0, true);
			wp4->AddPath(spec2, Path_MoveTo, 0, 0, 0, true);
		}
	}
}

func RelaunchLocations()
{
	return [{x = 65, y = 320, team = 1},
	    	{x = 1435, y = 320, team = 2}];
}
