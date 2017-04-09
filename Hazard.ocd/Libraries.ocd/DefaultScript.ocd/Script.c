#include Library_ScenarioScript_PlayerRespawn

local Name = "Default script";
local Description = "Basic script for scenarios.";
local Hazard;

/**
	Default script
	Basic script for scenarios.
	
	@author OC-Hazard-Team
	@version 1.0
*/
func Initialize()
{
	_inherited(...);
	Hazard = new Hazard 
	{
		Generator = {PowerSupply = false},
		Radar = {FakeRadar = true}
	};

	CreateObject(Environment_RoundManager);
	CreateObject(Environment_Configuration);
}


func InitializePlayer(int player)
{
	_inherited(player, ...);
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
