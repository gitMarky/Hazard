local team_number;

func Construction()
{
    CreateEffect(IntCheckGoal, 100, 1);
}

func Initialize()
{
	SetAction("Exist");
}

func SoundScore()
{
	Sound("Goals::BombingRun::Energize");
}

func SoundOut()
{
	Sound("Goals::BombingRund::DeEnergize");
}

func GetGoalTeam()
{
	return team_number;
}

func SetGoalTeam(int team)
{
	team_number = team;
}


local IntCheckGoal = new Effect
{
    Timer = func()
    {
        var bomb = this.Target->FindObject(Find_InRect(-19,-30,38,49), Find_ID(BombingRun_Bomb), Find_Not(Find_Owner(NO_OWNER))); // Bombe suchen.
	    if(bomb)
	    {
		    var bomb_team = GetPlayerTeam(bomb->GetOwner()); // Saving team
		    if(bomb_team != this.Target->GetGoalTeam())
		    {
		        var goal = FindObject(Find_ID(Goal_BombingRun));
		        if(!goal) return;

			    // Points
			    if(bomb->Contained()) 
			    {
				    goal->~DoScore(bomb_team, +2);
				    Log("$TeamMultiScore$", GetPlayerName(bomb->GetOwner()), 2, GetTeamName(bomb_team));
			    }
			    else 
			    {
				    goal->~DoScore(bomb_team, +1);
				    Log("$TeamScored$", GetPlayerName(bomb->GetOwner()), GetTeamName(bomb_team));
			    }

			    // Effects
			    var dir = this.Target->GetDir();
			    this.Target->SetAction("FlashUp");
			    this.Target->SetDir(dir);
			    
			    var radius = 15;
			 	var bomb_x = bomb->GetX() - this.Target->GetX();
			 	var bomb_y = bomb->GetY() - this.Target->GetY();
			 	var variance = 3;
			 	var bomb_xdir = bomb->GetXDir();
			 	var bomb_ydir = bomb->GetYDir();
	
				// some sparks that represent the bomb vanishing
			    this.Target->CreateParticle("Magic", bomb_x, bomb_y, PV_Random(-radius, +radius), PV_Random(-radius, +radius), PV_Random(20, 35),
			                 {
			                 	Prototype = Particles_Colored(Particles_Magic(), RGB(200, 230, 255), RGB(255, 255, 255)),
			                 	Size = PV_Random(4, 6),
	                 		    ForceY = PV_Gravity(80),
			                 }, 25);

			    // some sparks in the bomb direction
			    this.Target->CreateParticle("Magic", bomb_x, bomb_y, PV_Random(bomb_xdir-variance, bomb_xdir+variance), PV_Random(bomb_ydir-variance, bomb_ydir+variance), PV_Random(15, 25),
			                 {
			                 	Prototype = Particles_Colored(Particles_Magic(), RGB(200, 230, 255), RGB(255, 255, 255)),
			                 	Size = PV_Random(4, 6),
	                 		    ForceY = PV_Gravity(40),
			                 }, 15);

			    // Resetting bomb
			    bomb->ReturnToSpawn();
      
                // TODO: sound does not exist yet; Sound("TeamChange", true);
		    }
	    }
	    return true;
    },
};

func IsBombGoal()
{
	return true;
}

/**
 Creates a bombing run goal at the specified position.
 
 @par for_team The team number of the team that owns the gate.
 @par x The x position in global coordinates.
 @par y The y position in global coordinates.
 @par dir The direction that the gate should face.
 @return object The bomb gate that was created.
 */
global func CreateBombGate(int for_team, int x, int y, int dir)
{
	var gate = CreateObject(BombingRun_BombGate, AbsX(x), AbsY(y), NO_OWNER);
	gate->SetGoalTeam(for_team);
	gate->SetDir(dir);
	return gate;
}


local ActMap = 
{
	FlashUp =
	{
		Prototype = Action,
		Name = "FlashUp",
		Directions = 2,
		FlipDir = 1,
		Length = 6,
		Delay = 2,
		X = 0,
		Y = 80,
		Wdt = 33,
		Hgt = 49,
		OffX = 26,
		OffY = 10,
		FacetBase = 1,
		NextAction = "FlashDown",
		StartCall = "SoundScore"
	},
	FlashDown =
	{
		Prototype = Action,
		Name = "FlashDown",
		Directions = 2,
		FlipDir = 1,
		Length = 5,
		Reverse = 1,
		Delay = 4,
		X = 0,
		Y = 80,
		Wdt = 33,
		Hgt = 49,
		OffX = 26,
		OffY = 10,
		FacetBase = 1,
		NextAction = "Exist",
		StartCall = "SoundOut"
	},
	Exist =
	{
		Prototype = Action,
		Name = "Exist",
		Directions = 2,
		FlipDir = 1,
		Length = 1,
		Delay = 5,
		X = 0,
		Y = 80,
		Wdt = 33,
		Hgt = 49,
		OffX = 26,
		OffY = 10,
		FacetBase = 1,
		NextAction = "Exist"
	}
};

local Name = "$Name$";
local Description = "$Description$";
