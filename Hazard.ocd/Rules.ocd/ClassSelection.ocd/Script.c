/**
	Class selection
	Provides several classes for all players.
	
	@author Hazard Team
*/

#include Library_ConfigurableRule

local classes;
local choosemenu_id;

protected func Initialize()
{
    _inherited(...);
    classes = [];
/*    if(FindObject(Find_ID(GetID())) /*|| FindObject(Find_ID(Rule_InstaGIB)) || FindObject(Find_ID(Rule_WeaponChoice))*//*)
    {
        return RemoveObject();
    }*/
}

public func InitializePlayer(int iPlr)
{
    return RelaunchPlayer(iPlr, GetCrew(iPlr));
}

public func RelaunchPlayer(int iPlr, object pClonk)
{
    if(!pClonk) if(!(pClonk = GetCrew(iPlr)))
    {
        return ScheduleCall(this, "RelaunchPlayer", 1, 0, iPlr);
    }
    
    var dummy = CreateObject(Dummy, pClonk->GetX(), pClonk->GetY(), pClonk->GetOwner());
    dummy->SetCategory(dummy->GetCategory(), C4D_Foreground);
    dummy.Visibility = VIS_Owner;
    dummy->SetGraphics(nil, pClonk->GetID(), 1, 5, nil, 1, pClonk);
    pClonk->Enter(dummy);

    
    // Menu
    /*var menu = {
        Player = pClonk->GetOwner(),
        Decoration = GUI_MenuDeco,
        Margin = ["2em", "2em"],
        Target = pClonk,
        
        classes = {
            Right = "50%-0.5em",
        },
    };*/
    
    	var menu = 
	    {
		    Player = pClonk->GetOwner(),
		    Decoration = GUI_MenuDeco,
	    	Margin = ["2em", "2em"],
		    list = 
		    {
			    Right = "50%-0.5em",
			    Style = GUI_VerticalLayout,
			    BackgroundColor = RGBa(0, 0, 0, 150)
		    },
		    right = {
			    Target = pClonk,
			    Left = "50%+0.5em",
			    ID = 1,
			    icon = 
			    {
				    Left = "50%-4em",
				    Right = "50%+4em",
				    Bottom = "5em",
				    Top = "1em",
				    Symbol = HazardClonk
			    },
			    textwindow =
			    {
			    	Top = "6em",
			    	Left = "10%",
		    		Right = "80%",
			    	Text = "Select your class"
			    }
		    },
		    separator = {
			    Left = "50%-0.5em",
			    Right = "50%+0.5em",
			    BackgroundColor = RGBa(240, 240, 240, 150)
		    }
	    };
	    
	
	var index = 0;
    for(var i = 1, class; class = eval(Format("this->~Class%dInfo()",i)); i++)
    {
        if(class && GetType(class) == C4V_PropList)
        {
            var subm =
		    {
			    ID = 100 + index,
			    Priority = index,
			    Bottom = "+2em",
			    BackgroundColor = {Std = 0, Hover = 0x50ffff00, Nope = 0x50ff0000},
			    OnMouseIn = [ 
			    	GuiAction_Call(this, "ClassUpdateDesc", class), 
			    	GuiAction_SetTag("Hover")
			    ],
			    OnMouseOut = GuiAction_SetTag("Std"),
			    OnClick = GuiAction_Call(this, "SelectClass", class),
			    icon = {
			    	Symbol = class.Icon,
			    	Right = "+2em"
			    },
			    text = {
			    	Left = "+2.5em", 
			    	Style = GUI_TextVCenter, 
			    	Text = class.Name
			    },
		    };
		    GuiAddSubwindow(subm, menu.list);
        }
    }
    
    choosemenu_id = GuiOpen(menu);
	pClonk->SetMenu(choosemenu_id, true);
}

private func ClassUpdateDesc(proplist data, int iPlr, int ID, int subwindowID, object target)
{
	var update = 
	{
		icon = {Symbol = data.Name},
		textwindow = {Text = data.Description}
	};
	GuiUpdate(update, choosemenu_id, 1, this);
}

private func SelectClass(proplist data, int iPlr, int ID, int subwindowID, object target)
{
    GuiClose(choosemenu_id);
    var pClonk = GetCrew(iPlr);
    if(pClonk->Contained()) pClonk->Contained()->RemoveObject(true);
    
    for(var item in data.Items)
    {
        pClonk->CreateContents(item[0], item[1]);
    }
}

public func GameConfigIsChoosable()
{
    return false;
}


local Name = "$Name$";
local Description = "$Description$";
