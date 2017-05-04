//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Space

#include Library_DefaultScript

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Default initialization

func Initialize()
{
	SetGoal(SCENPAR_HAZARD_GOAL);

	_inherited(...);
	
	CreateLadders();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Deco

func CreateBackground()
{
	// sun
	var s2 = CreateObjectAbove(SUN_, LandscapeWidth() / 3, LandscapeHeight() / 2, NO_OWNER);
	var s1 = CreateObjectAbove(SUN_, LandscapeWidth() / 3, LandscapeHeight() / 2, NO_OWNER);
	
	s1->SetClrModulation(RGBa(255, 100, 0, 255));
	s2->SetObjectBlitMode(1);
	s2->SetClrModulation(RGBa(255, 255, 0, 255));
	s2->SetRotationSpeed(12);
	s2->SetGrowPos(13000);
	
	// sky
	SetSky("Stars");
	SetSkyParallax(30, 30);
}

func CreateDeco()
{
	// Deko
	CreateObjectAbove(SCR3, 1020, 555, NO_OWNER)->SetClrModulation(RGB(255, 255, 0));
	CreateObjectAbove(SCR3, 480, 555, NO_OWNER)->SetClrModulation(RGB(128, 0, 128));
	// Jumppads
	CreateObjectAbove(JMPD, 67, 730, NO_OWNER)->Set(67, 5);
	CreateObjectAbove(JMPD, 1433, 730, NO_OWNER)->Set(67, -5);
	CreateObjectAbove(JMPD, 250, 370, NO_OWNER)->Set(58, 25);
	CreateObjectAbove(JMPD, 1250, 370, NO_OWNER)->Set(58, -25);
	CreateObjectAbove(JMPD, 460, 180, NO_OWNER)->Set(65, -45);
	CreateObjectAbove(JMPD, 1040, 180, NO_OWNER)->Set(65, 45);
	CreateObjectAbove(JMPD, 510, 390, NO_OWNER)->Set(58, 25, 90);
	CreateObjectAbove(JMPD, 990, 390, NO_OWNER)->Set(58, -25, -90);
	
	// Alarm-lights
	
	CreateObjectAbove(ALGH, 1022, 199, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 1022, 538, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 1416, 378, NO_OWNER)->SetR(180);
	
	CreateObjectAbove(ALGH, 478, 199, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 478, 538, NO_OWNER)->SetR(180);
	CreateObjectAbove(ALGH, 84, 378, NO_OWNER)->SetR(180);
	
	// Lights
	CreateObjectAbove(BLGH, 1385, 628, NO_OWNER);
	CreateObjectAbove(BLGH, 1020, 374, NO_OWNER);
	CreateObjectAbove(CLGH, 1162, 641, NO_OWNER);
	CreateObjectAbove(CLGH, 1262, 434, NO_OWNER);
	CreateObjectAbove(FLGH, 1351, 508, NO_OWNER)->SetRotation(30);
	CreateObjectAbove(FLGH, 995, 518, NO_OWNER)->SetRotation(-50);
	CreateObjectAbove(FLGH, 991, 241, NO_OWNER)->SetRotation(50, 180);
	
	CreateObjectAbove(BLGH, 115, 628, NO_OWNER);
	CreateObjectAbove(BLGH, 480, 374, NO_OWNER);
	CreateObjectAbove(CLGH, 338, 641, NO_OWNER);
	CreateObjectAbove(CLGH, 238, 434, NO_OWNER);
	CreateObjectAbove(FLGH, 149, 508, NO_OWNER)->SetRotation(-30);
	CreateObjectAbove(FLGH, 505, 518, NO_OWNER)->SetRotation(50);
	CreateObjectAbove(FLGH, 509, 241, NO_OWNER)->SetRotation(-50, 180);
	
	// Vents
	CreateObjectAbove(VENT, 120, 700, NO_OWNER)->DoCon(-70);
	CreateObjectAbove(VENT, 1380, 700, NO_OWNER)->DoCon(-70);
}

func CreateLadders()
{
	// Struktur
	// TODO CreateObjectAbove(LADR, 190, 500, NO_OWNER)->Set(11);
	// TODO CreateObjectAbove(LADR, 1310, 500, NO_OWNER)->Set(11);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Equipment

func CreateSpawnPoints()
{
	// configure spawn points
	var config = GetSpawnPointTemplates();

	// place spawn points
	CopySpawnPoint(config.weapon_pumpgun, 100, 350);
	CopySpawnPoint(config.ammo_standard, 110, 350);
	CopySpawnPoint(config.weapon_pumpgun, 1400, 350);
	CopySpawnPoint(config.ammo_standard, 1390, 350);
	CopySpawnPoint(config.upgrade_laser, 150, 500);
	CopySpawnPoint(config.upgrade_laser, 1350, 500);
	CopySpawnPoint(config.ammo_energy, 160, 500);
	CopySpawnPoint(config.ammo_energy, 1340, 500);
	CopySpawnPoint(config.ammo_standard, 1390, 350);
	CopySpawnPoint(config.item_jetpack, 750, 350);
	CopySpawnPoint(config.ammo_gasoline, 735, 350);
	CopySpawnPoint(config.ammo_gasoline, 765, 350);
	CopySpawnPoint(config.ammo_missile, 670, 90);
	CopySpawnPoint(config.ammo_missile, 830, 90);
	CopySpawnPoint(config.weapon_bazooka, 750, 20);
	CopySpawnPoint(config.weapon_grenade, 90, 110);
	CopySpawnPoint(config.weapon_grenade, 1410, 110);
	CopySpawnPoint(config.ammo_grenade, 110, 110);
	CopySpawnPoint(config.ammo_grenade, 1390, 110);
	CopySpawnPoint(config.ammo_grenade, 660, 270);
	CopySpawnPoint(config.ammo_grenade, 840, 430);
	CopySpawnPoint(config.ammo_standard, 660, 430);
	CopySpawnPoint(config.ammo_standard, 840, 270);
	CopySpawnPoint(config.upgrade_rifle, 480, 550);
	CopySpawnPoint(config.upgrade_rifle, 1020, 550);
	CopySpawnPoint(config.weapon_motegun, 460, 710);
	CopySpawnPoint(config.weapon_motegun, 1040, 710);
	CopySpawnPoint(config.ammo_energy, 620, 710);
	CopySpawnPoint(config.ammo_energy, 880, 710);
	CopySpawnPoint(config.item_armor, 90, 720);
	CopySpawnPoint(config.item_armor, 1410, 720);
	CopySpawnPoint(config.weapon_energy, 460, 210);
	CopySpawnPoint(config.weapon_energy, 1040, 210);
	CopySpawnPoint(config.ammo_energy, 500, 210);
	CopySpawnPoint(config.ammo_energy, 1000, 210);
	CopySpawnPoint(config.weapon_mine, 750, 530);
	
	// remove template spawn points
	RemoveSpawnPointTemplates(config);
}

/* Regelwaehler */

//func ChooserFinished()
//{
//	Arena_ChooserFinished();
//	
//	var wp = FindObject(WPCH);
//	if (wp)
//	{
//		// und begrenzte Waren...
//		wp->RemoveWare();
//		wp->AddWare(weapon_pistol); // Pistole
//		wp->AddWare(weapon_energy); // Energiegewehr
//		wp->AddWare(weapon_grenade); // Granatenwerfer
//		wp->AddWare(weapon_motegun); // Partikelkanone
//		wp->AddWare(upgrade_laser); // Laser
//		wp->AddWare(FLSH); // Taschenlampe
//		wp->AddWare(item_jetpack); // Jetpack
//		wp->AddWare(HSHD); // Schild
//		wp->AddWare(DRSU); // Drone
//		wp->AddWare(LMIN); // Lasermine
//		wp->AddWare(SMIN); // Schwarmmine
//		//wp->SortWare();
//	}
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AI

func CreateWaypoints()
{
	for (var i = 0; i < 2; i++)
	{
		if (!i)
			var dir = 1;
		else
			dir = -1;
		
		var wp1 = CreateWP(1500 * i + dir * 90, 350);
		var wp2 = CreateWP(1500 * i + dir * 200, 410);
		var wp3 = CreateWP(1500 * i + dir * 30, 325);
		var wp4 = CreateWP(1500 * i + dir * 240, 360);
		var wp5 = CreateWP(1500 * i + dir * 90, 410);
		var wp6 = CreateWP(1500 * i + dir * 170, 500);
		var wp7 = CreateWP(1500 * i + dir * 260, 500);
		var wp8 = CreateWP(1500 * i + dir * 340, 610);
		var wp9 = CreateWP(1500 * i + dir * 280, 670);
		var wp10 = CreateWP(1500 * i + dir * 130, 720);
		var wp11 = CreateWP(1500 * i + dir * 70, 720);
		var wp12 = CreateWP(1500 * i + dir * 415, 550);
		var wp13 = CreateWP(1500 * i + dir * 315, 270);
		var wp14 = CreateWP(1500 * i + dir * 405, 210);
		var wp15 = CreateWP(1500 * i + dir * 455, 170);
		var wp16 = CreateWP(1500 * i + dir * 145, 110);
		var wp17 = CreateWP(1500 * i + dir * 20, 110);
		var wp18 = CreateWP(1500 * i + dir * 560, 210);
		var wp19 = CreateWP(1500 * i + dir * 670, 95);
		var wp20 = CreateWP(1500 * i + dir * 680, 270);
		var wp21 = CreateWP(1500 * i + dir * 635, 430);
		var wp22 = CreateWP(1500 * i + dir * 670, 430);
		var wp23 = CreateWP(1500 * i + dir * 515, 510);
		var wp24 = CreateWP(1500 * i + dir * 535, 555);
		var wp25 = CreateWP(1500 * i + dir * 460, 720);
		var wp26 = CreateWP(1500 * i + dir * 640, 575);
		var wp27 = CreateWP(1500 * i + dir * 620, 720);
		
		if (!i)
		{
			var wp28 = CreateWP(750, 355);
			var wp29 = CreateWP(750, 655);
			var spec1 = wp18;
			var spec2 = wp19;
			var spec3 = wp20;
			var spec4 = wp26;
			var jtpk1 = Jetpack_Right;
			var jtpk2 = Jetpack_UpLeft;
		}
		else
		{
			var jtpk1 = Jetpack_Left;
			var jtpk2 = Jetpack_UpRight;
		}
		
		wp1->AddPath(wp2);
		wp1->AddPath(wp3);
		wp1->AddPath(wp4, Path_Jump, 1 * dir);
		wp2->AddPath(wp1, Path_Jump, -1 * dir);
		wp2->AddPath(wp4, Path_Jump, 1 * dir);
		wp2->AddPath(wp5);
		wp2->AddPath(wp6, Path_MoveTo);
		wp2->AddPath(wp12);
		wp3->AddPath(wp1);
		wp3->AddPath(wp5);
		wp4->AddPath(wp14);
		wp5->AddPath(wp2);
		wp5->AddPath(wp3);
		wp6->AddPath(wp2, Path_Jump);
		wp6->AddPath(wp7);
		wp6->AddPath(wp10);
		wp7->AddPath(wp6);
		wp7->AddPath(wp8);
		wp7->AddPath(wp12, Path_Backflip);
		wp8->AddPath(wp7, Path_Jump, -1 * dir);
		wp8->AddPath(wp12, Path_Jump, 1 * dir);
		wp8->AddPath(wp25);
		wp9->AddPath(wp8, Path_Jump, 1 * dir);
		wp9->AddPath(wp10, Path_Jump, -1 * dir);
		wp9->AddPath(wp25);
		wp10->AddPath(wp9, Path_Jump, 1 * dir);
		wp10->AddPath(wp11);
		wp11->AddPath(wp6);
		wp12->AddPath(wp2, Path_Jump, -1 * dir, 45, jtpk2); // Jetpack!
		wp12->AddPath(wp8);
		wp12->AddPath(wp24);
		wp13->AddPath(wp2);
		wp13->AddPath(wp14, Path_Jump, 1 * dir);
		wp14->AddPath(wp3, Path_Backflip, -1 * dir);
		wp14->AddPath(wp13);
		wp14->AddPath(wp15, Path_Jump, 1 * dir);
		wp14->AddPath(wp18);
		wp15->AddPath(wp16);
		wp16->AddPath(wp8);
		wp16->AddPath(wp14, 0, 1 * dir, 50, jtpk1); // Jetpack
		wp16->AddPath(wp17);
		wp17->AddPath(wp16);
		wp18->AddPath(wp14);
		wp18->AddPath(wp19, Path_Jump, 1 * dir);
		wp18->AddPath(wp20);
		//wp18
		wp19->AddPath(wp18);
		//wp19-> AddPath(wp, Path_Jump, 1*dir);
		wp20->AddPath(wp18, Path_Jump, -1 * dir);
		wp20->AddPath(wp28);
		//wp20
		wp21->AddPath(wp20, Path_Jump, -1 * dir);
		wp21->AddPath(wp22);
		wp21->AddPath(wp24);
		wp22->AddPath(wp21);
		wp22->AddPath(wp28, Path_Jump, 1 * dir);
		wp23->AddPath(wp21, Path_Jump, 1 * dir);
		wp23->AddPath(wp26);
		wp24->AddPath(wp12);
		wp24->AddPath(wp23);
		wp24->AddPath(wp26);
		wp25->AddPath(wp8, Path_Jump, -1 * dir);
		wp25->AddPath(wp9, Path_Jump, -1 * dir);
		wp25->AddPath(wp29, Path_Jump, 1 * dir, 20, jtpk1); // Jetpack
		wp25->AddPath(wp27, Path_Jump, 1 * dir);
		wp26->AddPath(wp23, Path_Jump, -1 * dir);
		wp26->AddPath(wp24);
		wp26->AddPath(wp29);
		wp27->AddPath(wp25, Path_Jump, -1 * dir);
		wp27->AddPath(wp29, Path_Jump, 1 * dir);
		wp28->AddPath(wp20, Path_Jump, 1 * dir);
		wp28->AddPath(wp22);
		wp29->AddPath(wp25, Path_Backflip, -1 * dir);
		wp29->AddPath(wp26, Path_Jump, -1 * dir);
		wp29->AddPath(wp27);
		if (i)
		{
			spec1->AddPath(wp20, Path_Backflip, 1);
			spec2->AddPath(wp19, Path_Jump, 1);
			spec3->AddPath(wp18, Path_Jump, 1, 20, Jetpack_Right); // Jetpack
			spec3->AddPath(wp20, Path_Jump, 1);
			spec4->AddPath(wp26, Path_Backflip, 1);
			wp18->AddPath(spec3, Path_Backflip, -1);
			wp19->AddPath(spec2, Path_Jump, -1);
			wp20->AddPath(spec1, Path_Jump, -1, 20, Jetpack_Left); // Jetpack
			wp20->AddPath(spec3, Path_Jump, -1);
			wp26->AddPath(spec4, Path_Backflip, -1);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Relaunches

func RelaunchLocations()
{
	return 
	[
		{x =   80, y = 350, team = 1},
		{x = 1420, y = 350, team = 2}
	];
}
