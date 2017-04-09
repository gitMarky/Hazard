#appendto Environment_Configuration


/**
 In Hazard the bot configuration happens in the lobby.
 @return bool {@c false}.
 */
public func CanConfigureBots()
{
	return false;
}


/**
 In Hazard the goal configuration is done by scenario parameters.
 @return bool {@c false}.
 */
public func CanConfigureGoal()
{
	return false;
}


/**
 In Hazard the team configuration happens in the lobby.
 @return bool {@c false}.
 */
public func CanConfigureTeams()
{
	return false;
}


/**
 In Hazard the configuration of spawn points is not possible.
 @return bool {@c false}.
 */
public func CanConfigureSpawnPoints()
{
	return false;
}


public func GetGameConfigurationIcon()
{
	return Icon_Configuration;
}


private func GetAvailableGoals()
{
	if (Hazard.Scenario_Goal == SCENPAR_HAZARD_GOAL_Random) return this->~GetAvailableGoalsRandom();
    if (Hazard.Scenario_Goal == SCENPAR_HAZARD_GOAL_BombingRun) return [Goal_BombingRun];
    //if (Hazard.Scenario_Goal == SCENPAR_HAZARD_GOAL_CaptureTheFlag) return [];
    //if (Hazard.Scenario_Goal == SCENPAR_HAZARD_GOAL_DeathMatch) return [];
    //if (Hazard.Scenario_Goal == SCENPAR_HAZARD_GOAL_LastManStanding) return [];
    //if (Hazard.Scenario_Goal == SCENPAR_HAZARD_GOAL_Domination) return [];
    //if (Hazard.Scenario_Goal == SCENPAR_HAZARD_GOAL_AlienHunt) return [];
    //if (Hazard.Scenario_Goal == SCENPAR_HAZARD_GOAL_Assault) return [];

	FatalError(Format("Goal selection was not possible: SCENPAR_HAZARD_GOAL = %d", Hazard.Scenario_Goal));
}
