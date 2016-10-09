#include Library_TeamGoal

public func GetDefaultWinScore()
{
	return 5;
}

public func GetDescription(int player)
{
	var message = Format("$Description$ $WinString$", GetWinScore());
	return message;
}

func Activate(int player) // TODO: remove this, once there is a fitting description
{
}

func IsConfigurable(){ return true;} // available in the game configuration

func GetBomb()
{
	return FindObject(Find_ID(BombingRun_Bomb));
}

func GetBombCarrier(object bomb)
{
	return bomb->Contained();
}

func GetOwnGoal(int owner)
{
	for (var goal in FindObjects(Find_ID(BombingRun_BombGate))) 
		if (goal->GetGoalTeam() == GetPlayerTeam(owner))
			return goal;
}

func GetEnemyGoal(int owner)
{
	for (var goal in FindObjects(Find_ID(BombingRun_BombGate))) 
		if (goal->GetGoalTeam() != GetPlayerTeam(owner))
			return goal;
}


public func DoCleanup(int round)
{
	for (var bomb in FindObjects(Find_ID(BombingRun_Bomb)))
		bomb->ForceRemove();

	RemoveAll(FindObjects(Find_ID(BombingRun_BombGate)));
}

/* Global functions */

/** CreateBomb
    Create a bomb at the specified position with the specified color.
    
    @par x X-coordinate of the bomb.
    @par y Y-coordinate of the bomb.
    @par color Color of the bomb.
*/
global func CreateBomb(int x, int y, int color)
{
	var pBomb = CreateObject(BombingRun_Bomb, AbsX(x), AbsY(y), -1);
	pBomb->Init(x, y, color);
}

local ActMap = 
{
	BombFriendly = 
	{
		Prototype = Action,
		Name = "BombFriendly",
		Length = 1,
		X = 64,
		Y = 0,
		Wdt = 24,
		Hgt = 24
	},
	BombEnemy =
	{
		Prototype = Action,
		Name = "BombEnemy",
		Length = 1,
		X = 64,
		Y = 24,
		Wdt = 24,
		Hgt = 24
	},
	BombGone =
	{
		Prototype = Action,
		Name = "BombGone",
		Length = 1,
		X = 88,
		Y = 0,
		Wdt = 24,
		Hgt = 24
	}
};

local Name = "$Name$";
local Description = "$Description$";
local bomb_status = "";

/* Callbacks from the bomb or gates */

/**
 The bomb was destroyed and respawns at its original position.
 */
public func OnBombReturned()
{
	UpdateBombStatus();
}

/**
 The bomb exits the holder. This may be an intentional pass to another player.
 */
public func OnBombLost()
{
	UpdateBombStatus("BombGone");
}

/**
 The bomb scored at a goal.
 */
public func OnBombScored()
{
	UpdateBombStatus();
}

/**
 Someone collected the bomb.
 */
public func OnBombTaken(object new_carrier)
{
	var status;
	if (new_carrier)
	{
		status = [];
	
		var carrier_team = GetPlayerTeam(new_carrier->GetOwner());
		
		for (var i = 0; i < GetPlayerCount(); ++i)
		{
			var team = GetPlayerTeam(GetPlayerByIndex(i));
			
			if (team == carrier_team)
				status[i] = "BombFriendly";
			else
				status[i] = "BombEnemy";
		}
	}
	UpdateBombStatus(status);
}

private func UpdateBombStatus(status)
{
	bomb_status = status ?? "";
	NotifyHUD();
}

public func GetPictureName(int player)
{
	if (GetType(bomb_status) == C4V_Array)
		return bomb_status[player];
	else
		return bomb_status ?? "";
}

