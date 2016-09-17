/**
 A console.
 @author OC-Hazard-Team
 @credits Hazard Team
 @version 1.0
 */

local smashed, target, grabbed, obj;

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

func ControlUp(pClonk)
{
	return SetTarget(pClonk);
}

func Grabbed(object pClonk, bool grab)
{
	if (!grab)
		return pClonk->CloseMenu();
	if (smashed || GetEffect("EMPShock", this))
	{
		Sound("Electric");
		pClonk->DoDamage(Random(5));
		return;
	}
	
	if (!target)
		return SetTarget(pClonk);
	
	pClonk->CreateMenu(target->GetID(), this, 0, Format("$Control$: %s", target->GetName()), 0, 1);
	
	var desc, condition;
	for (var i = 0; i < GetLength(target.console.options); i++)
	{
	    desc = target.console.options[i].name;
	    condition = target.console.options[i].condition;
	    if(!condition) continue;
		pClonk->AddMenuItem
		(
			desc,
			"ExecuteFunc",
			GetID(),
			0,
			i,
			"$Control$"
		);
	}
	return true;
}
protected func ExecuteFunc(dummy, int i)
{
    target->Call(target.console.options[i].command);
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

func Set(pTarget)
{
	target = pTarget;
	return target;
}

func SetTarget(object pClonk)
{
	pClonk->CreateMenu(GetID(), this, 0, "$ChooseTarget$", 0, 0);
	for (obj in FindObjects(Find_Func("IsConsoleTarget"), Find_Distance(1000))) 
	{
		pClonk->AddMenuItem(obj->GetName(),"Control", obj->GetID(), 0, obj);
	}
	return true;
}

public func Control(dummy, object pObj)
{
	Set(pObj);
	return true;
}

local Touchable = 2;
local Name = "$Name$";
local Description = "$Description$";

