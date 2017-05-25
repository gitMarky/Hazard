#appendto Library_ConfigurableGoal

public func DoWinRound(int faction)
{
	_inherited(faction);
	
	// eliminate losing players
	for (var i = 0; i < GetPlayerCount(); ++i)
	{
		var player = GetPlayerByIndex(i);
		var player_faction = GetFactionByPlayer(player);
		
		if (faction != player_faction)
		{
			EliminatePlayer(player);
		}
	}
}
