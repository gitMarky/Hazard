local emp_range, max_range;

func Initialize()
{
	emp_range = 10;
	max_range = 50;
	UpdateLight();
	SetAction("Grow");
}

func SetEmpRange(int range)
{
	max_range = range;
	UpdateLight();
}

func UpdateLight()
{
	AddLightAmbience(max_range);
	SetLightColor(LIGHT_COLOR_EMP);
}

func Grow()
{
	//Log("Growing - EMP range is %d", emp_range);
	emp_range += 5;
	if (emp_range >= max_range)
	{
		EmpScan();
		RemoveObject();	
	}
	else
	{
		EmpEffects();
	}
}

func EmpEffects()
{
	var particle = { Prototype = Particles_EmpShock(),
			 		 Size = PV_Random((2 * emp_range) / 3, (3 * emp_range) / 2),};
	

	CreateParticle("EMPShock", 0, 0, 0, 0, 20, particle, 1);
	
	// cast some rays
	for (var i = 0; i < 2; ++i)
	{
		var laser = CreateObject(LaserEffect, 0, 0, NO_OWNER);
		
		var laser_angle = Random(360);
		
		var x_end = GetX() + Sin(laser_angle, emp_range / 2);
		var y_end = GetY() - Cos(laser_angle, emp_range / 2);

		laser->Line(GetX(), GetY(), x_end, y_end)
		 ->SetWidth(10)
		 ->SetLifetime(3)
		 ->Color(RGBa(28, 143, 241, 128))
		 ->Activate();
	}
}

func EmpScan()
{
	for (var machine in FindObjects(Find_Distance(emp_range + 10), Find_NoContainer(), Find_Func("IsMachine"))) 
	{
		if (ObjectDistance(machine) < emp_range) // does this make sense? we are searchgin in emp_range / 2 only, so the distance should be correct anyway...
			machine->~EMPShock();
	}
}

local ActMap = {
Grow = {
	Prototype = Action,
	Name = "Grow",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 1,
	FacetBase = 1,
	NextAction = "Grow",
	EndCall = "Grow",
},

};
