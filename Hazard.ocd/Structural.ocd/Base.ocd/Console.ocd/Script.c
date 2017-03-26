/**
 A console.
 @author OC-Hazard-Team
 @credits Hazard Team
 @version 1.0
 */

local smashed, console_target, grabbed;

func Construction()
{
	AddEffect("Lights", this, 1, 1, this);
}


// Effects
func FxLightsTimer(object pTarget, proplist pEffect)
{
	/*  if(smashed || GetEffect("EMPShock", this()))
    {
    if(!Random(10)) CastObjects(SPRK, 1, 30, RandomX(-15,15));
    }
  else
    {*/
	if (!Random(8))
		CreateParticle("NoGravSpark", 3, 1, 0, 0, 50, {R: 250, G: 10, B: 10, A: 50});
	if (!Random(8))
		CreateParticle("NoGravSpark", 3, 3, 0, 0, 50, {R: 10, G: 10, B: 250, A: 50});
	//    }
}

// Damage
func Damage()
{
	if (smashed)
		return;
	if (GetDamage() >= 40)
	{
		Sound("Blast1");
		Sound("CrystalHit*");
		SetGraphics("Broken");
		smashed = true;
	}
}

/* Control */

func ControlUp(object user)
{
	return SetTarget(user);
}

func Grabbed(object user, bool grab)
{
	if (!grab)
		return user->CloseMenu();
	if (smashed || GetEffect("EMPShock", this))
	{
		Sound("Electric");
		user->DoDamage(Random(5));
		return;
	}
	
	if (!console_target)
		return SetTarget(user);
	
	user->CreateMenu(console_target->GetID(), this, 0, Format("$Control$: %s", console_target->GetName()), 0, 1);
	
	var desc, condition;
	for (var i = 0; i < GetLength(console_target.console.options); i++)
	{
	    desc = console_target.console.options[i].name;
	    condition = console_target.console.options[i].condition;
	    if(!condition) continue;
		user->AddMenuItem(desc, "ExecuteFunc", GetID(),	0, i, "$Control$");
	}
	return true;
}


protected func ExecuteFunc(dummy, int i)
{
    console_target->Call(console_target.console.options[i].command);
    return true;
}


//EMP-Angriff
func EMPShock()
{
	//Shockable?
	if (GetEffect("EMPShock", this) || smashed)
		return 0;
	
	//Yes
	AddEffect("EMPShock", this, 180, 650, this, GetID());
}


// IsConsole()
func IsConsole()
{
	return true;
}


func IsMachine()
{
	return true;
}

func Set(object target)
{
	console_target = target;
	return console_target;
}

func SetTarget(object user)
{
	user->CreateMenu(GetID(), this, 0, "$ChooseTarget$", 0, 0);
	for (var obj in FindObjects(Find_Func("IsConsoleTarget"), Find_Distance(1000))) 
	{
		user->AddMenuItem(obj->GetName(),"Control", obj->GetID(), 0, obj);
	}
	return true;
}

public func Control(dummy, object target)
{
	Set(target);
	return true;
}

local Touchable = 2;
local Name = "$Name$";
local Description = "$Description$";
