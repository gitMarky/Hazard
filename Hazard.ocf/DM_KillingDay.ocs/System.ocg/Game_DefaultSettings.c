/**
 Overloads/implements callbacks from the game configuration object.
 */
 
 #appendto Environment_Configuration

protected func GetDefaultRules()
{
	return [];
}

protected func GetAvailableGoals()
{
	return [Goal_DeathMatchHazard];
}