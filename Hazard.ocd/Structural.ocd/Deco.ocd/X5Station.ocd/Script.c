
func Initialize()
{
	SetAction("Be");
}

func Init2(int dir)
{
	SetDir(dir);
	
	var r = -2 * (dir == 1) + 1;
//	var light;
	var x = -286 + dir * 572;
//	var y = -187;
//	var c = RGBa(255, 255, 255, 50);
	
	var rocket = CreateObject(X5RK, x + r * 272, 171, GetOwner());
	rocket->SetAction("Clamped");
	rocket->SetDir(dir);
	/*
  
  TODO 
  
  light = AddLightCone(1000,c,this);
  light->ChangeOffset(x+r*21,y+79);
  light->ChangeR(122*r);
  light->ChangeSizeXY(3000,6000);

  light = AddLightCone(1000,c,this);
  light->ChangeOffset(x+r*168,y+196);
  light->ChangeR(128*r);
  light->ChangeSizeXY(3000,4000);
  
  light = AddLightCone(1000,c,this);
  light->ChangeOffset(x+r*166,y+74);
  light->ChangeR(80*r);
  light->ChangeSizeXY(3000,4000);

  light = AddLightCone(1000,c,this);
  light->ChangeOffset(x+r*391,y+108);
  light->ChangeR(270*r);
  light->ChangeSizeXY(4000,3000);

  light = AddLightCone(1000,c,this);
  light->ChangeOffset(x+r*414,y+213);
  light->ChangeR(252*r);
  light->ChangeSizeXY(5000,2000);
  */
	// hinter der Rakete
	//light = AddLightCone(1000,c,this);
	//light->ChangeOffset(x+r*345,y+213);
	//light->ChangeR(270*r);
	//light->ChangeSizeXY(2000,7000);
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
Be = {
	Prototype = Action,
	Name = "Be",
	Procedure = DFA_NONE,
	Directions = 2,
	FlipDir = 1,
	FacetBase = 1,
	NextAction = "Hold",
},

};
