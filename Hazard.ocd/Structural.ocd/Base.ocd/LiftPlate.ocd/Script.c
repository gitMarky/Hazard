

#include Library_LiftPlate

func Definition(id def)
{
	def.MeshTransformation = Trans_Translate(0, 15000, 0);
	def.PictureTransformation = Trans_Mul(Trans_Rotate(20, 0, 1, 0),
										  Trans_Rotate(-20, 1, 0, 0),
										  Trans_Rotate(-20, 0, 0, 1));
}

func UnstuckClonks()
{
	// looks for passengers in the SolidMask and moves them to the top of the plate
	for (var passenger in FindObjects(Find_InRect(-25, -2, 50, 20), Find_NoContainer()))
		if (passenger->Stuck())
			passenger->SetPosition(passenger->GetX(), GetY());
}

/* Status */

func Passenger()
{
	return FindObject(Find_InRect(-24, -13, 48, 16), Find_OCF(OCF_CrewMember), Find_NoContainer());
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

