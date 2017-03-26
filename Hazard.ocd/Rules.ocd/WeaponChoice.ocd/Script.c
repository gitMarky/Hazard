/*-- WeaponChoice --*/

#include Library_ConfigurableRule

local WeaponChoice;
local spawntimer;
local spawnclonk;
local wares;

protected func Construction()
{
    _inherited(...);
    SetPosition();
    WeaponChoice = [];
    AddTimer(this.Spawntimer, 30);
}


protected func Spawntimer()
{
    if(spawntimer)
    {
        spawntimer--;
        PlayerMessage(spawnclonk->GetOwner(),"@$TimeTillRespawn$",0,spawntimer);
        if(!spawntimer)
        {
            if(spawnclonk->Contained()) spawnclonk->Contained()->RemoveObject(true);
	    }
    }
}

protected func InitializePlayer(int iPlr)
{
    if(!WeaponChoice[iPlr])
    {
        WeaponChoice[iPlr] = [];
    }

    var pClonk = GetCursor(iPlr);
    if(!pClonk || FindObject(Find_ID(Environment_Configuration)))
    {
        ScheduleCall(this,"InitializePlayer",1,0,iPlr);
    }
  
    if(GetPlayerType(iPlr) == C4PT_Script)
    {
    Schedule(this, Format("SetWealth(%d, GetWealth(%d) * GetCrewCount(%d));", iPlr, iPlr, iPlr), 1);
    }
    ScheduleCall(this,"OpenMenu",1,0, iPlr, pClonk);
}

protected func RelaunchPlayer(int iPlr, object pClonk)
{
    if(!pClonk && !(pClonk = GetCursor(iPlr)))
    {
        return ScheduleCall(this,"RelaunchPlayer",1,0,iPlr,pClonk);
    }
    if(!pClonk->GetAlive())
    {
        return ScheduleCall(this,"RelaunchPlayer",1,0,iPlr);
    }

    if(FindObject(Find_ID(Goal_LastManStanding)))
    {
        spawntimer = 10;
        spawnclonk = pClonk;
    }
    
    OpenMenu(iPlr, pClonk);
	return true;
}

private func OpenMenu(int iPlr, object pClonk)
{
    //Menu
    pClonk->CreateMenu(GetID(), this, 0, GetName(), 0, C4MN_Style_Dialog | C4MN_Style_EqualItemHeight);
	
	for(var i = 0, tmp; tmp = GetDefinition(i); i++)
	{
	    if(tmp != Weapon_Base && (tmp->~IsHazardWeapon() || tmp->~IsEquipment() || tmp->~IsUpgrade()))
	    {
	        var icon;
	        if(WeaponChoice[iPlr][i])
	        {
	            icon = Icon_Ok;
	        }
	        else
	        {
	            icon = Icon_Cancel;
	        }
	        pClonk->AddMenuItem(tmp->GetName(), Format("Object(%d)->BuyItem(%i, %d, %d, Object(%d))", this->ObjectNumber(), tmp, i, iPlr, pClonk->ObjectNumber()), icon);
	    }
	}
	pClonk->AddMenuItem("$End$", "Finish", GetID(), 0, pClonk);
	return true;
}

private func BuyItem(id item, int i, int iPlr, object pClonk)
{
    if(!WeaponChoice[iPlr][i])
    {
        if(GetWealth(iPlr) >= item->GetValue())
        {
            DoWealth(iPlr, -(item->GetValue()));
            pClonk->CreateContents(item);
            WeaponChoice[iPlr][i] = true;
            pClonk->Sound("UI::Cash", false, 0, iPlr + 1); 
        }
        else
        {
            WeaponChoice[iPlr][i] = false;
            pClonk->Sound("UI::Error", false, 0, iPlr + 1); 
        }
    }
    
    else
    {
        if(pClonk->FindContents(item))
        {
            DoWealth(iPlr, item->GetValue());
            pClonk->FindContents(item)->RemoveObject();
            WeaponChoice[iPlr][i] = false;
            pClonk->Sound(Format("UI::UnCash%d", Random(3) + 1), false, 0, iPlr + 1);
        }
    }
    
    OpenMenu(iPlr, pClonk);
}

private func Finish(id dummy, object pClonk)
{
    if(pClonk->Contained() && pClonk->Contained()->GetID() == Dummy) pClonk->Contained()->RemoveObject(true);
    return true;
}

public func GameConfigIsChoosable() { return false; }
local Name = "$Name$";
