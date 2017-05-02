/**
	Default script
	Basic script for scenarios.
	
	@author OC-Hazard-Team
	@version 1.0
*/

#include Library_ScenarioScript_PlayerRespawn

static const SCENPAR_HAZARD_GOAL_Random = -1;
static const SCENPAR_HAZARD_GOAL_BombingRun = 1;
static const SCENPAR_HAZARD_GOAL_CaptureTheFlag = 2;
static const SCENPAR_HAZARD_GOAL_DeathMatch = 3;
static const SCENPAR_HAZARD_GOAL_LastManStanding = 4;
static const SCENPAR_HAZARD_GOAL_Domination = 5;
static const SCENPAR_HAZARD_GOAL_AlienHunt = 6;
static const SCENPAR_HAZARD_GOAL_Assault = 7;

local Name = "Default script";
local Description = "Basic script for scenarios.";
static Hazard;

/**
 * Default script.
 *
 * In the actual scenario script, call {@code {@link Library_DefaultScript#SetGoal}; _inherited(...);},
 * then add any of your own code.
 */
func Initialize()
{
	_inherited(...);
	
	// Basic properties
	
	InitializeProperties();
	
	// Create necessary objects

	CreateObject(Environment_RoundManager);
	CreateObject(Environment_Configuration);
	
	// Create scenario specific stuff
	
	CreateBackground();
	CreateDeco();
	CreateSpawnPoints();
	CreateWaypoints();
}


private func InitializePlayer(int player)
{
	_inherited(player, ...);
}

private func InitializeProperties()
{
	if (nil == Hazard)
	{
		Hazard = new Hazard 
		{
			Generator = {PowerSupply = false},
			Radar = {FakeRadar = true},
			Scenario_Goal = SCENPAR_HAZARD_GOAL_Random,
		};
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Callbacks from configuration menu object.

/**
 * Callback from configuration menu object.
 */
private func OnConfigurationEnd()
{
	_inherited(...);

	// the players have been released from their containers by
	// the round countdown. Put them in relaunch containers
	// at the starting position
	for (var i = 0; i < GetPlayerCount(); i++)
	{
		SpawnPlayer(GetPlayerByIndex(i));
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Callbacks from the round manager.


/**
 Callback from the round manager.
 */
protected func OnRoundEnd(int round)
{
	GameOver();
}


private func GetPlayerCrewID(int player)
{
	return HazardClonk;
}

private func StartingEquipment(object crew)
{
	//nobody gets anything
}

private func SetGoal(int goal)
{
	InitializeProperties();

	DebugLog("Set goal to %d", goal);
	Hazard.Scenario_Goal = goal;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Overloadable functions

/**
 * Use this function to create background objects, adjust sky parameters, etc.
 */
public func CreateBackground()
{
}

/**
 * Use this function to create deco objects.
 */
public func CreateDeco()
{
}

/**
 * Use this function to create spawn points.
 */
public func CreateSpawnPoints()
{
}

/**
 * Use this function to create waypoints for the AI.
 */
public func CreateWaypoints()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Helpers for spawn points

/**
 * Gets a proplist with the usual spawn points. 
 * 
 * This is more convenient than copy & pasting the script each time.
 */
public func GetSpawnPointTemplates()
{
	return {
		ammo_standard = CreateSpawnPoint(0, 0)->SpawnItem(STAP),
		ammo_grenade = CreateSpawnPoint(0, 0)->SpawnItem(GRAP),
		ammo_gasoline = CreateSpawnPoint(0, 0)->SpawnItem(GSAP),
		ammo_energy = CreateSpawnPoint(0, 0)->SpawnItem(ENAP),
		ammo_missile = CreateSpawnPoint(0, 0)->SpawnItem(MIAP),
		
		upgrade_laser = CreateSpawnPoint(0, 0)->SpawnItem(Upgrade_Laser),
		upgrade_slime = CreateSpawnPoint(0, 0)->SpawnItem(Upgrade_Slime),
		upgrade_rifle = CreateSpawnPoint(0, 0)->SpawnItem(Upgrade_WeaponPart),
		
		weapon_pumpgun = CreateSpawnPoint(0, 0)->SpawnItem(Weapon_Pumpgun),
		weapon_grenade = CreateSpawnPoint(0, 0)->SpawnItem(Weapon_GrenadeLauncher),
		weapon_flame = CreateSpawnPoint(0, 0)->SpawnItem(Weapon_FlameThrower),
		weapon_bazooka = CreateSpawnPoint(0, 0)->SpawnItem(Weapon_Bazooka),
		weapon_energy = CreateSpawnPoint(0, 0)->SpawnItem(Weapon_EnergyRifle),
		weapon_motegun= CreateSpawnPoint(0, 0)->SpawnItem(Weapon_Motegun),
		weapon_mine = CreateSpawnPoint(0, 0)->SpawnItem(MINE),
		weapon_minigun = CreateSpawnPoint(0, 0)->SpawnItem(Weapon_Minigun),
		weapon_chainsaw = CreateSpawnPoint(0, 0)->SpawnItem(Weapon_Chainsaw),
		
		item_jetpack = CreateSpawnPoint(0, 0)->SpawnItem(Gear_Jetpack),
		item_medipack = CreateSpawnPoint(0, 0)->SpawnItem(MEDI),
		item_airstrike = CreateSpawnPoint(0, 0)->SpawnItem(AIRS),
		item_armor = CreateSpawnPoint(0, 0)->SpawnItem(HARM),
		item_novodekan = CreateSpawnPoint(0, 0)->SpawnItem(NVDN),
		item_drone = CreateSpawnPoint(0, 0)->SpawnItem(DRSU),
	    item_shield = CreateSpawnPoint(0, 0)->SpawnItem(HSHD),
	};
}

/**
 * Removes all spawn point templates in a given proplist.
 */
public func RemoveSpawnPointTemplates(proplist templates)
{
	for (var property in GetProperties(templates))
	{
		if (templates[property] != nil)
		{
			templates[property]->RemoveObject();
		}
	}
}
