/**
 The generator produces energy.
 @author OC-Hazard-Team
 @credits Hazard Team
 @version 1.0
 */

#include Library_Structure
#include Library_PowerProducer
#include Library_Flag

public func IsWorking()
{
	return this->GetAction() == "Work";
}

func TurnOn()
{
	if ((this->GetAction() == "Work") || (this->GetAction() == "Start1") || (this->GetAction() == "Start2"))
		return;
	var phase = this->GetPhase();
	if (this->GetAction() == "Offline" || this->GetAction() == "End1")
		this->SetAction("Start1");
	if (this->GetAction() == "End2")
		this->SetAction("Start2");
	SetPhase(phase);
	Sound("Energize");
	CreateEffect(IntWorking,1,1);
}

func TurnOff()
{
	if((this->GetAction()== "Idle") || (this->GetAction() == "End1") || (this->GetAction() == "End2"))
		return;
	var phase = this->GetPhase();
	if (this->GetAction() == "Work" || this->GetAction() == "Start2")
		this->SetAction("End2");
	if (this->GetAction() == "Start1")
		this->SetAction("End1");
	SetPhase(phase);
	Sound("DeEnergize");
	RemoveEffect(nil, this, IntWorking);
}

func Started()
{
	GameCallEx("PowerSupplyOn");
}
func Ended()
{
	GameCallEx("PowerSupplyOff");
}

func Initialize()
{
    _inherited(...);
	this->SetAction("Offline");
}

/* Console */
public func IsConsoleTarget()  {return true;}
local console = {
options = [TurnOnConsole, TurnOffConsole],
};


local TurnOnConsole = {
    name = "$TurnOn$",
    command = TurnOn,
    condition = true,
};

local TurnOffConsole = {
    name = "$TurnOff$",
    command = TurnOff,
    condition = true,
};

/* Energy */
local DefaultFlagRadius;

public func IsPowerProducer()   {return Scenario.Hazard.Generator.PowerSupply; }
public func IsSteadyPowerProducer() { return true; }
public func GetProducerPriority() { return 3; }

public func OnPowerProductionStart(int amount) 
{
	TurnOn();
	return true;
}

public func OnPowerProductionStop(int amount)
{
    TurnOff();
    return true;
}

local Name = "$Name$";
local Description = "$Description$";
local ActMap = 
{
	Work=
	{
		Prototype = Action,
		Name = "Work",
		Procedure = DFA_NONE,
		Delay = 1,
		Length = 29,
		FacetBase = 1,
		X = 0,
		Y = 150,
		Wdt = 150,
		Hgt = 50,
		OffX = 72,
		OffY = 64,
		NextAction = "Work",
		Sound = "Energy",
	},
	Start1 =
	{
		Prototype = Action,
		Name = "Start1",
		Procedure = DFA_NONE,
		Delay = 3,
		Length = 29,
		FacetBase = 1,
		X = 0,
		Y = 150,
		Wdt = 150,
		Hgt = 50,
		OffX = 72,
		OffY = 64,
		NextAction = "Start2",
		Sound = "Energy"
	},
	Start2 =
	{
		Prototype = Action,
		Name = "Start2",
		Procedure = DFA_NONE,
		Delay = 2,
		Length = 29,
		FacetBase = 1,
		X = 0,
		Y = 150,
		Wdt = 150,
		Hgt = 50,
		OffX = 72,
		OffY = 64,
		NextAction = "Work",
		Sound = "Energy",
		EndCall = "Started"
	},
	End2 =
	{
		Prototype = Action,
		Name = "End2",
		Procedure = DFA_NONE,
		Delay = 2,
		Length = 29,
		FacetBase = 1,
		X = 0,
		Y = 150,
		Wdt = 150,
		Hgt = 50,
		OffX = 72,
		OffY = 64,
		NextAction = "End1",
		Sound = "Energy"
	},
	End1 =
	{
		Prototype = Action,
		Name = "End1",
		Procedure = DFA_NONE,
		Delay = 3,
		Length = 29,
		FacetBase = 1,
		X = 0,
		Y = 150,
		Wdt = 150,
		Hgt = 50,
		OffX = 72,
		OffY = 64,
		NextAction = "Offline",
		Sound = "Energy",
		EndCall = "Ended"
	},
	Offline =
	{
		Prototype = Action,
		Name = "Offline",
		Procedure = DFA_NONE,
		Delay = 0,
		Length = 1,
		FacetBase = 1,
		X = 0,
		Y = 150,
		Wdt = 150,
		Hgt = 50,
		OffX = 72,
		OffY = 64,
		NextAction = "Offline"
	}
};

local IntWorking = new Effect {
    Timer = func() {
        if(!Random(100))
		{
			LaunchLightning(GetX(),GetY(),RandomX(-15,15),0,-10,10);
		}
		return true;
    },
};
