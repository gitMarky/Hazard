/*-- Valve --*/


local open;

func Initialize()
{
	open = false;
	SetAction("Exist");
}

func ToggleValve()
{
	open = !open;
	UpdatePipesystem();
}

func Status()
{
	return open;
}

/* Serialisierung */

func Serialize(array extra) // TODO: implement proper saving mechanism
{
	if (open)
		extra[GetLength(extra)] = "ControlDig()";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// interaction

func IsInteractable(object user){	return true;}


// Adapt appearance in the interaction bar.
public func GetInteractionMetaInfo(object clonk)
{
	var desc;
	if (open)
	{
		desc = "$CloseValve$";
	}
	else
	{
		desc = "$OpenValve$";
	}
	return { Description = desc, IconName = nil, IconID = VALV };
}

// Called on player interaction.
public func Interact(object user)
{
	if (!IsInteractable(user)) return true;
	ToggleValve();
	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Exist = {
	Prototype = Action,
	Name = "Exist",
	Procedure = DFA_FLOAT,
	Delay = 1,
	FacetBase = 1,
	NextAction = "Exist",
},

};
