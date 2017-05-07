//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Face

#include Library_DefaultScript

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Default initialization

func Initialize()
{
	SetGoal(SCENPAR_HAZARD_GOAL);
	SetWinScore(SCENPAR_HAZARD_SCORE);

	_inherited(...);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Deco

func CreateBackground()
{
	SetSkyParallax(0, 150, 20);
}

func CreateDeco()
{
	// objects
	CreateObjectAbove(FLGH, 1335, 316, NO_OWNER)->SetRotation(0, 180);
	CreateObjectAbove(FLGH, 165, 316, NO_OWNER)->SetRotation(0, 180);
	// TODO CreateObjectAbove(LADR, 1335, 450, NO_OWNER)->Set(13);
	// TODO CreateObjectAbove(LADR, 165, 450, NO_OWNER)->Set(13);
	var liftp = CreateObjectAbove(LFTP, 805, 274, NO_OWNER);
	liftp->DisableVertical();
	liftp->ContactLeft();
	liftp = CreateObjectAbove(LFTP, 695, 274, NO_OWNER);
	liftp->DisableVertical();
	liftp->ContactRight();

	CreateObjectAbove(CLGH, 1237, 193, NO_OWNER);
	CreateObjectAbove(CLGH, 263, 193, NO_OWNER);
	CreateObjectAbove(BLGH, 750, 450, NO_OWNER);
	CreateObjectAbove(BLGH, 750, 320, NO_OWNER);
	CreateObjectAbove(HSGN, 750, 375, NO_OWNER)->SetCon(75);
	CreateObjectAbove(FENC, 1261, 260, NO_OWNER);
	CreateObjectAbove(FENC, 1201, 260, NO_OWNER);
	CreateObjectAbove(FENC, 239, 260, NO_OWNER);
	CreateObjectAbove(FENC, 299, 260, NO_OWNER);
	CreateObjectAbove(ENGT, 1306, 385, NO_OWNER)->SetCon(50);
	CreateObjectAbove(ENGT, 194, 385, NO_OWNER)->SetCon(50);
	// Warps
	/* TODO
	CreateObjectAbove(AWRP, 260, 450, NO_OWNER)->Set(210, 250);
	CreateObjectAbove(AWRP, 170, 120, NO_OWNER)->Set(210, 250);
	CreateObjectAbove(AWRP, 170, 280, NO_OWNER)->Set(200, 490);
	CreateObjectAbove(AWRP, 170, 220, NO_OWNER)->Set(230, 90);
	CreateObjectAbove(AWRP, 110, 480, NO_OWNER)->Set(230, 90);
	
	CreateObjectAbove(AWRP, 1240, 450, NO_OWNER)->Set(1290, 250);
	CreateObjectAbove(AWRP, 1330, 120, NO_OWNER)->Set(1290, 250);
	CreateObjectAbove(AWRP, 1330, 280, NO_OWNER)->Set(1300, 490);
	CreateObjectAbove(AWRP, 1330, 220, NO_OWNER)->Set(1270, 90);
	CreateObjectAbove(AWRP, 1390, 480, NO_OWNER)->Set(1270, 90);
	*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Equipment

func CreateSpawnPoints()
{
	// configure spawn points
	var config = GetSpawnPointTemplates();

	// place spawn points
	CopySpawnPoint(config.weapon_grenade, 280, 610);
	CopySpawnPoint(config.ammo_grenade, 300, 610);
	CopySpawnPoint(config.weapon_energy, 240, 490);
	CopySpawnPoint(config.ammo_energy, 260, 490);
	CopySpawnPoint(config.ammo_standard, 220, 340);
	CopySpawnPoint(config.weapon_pumpgun, 240, 340);
	CopySpawnPoint(config.ammo_standard, 260, 340);
	CopySpawnPoint(config.weapon_bazooka, 300, 250);
	CopySpawnPoint(config.ammo_missile, 280, 250);
	CopySpawnPoint(config.weapon_motegun, 300, 80);
	CopySpawnPoint(config.ammo_energy, 280, 80);
	CopySpawnPoint(config.item_medipack, 110, 50);
	CopySpawnPoint(config.upgrade_rifle, 160, 50);
	CopySpawnPoint(config.weapon_mine, 360, 400);
	
	CopySpawnPoint(config.upgrade_laser, 750, 250);
	
	CopySpawnPoint(config.weapon_grenade, 1220, 610);
	CopySpawnPoint(config.ammo_grenade, 1200, 610);
	CopySpawnPoint(config.weapon_energy, 1260, 490);
	CopySpawnPoint(config.ammo_energy, 1240, 490);
	CopySpawnPoint(config.ammo_standard, 1280, 340);
	CopySpawnPoint(config.weapon_pumpgun, 1260, 340);
	CopySpawnPoint(config.ammo_standard, 1240, 340);
	CopySpawnPoint(config.weapon_bazooka, 1200, 250);
	CopySpawnPoint(config.ammo_missile, 1220, 250);
	CopySpawnPoint(config.weapon_motegun, 1200, 80);
	CopySpawnPoint(config.ammo_energy, 1220, 80);
	CopySpawnPoint(config.item_medipack, 1390, 50);
	CopySpawnPoint(config.upgrade_rifle, 1340, 50);
	CopySpawnPoint(config.weapon_mine, 1140, 400);
	
	CopySpawnPoint(config.weapon_chainsaw, 750, 417);
	CopySpawnPoint(config.ammo_gasoline, 750, 447);
	
	//TODO PlaceVehicleSpawnpoint(TANK, 105, 550);
	//TODO PlaceVehicleSpawnpoint(TANK, 1395, 550);
	
	// remove template spawn points
	RemoveSpawnPointTemplates(config);
}

/* Regelwaehler */

//public func ChooserFinished()
//{
//  Arena_ChooserFinished();
//
//  // Bei Waffenwahl werden alle Nicht-Munispawns entfernt
//  var wp = FindObject(WPCH);
//  if(wp)
//  {
//    // und begrenzte Waren...
//    wp->RemoveWare();
//    wp->AddWare(PIWP);  // Pistole
//    wp->AddWare(weapon_pumpgun);  // Pumpgun
//    wp->AddWare(weapon_grenade);  // Granatenwerfer
//    wp->AddWare(weapon_minigun);  // Minigun
//    wp->AddWare(weapon_motegun);  // Partikelkanone
//    wp->AddWare(weapon_bazooka);  // Bazooka
//    wp->AddWare(upgrade_laser);  // Laser
//    wp->AddWare(upgrade_rifle);  // Waffenteile
//    wp->AddWare(FLSH);  // Taschenlampe
//    wp->AddWare(weapon_mine);  // Lasermine
//    //wp->SortWare();
//  }
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AI

func CreateWaypoints()
{
	var spec1, spec2, dir;
	for (var i = 0; i < 2; i++)
	{
		if (!i)
		{
			dir = +1;
		}
		else
		{
			dir = -1;
		}
		
		var wp1 = CreateWP(1500 * i + dir * 344, 489);
		var wp2 = CreateWP(1500 * i + dir * 735, 248);
		var wp3 = CreateWP(1500 * i + dir * 400, 120);
		var wp4 = CreateWP(1500 * i + dir * 91, 49);
		var wp5 = CreateWP(1500 * i + dir * 177, 48);
		var wp6 = CreateWP(1500 * i + dir * 244, 89);
		var wp7 = CreateWP(1500 * i + dir * 320, 78);
		var wp8 = CreateWP(1500 * i + dir * 181, 103);
		var wp9 = CreateWP(1500 * i + dir * 181, 203);
		var wp10 = CreateWP(1500 * i + dir * 227, 251);
		var wp11 = CreateWP(1500 * i + dir * 318, 248);
		var wp12 = CreateWP(1500 * i + dir * 181, 264);
		var wp13 = CreateWP(1500 * i + dir * 273, 434);
		var wp14 = CreateWP(1500 * i + dir * 118, 447);
		var wp15 = CreateWP(1500 * i + dir * 341, 338);
		var wp16 = CreateWP(1500 * i + dir * 302, 339);
		var wp17 = CreateWP(1500 * i + dir * 186, 339);
		var wp18 = CreateWP(1500 * i + dir * 180, 490);
		var wp20 = CreateWP(1500 * i + dir * 707, 447);
		var wp21 = CreateWP(1500 * i + dir * 516, 529);
		var wp22 = CreateWP(1500 * i + dir * 290, 609);
		var wp23 = CreateWP(1500 * i + dir * 31, 489);
		
		wp1->AddPath(wp18);
		wp1->AddPath(wp16, Path_Jump);
		wp1->AddPath(wp21);
		wp2->AddPath(wp21);
		wp2->AddPath(wp11, Path_Lift);
		wp2->AddPath(wp1, 0, 0, 30);
		wp3->AddPath(wp20);
		wp3->AddPath(wp7);
		wp3->AddPath(wp2, Path_Jump, 0, 40);
		wp4->AddPath(wp5);
		wp5->AddPath(wp6);
		wp5->AddPath(wp4);
		wp6->AddPath(wp8);
		wp6->AddPath(wp7);
		wp6->AddPath(wp5, Path_Jump);
		wp7->AddPath(wp6);
		wp7->AddPath(wp3);
		wp8->AddPath(wp10);
		wp9->AddPath(wp6);
		wp10->AddPath(wp12);
		wp10->AddPath(wp9, Path_Jump);
		wp10->AddPath(wp11);
		wp11->AddPath(wp10);
		wp11->AddPath(wp21);
		wp11->AddPath(wp2, Path_Lift);
		wp12->AddPath(wp18);
		wp13->AddPath(wp10);
		wp14->AddPath(wp6);
		wp15->AddPath(wp16);
		wp15->AddPath(wp21);
		wp16->AddPath(wp1);
		wp16->AddPath(wp15);
		wp16->AddPath(wp17);
		wp17->AddPath(wp18);
		wp17->AddPath(wp16);
		wp18->AddPath(wp13);
		wp18->AddPath(wp17, Path_Jump);
		wp18->AddPath(wp1);
		wp20->AddPath(wp21);
		wp21->AddPath(wp22);
		wp21->AddPath(wp1);
		wp21->AddPath(wp20);
		wp22->AddPath(wp21);
		wp22->AddPath(wp23);
		wp23->AddPath(wp22);
		wp23->AddPath(wp14, Path_Backflip);
		
		if (!i)
		{
			spec1 = wp20;
			spec2 = wp2;
		}
		else
		{
			wp20->AddPath(spec1, Path_Jump, -1);
			spec1->AddPath(wp20, Path_Jump, +1);
			wp2->AddPath(spec2);
			spec2->AddPath(wp2);
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
		{x =   30, y = 480, team = 1},
		{x =   30, y =  25, team = 1},
		{x =   30, y =  25, team = 1},
		{x =   30, y =  25, team = 1},
		{x = 1470, y = 480, team = 2},
		{x = 1470, y =  25, team = 2},
		{x = 1470, y =  25, team = 2},
		{x = 1470, y =  25, team = 2}
	];
}
