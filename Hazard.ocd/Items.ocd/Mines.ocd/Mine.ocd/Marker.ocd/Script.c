/**
	Mineflag
	
	Shows friends where mines lie.
 */

func Set(object target)
{
	SetAction("Attach", target);
	
	SetR(target->GetR());
	
	SetOwner(target->GetController());
	SetNewOwner();
	CreateEffect(IntWobble, 1, 1);
}

func OnOwnerChanged()
{
	SetNewOwner();
}

func SetNewOwner()
{
	SetClrModulation(ModulateColor(GetPlayerColor(GetOwner()), RGBa(255, 255, 255, 225)));
	
	if (GetOwner() == NO_OWNER)
		this.Visibility = VIS_None;
	else
		this.Visibility = VIS_Allies | VIS_Owner;
}

func AttachTargetLost()
{
	RemoveObject();
}

local IntWobble = new Effect
{
	Timer = func (int time)
	{
		var size = 1000 + Sin(time * 10, 100);
		Target->SetObjDrawTransform(size, Sin(time * 3, 100), 0, 0, size);
	},
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Attach = {
	Prototype = Action,
	Name = "Attach",
	Procedure = DFA_ATTACH,
	Directions = 1,
	Length = 1,
	Delay = 1,
	FacetBase = 1,
	NextAction = "Attach",
},

};

local Plane = 20000;
