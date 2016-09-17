#include Grenade_Normal

func OnDetonation()
{
	var emp = CreateObject(Shockwave_EMP, 0, 0, GetOwner());
	emp->SetEmpRange(this.damage);
    emp->Sound("Weapon::Grenade::EMP");
	RemoveObject();
}

func ExplodeDelay(){ return 20;}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
