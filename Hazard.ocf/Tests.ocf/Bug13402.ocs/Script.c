
protected func InitializePlayer(int player)
{
	// Set zoom and move player to the middle of the scenario.
	SetPlayerZoomByViewRange(player, LandscapeWidth(), nil, PLRZOOM_Direct);
	SetFoW(false, player);
	GetCrew(player)->SetPosition(120, 190);
	GetCrew(player)->MakeInvincible();
	
	// Add test control effect.
	LaunchTest(1);
	return true;
}


global func GetInfiniteAmmoSource(type)
{
	return AMMO_Source_Infinite;
}

global func Shoot(object weapon, object bot)
{
	weapon->ControlUseAltHolding(bot, +100, -100); // fire 45° angle upwards
}

/*-- Test helpers --*/

// override for the weapon: kills its user
global func Bug13402_OnRecoveryDie(object user, proplist firemode)
{
	Log("On Recovery - kill the weapon user");
	_inherited(user, firemode);
	
	if (user)
	{
		user->Kill();
	}
}


global func Bug13402_OnRecoveryDrop(object user, proplist firemode)
{
	Log("On Recovery - drop the weapon");
	_inherited(user, firemode);
	
	if (user)
	{
		this->Exit();
	}
}


global func Bug13402_Departure(object container)
{
	Log("Departure - print all effects that are active in the weapon");
	
	for (var i = 0; i < GetEffectCount(); ++i)
	{
		var active = GetEffect("*", this, i);
		Log(" - active: %v", active);
	}
	
	_inherited(container);
}

global func Bug13402_OnStartCooldown(object user, proplist firemode)
{
	Log("On start cooldown - weapon has cooldown, should finish the sound");
	Sound("Weapon::Minigun::MiniGun", nil, nil, nil, -1);
	_inherited(user, firemode);
}

global func Bug13402_OnFinishCooldown(object user, proplist firemode)
{
	Log("On finish cooldown - weapon has correct cooldown, did finish the sound");
	Sound("Weapon::Minigun::MiniTurn", nil, nil, nil, -1);
	_inherited(user, firemode);
	
	if (!CurrentTest().Weapon->Contained())
	{
		PassTest();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
// Tests

global func Test1_OnStart(int player)
{
	Log("-- Test 1: Bug 13402 - Weapon should stop infinite sound when user dies --");

	CurrentTest().Bot = CreateObject(HazardClonk, 80, 190, NO_OWNER);

	CurrentTest().Weapon = CurrentTest().Bot->CreateContents(Weapon_Minigun);
	CurrentTest().Weapon.GetAmmoSource = Global.GetInfiniteAmmoSource;
	CurrentTest().Weapon.OnRecovery = Global.Bug13402_OnRecoveryDie; // Override the recovery function
	CurrentTest().Weapon.Departure = Global.Bug13402_Departure;
	CurrentTest().Weapon.OnStartCooldown = Global.Bug13402_OnStartCooldown; // Override the cooldown, so that the test passes if the weapon cools down
	CurrentTest().Weapon.OnFinishCooldown = Global.Bug13402_OnFinishCooldown; // Override the cooldown, so that the test passes if the weapon cools down

	return true;
}

global func Test1_Execute()
{
	if (CurrentTest().Bot->GetAlive())
	{
		Shoot(CurrentTest().Weapon, CurrentTest().Bot);
		return Wait();	
	}
	else
	{
		if (CurrentTest().BotDied)
		{
			return true;
		}
		else
		{
			CurrentTest().BotDied = true;
			return Wait(120);
		}
	}
}

global func Test1_OnFinished()
{
	CurrentTest().Weapon->RemoveObject();
	CurrentTest().Bot->RemoveObject();
	CurrentTest().BotDied = false;
}

/////////////////////////////////////////////////////////////////////////////////////////////

global func Test2_OnStart(int player)
{
	Log("-- Test 2: Bug 13402 - Weapon should stop infinite sound when the user drops it --");

	CurrentTest().Bot = CreateObject(HazardClonk, 80, 190, NO_OWNER);

	CurrentTest().Weapon = CurrentTest().Bot->CreateContents(Weapon_Minigun);
	CurrentTest().Weapon.GetAmmoSource = Global.GetInfiniteAmmoSource;
	CurrentTest().Weapon.OnRecovery = Global.Bug13402_OnRecoveryDrop; // Override the recovery function
	CurrentTest().Weapon.Departure = Global.Bug13402_Departure;
	CurrentTest().Weapon.OnStartCooldown = Global.Bug13402_OnStartCooldown; // Override the cooldown, so that the test passes if the weapon cools down
	CurrentTest().Weapon.OnFinishCooldown = Global.Bug13402_OnFinishCooldown; // Override the cooldown, so that the test passes if the weapon cools down

	return true;
}

global func Test2_Execute()
{
	if (CurrentTest().Bot->Contents())
	{
		Shoot(CurrentTest().Weapon, CurrentTest().Bot);
		return Wait();	
	}
	else
	{
		if (CurrentTest().BotDroppedWeapon)
		{
			return true;
		}
		else
		{
			CurrentTest().BotDroppedWeapon = true;
			return Wait(120);
		}
	}
}

global func Test2_OnFinished()
{
	CurrentTest().Weapon->RemoveObject();
	CurrentTest().Bot->RemoveObject();
	CurrentTest().BotDroppedWeapon = false;
}

