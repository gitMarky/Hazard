
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

/*-- Tests --*/

// override for the weapon: kills its user
global func Test1_OnRecovery(object user, proplist firemode)
{
	Log("On Recovery - kill the weapon user");
	_inherited(user, firemode);
	
	if (user)
	{
		user->Kill();
	}
}


global func Test1_Departure(object container)
{
	Log("Departure - print all effects that are active in the weapon");
	
	for (var i = 0; i < GetEffectCount(); ++i)
	{
		var active = GetEffect("*", this, i);
		Log(" - active: %v", active);
	}
	
	_inherited(container);
}


global func Test1_OnStart(int player)
{
	CurrentTest().Bot = CreateObject(HazardClonk, 80, 190, NO_OWNER);

	CurrentTest().Weapon = CurrentTest().Bot->CreateContents(Weapon_Minigun);
	CurrentTest().Weapon.GetAmmoSource = Global.GetInfiniteAmmoSource;
	CurrentTest().Weapon.OnRecovery = Global.Test1_OnRecovery; // Override the recovery function
	CurrentTest().Weapon.Departure = Global.Test1_Departure;

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
			Log("Bot died");
			return PassTest();
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

