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
