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
	Default script
	Basic script for scenarios.
	
	@author OC-Hazard-Team
	@version 1.0
*/
func Initialize()
{
	_inherited(...);
	
	InitializeProperties();

	CreateObject(Environment_RoundManager);
	CreateObject(Environment_Configuration);
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
	
	Log("Set goal to %d", goal);
	Hazard.Scenario_Goal = goal;
}
