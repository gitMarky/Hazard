
local damaged;

func Incineration()
{
	if (!damaged)
	{
		damaged = true;
		
		
		var particles =
		{
			Prototype = Particles_Colored(Particles_WoodChip(), RGB(228, 228, 228), RGB(255, 255, 255)),
		 	Size = PV_Random(7, 9),
		 	DampingX = 1000,
		 	DampingY = 1000,
		 	Attach = nil,
	 	};
		
		var radius = 20;
		
		CreateParticle("Sandbag", 0, 0, PV_Random(-radius, +radius), PV_Random(-radius, +radius), PV_Random(70, 85), particles, 10);
		RemoveObject();
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 25;
