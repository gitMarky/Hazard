// Intro sequence for the tutorial

#appendto Sequence

func Tutorial_Start()
{
	GetCrew()->SetCommand("MoveTo", nil, screen->GetX() - 5, GetCrew()->GetY());
	SetMaxPlayer(2);
	CreateScriptPlayer("$Drones$", RGB(1, 1, 1), 2, 15);
	return ScheduleNext(130);
}


func Tutorial_1()
{
	var view_range = Abs(screen->GetY() - GetCrew()->GetY()) + 250;
	SetPlayerZoomByViewRange(0, view_range, view_range, PLRZOOM_Set);
	
	SetHostility(0, 1, true, true);
	screen->SetAction("Noise");
	if (door2)
		door2->Close();
	return ScheduleNext(50);
}


func Tutorial_2()
{
	screen->SetAction("On");
	return ScheduleNext(20);
}

func Tutorial_3()
{
	screen_dlg->Interact(GetCrew());
	GetCrew()->SetCrewEnabled(true);
	SetCursor(0, GetCrew(), true);
	return ScheduleNext(1);
}

func Tutorial_4()
{
	if (IsValueInArray(scenario_progress, TUTORIAL_FINISHED_INTRO))
	{
		SetPlayerZoomByViewRange(0, nil, nil, PLRZOOM_Set);
		screen->SetAction("Noise");
		return ScheduleNext(50);
	}
	else
	{
		return ScheduleSame(5);
	}
}


func Tutorial_5()
{
	screen->SetAction("Off");
	return ScheduleNext(10);
}


func Tutorial_6()
{
	if (IsValueInArray(scenario_progress, TUTORIAL_HAS_PISTOL))
	{
		if (door1)
			door1.lock = false;
		CreateSpawnPoint(850, 590)->SpawnItem(STAP)->StartSpawning();
		return ScheduleNext(10);
	}
	else
	{
		return ScheduleSame(10);
	}
}

func Tutorial_7()
{
	if (GetCrew()->GetX() > 750 && GetCrew()->GetY() < 600)
	{
		StartDialogue("CommanderAmmo");
		
		if (door1)
		{
			door1->Close();
			door1.lock = true;
		}
		
		return ScheduleNext(10);
	}
	else
	{
		return ScheduleSame(10);
	}
}

func Tutorial_8()
{
	var collected_ammo = !FindObject(Find_ID(STAP));
	
	if (collected_ammo)
	{
		StartDialogue("CommanderDrone1");
		
		drone = CreateDrone(950, 545);
		drone->StartMoving(0, -30, 0, 20, 0, 0, 100);
		return ScheduleNext(10);
	}
	else
	{
		return ScheduleSame(10);
	}
}


func Tutorial_9()
{
	return WaitUntilDroneDown();
}

func Tutorial_10()
{
	StartDialogue("CommanderDrone2");
	drone = CreateDrone(990, 472);
	drone->StartMoving(-15, 0, 55, 0);
	return ScheduleNext(10);
}

func Tutorial_11()
{
	return WaitUntilDroneDown();
}

func Tutorial_12()
{
	StartDialogue("CommanderTeleporter");
	
	if (tele)
		tele->Activate();
	RemoveAllSpawnpoints();

	CreateSpawnPoint(1580, 960)->SpawnItem(GRAP)->StartSpawning();

	return ScheduleNext(10);
}

func Tutorial_13()
{
	if (GetCrew()->GetX() > 1400)
	{
		StartDialogue("CommanderGLauncher");
		if (tele2)
			tele2->Deactivate();
		return ScheduleNext(30);
	}
	else
	{
		return ScheduleSame(10);
	}
}


func Tutorial_14()
{
	var grenade_ammo = FindObject(Find_ID(GRAP));
	var has_launcher = GetCrew()->FindContents(Weapon_GrenadeLauncher);
	if (grenade_ammo || !has_launcher)
	{
		return ScheduleSame(10);
	}
	else
	{
		StartDialogue("CommanderDrone3");
		
		drone = CreateDrone(1750, 950)->StartMoving(0, 1, 0, 3);
		return ScheduleNext(10);
	}
}

func Tutorial_15()
{
	return WaitUntilDroneDown();
}

func Tutorial_16()
{
	StartDialogue("CommanderDrone4");
	
	var launcher = FindObject(Find_ID(Weapon_GrenadeLauncher));
	launcher->ChangeFiremode(launcher.firemode_fragmentation);

	drone = CreateDrone(1400, 950);
	drone->StartMoving(0, 1, 0, 3);
	drone->SetDir(DIR_Right);
	drone.drop = Upgrade_Laser;
	return ScheduleNext(10);
}

func Tutorial_17()
{
	return WaitUntilDroneDown();
}

func Tutorial_18()
{
	StartDialogue("CommanderUpgrade");
	RemoveAllSpawnpoints();
	return ScheduleNext(10);
}

func Tutorial_19()
{
	var laser = FindObject(Find_ID(Upgrade_Laser));
	if (laser)
	{
		return ScheduleSame(10);
	}
	else
	{
		StartDialogue("CommanderFiremode");
	
		CreateSpawnPoint(850, 590)->SpawnItem(Gear_Jetpack)->StartSpawning();
		CreateSpawnPoint(900, 590)->SpawnItem(ENAP)->StartSpawning();
		CreateObject(MEDI, 925, 600);

		tele2->Activate();
		
		return ScheduleNext(40);
	}
}

func Tutorial_20()
{
	var jetpack = GetCrew()->FindContents(Gear_Jetpack);
	
	if (!jetpack)
	{
		return ScheduleSame(10);
	}
	else
	{
		StartDialogue("CommanderJetpack1");
	
		tele->Deactivate();
		return ScheduleNext(30);
	}
}

func Tutorial_21()
{
	var jetpack = GetCrew()->FindContents(Gear_Jetpack);
	if (jetpack)
	{
		return ScheduleSame(10);
	}
	else
	{
		StartDialogue("CommanderJetpack2");

		return ScheduleNext(20);
	}
}

func Tutorial_22()
{
	if (GetCrew()->GetX() < 1070 && GetCrew()->GetY() > 450)
	{
		return ScheduleSame(10);
	}
	else
	{
		StartDialogue("CommanderDrone5");

		//TODO: Muni wegnehmen *hidez*
		//DoAmmo(STAM, -GetAmmo(STAM, GetCrew()), GetCrew());
		//DoAmmo(GRAM, -GetAmmo(GRAM, GetCrew()), GetCrew());
		//DoAmmo(GRAM, -GetAmmo(GRAM, FindObject(GLWP)), FindObject(GLWP));

		CreateDrone(1180, 450)->StartMoving(0, 1, 0, 25);
		CreateDrone(1250, 450)->StartMoving(0, -1, 0, 25);
		CreateDrone(1320, 450)->StartMoving(0, 1, 0, 25);

		drone = CreateDrone(1390, 450);
		drone->StartMoving(0, -1, 0, 25);
		drone.drop = Upgrade_Laser;
		
		return ScheduleNext(10);
	}
}

func Tutorial_23()
{
	return WaitUntilDroneDown();
}

func Tutorial_24()
{
	StartDialogue("CommanderDrone6");

	drone = CreateDrone(1250, 350);
	drone->StartMoving(1, 1, 50, 20, 25, 0);
	drone.drop = Weapon_Bazooka;
	FindObject(Find_ID(Target))->SetGraphics(nil, Weapon_Bazooka);

	// TODO: remove old weapons
	FindObject(Find_ID(Weapon_Pistol))->RemoveObject();
	
	// TODO -> Remove this again / replace with just the upgrade
	var launcher = FindObject(Find_ID(Weapon_GrenadeLauncher));
	launcher->ChangeFiremode(launcher.firemode_emp);
	//launcher->Upgrade(Upgrade_Laser);

	CreateSpawnPoint(1065, 450)->SpawnItem(ENAP)->StartSpawning();

	return ScheduleNext(10);
}

func Tutorial_25()
{
	var laser = FindObject(Find_ID(Upgrade_Laser));
	if (laser)
	{
		ScheduleSame(10);
	}
	else
	{
		StartDialogue("CommanderHoming");
		
		FindObject(Find_ID(Weapon_GrenadeLauncher))->RemoveObject();
		
		CreateSpawnPoint(1375, 590)->SpawnItem(MIAP)->StartSpawning();

		drone = CreateDrone(1645, 675);
		// TODO: hack for homing missile *cough*
		// not necessary I'd say, the missile attacks projectile targets after all
		// drone->SetCategory(C4D_Living);
		// drone->SetAlive(true);
		return ScheduleNext(10);
	}
}

func Tutorial_26()
{
	return WaitUntilDroneDown();
}

func Tutorial_27()
{
	StartDialogue("CommanderWarehouse");
	
	// TODO FindObject(Find_ID(MIAP))->Contained()->RemoveObject();
	RemoveAllSpawnpoints();
	FindObject(Find_ID(Weapon_Bazooka))->RemoveObject();

	CreateSpawnPoint(1085, 450)->SpawnItem(Weapon_Motegun)->StartSpawning();

	return ScheduleNext(10);
}


func Tutorial_28()
{
	var motegun = GetCrew()->FindContents(Weapon_Motegun);

	if (!motegun)
	{
		return ScheduleSame(10);
	}
	else
	{
		StartDialogue("CommanderMoteGun");

		for (var x = 0; x < 10; x++)
		{
			CreateDrone(1180 + 30 * x, 450)->StartMoving(1, 1, 15, 15, 7);

			if (x < 8)
			{
				CreateDrone(980 - 30 * x, 450)->StartMoving(-1, -1, 15, 15, 0, 7);
			}
		}
		
		return ScheduleNext(10);
	}
}

func Tutorial_29()
{
	return WaitUntilDroneDown();
}	

func Tutorial_30()
{
	StartDialogue("CommanderMinigun");
	
	RemoveAllSpawnpoints();
	FindObject(Find_ID(Weapon_Motegun))->RemoveObject();

	//CreateSpawnPoint(1085, 450)->SpawnItem(Weapon_Minigun)->StartSpawning();

	var mg = GetCrew()->CreateContents(Weapon_Minigun);
	// CreateObjectAbove(Weapon_Minigun, GetCrew()->GetX(), GetCrew()->GetDefBottom());

	//TODO: this makes the minigun load 500 bullets, instead of the usual amount
	// we do not need such an effect, it is sufficient to set the ammo to unlimited :p
	//AddEffect("MinigunMegarammoBonus", GetCursor(), 190, 0, GetCursor());
	//TODO: AddSpawnEffect(mg);
	//TODO: vieeeel ammo.
	//DoAmmo(STAM, 500, mg);
	//DoAmmo(STAM, 300, GetCrew());
	return ScheduleNext(10);
}

func Tutorial_31()
{
	var x, y;
	for (x = 0; x < 5; x++)
		for (y = 0; y < 5; y++)
			CreateDrone(850 + x * 20, 400 + y * 20)->SetDir(1);

	for (x = 0; x < 5; x++)
		for (y = 0; y < 5; y++)
			CreateDrone(1230 + x * 20, 400 + y * 20);

	for (x = 0; x < 24; x++)
		for (y = 0; y < 5; y++)
			CreateObject(Target_Drone, 850 + x * 20, 300 + y * 20)->SetDir(x < 12);

	return ScheduleNext(10);
}

func Tutorial_32()
{
	var x, y;

	return ScheduleNext(10);
}

func Tutorial_33()
{
	var x, y;

	return ScheduleNext(10);
}

func Tutorial_34()
{
	return WaitUntilDroneDown();
}

func Tutorial_35()
{	
	StartDialogue("CommanderEnd");
	return ScheduleNext(10);
}

func Tutorial_36()
{
	if (IsValueInArray(scenario_progress, TUTORIAL_FINISHED))
	{
		Sound("Applause");
		GetCrew()->SetCrewEnabled(true);
		return ScheduleNext(60);
	}
	else
	{
		return ScheduleNext(10);
	}
}

func Tutorial_37()
{
	return Stop();
}


func Tutorial_Stop()
{
	GetCrew()->DoCrewExp(100);
	EliminatePlayer(1);
	GameOver();
	return true;
}


func StartDialogue(string name)
{
	if (screen_dlg)
		screen_dlg->RemoveObject();
	screen_dlg = screen->SetDialogue(name, false);
	screen_dlg->Interact(GetCrew());
	
	GetCrew()->SetComDir(COMD_Stop);
	GetCrew()->SetXDir();
}

func WaitUntilDroneDown()
{
	if (FindObject(Find_ID(Target)))
		return ScheduleSame(10);
	return ScheduleNext(30);
}

func RemoveAllSpawnpoints()
{
	RemoveAll(Find_ID(SpawnPoint));
}

func CreateDrone(int x, int y)
{
	var drone = CreateObject(Target_Drone, x, y, NO_OWNER);
	drone->FadeIn();
	return drone;
}
