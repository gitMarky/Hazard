#include Clonk
#include Library_AmmoManager
#include Library_Agility
#include Library_UseGear

public func GetAmmoSource(id ammo)
{
	return AMMO_Source_Local;
}

func Initialize()
{
    _inherited(...);
    var hud = this->GetHazardHUD();
    if (hud) ScheduleCall(this, this.UpdateHazardHUD, 1);
}

func SetSkin(int new_skin)
{
	// Remember skin
	skin = new_skin;
	
	//Steampunk
	SetGraphics(skin_name = "Alchemist", Clonk);
	gender = 0;
	
	SetHazardSkin();

	RemoveBackpack(); // remove the backpack

	//refreshes animation (whatever that means?)
	// Go back to original action afterwards and hope
	// that noone calls SetSkin during more complex activities
	var prev_action = GetAction();
	SetAction("Jump");
	SetAction(prev_action);
	SetOwner(GetOwner()); // somehow the color did not get updated after setting the color

	return skin;
}

func SetHazardSkin()
{
	SetMeshMaterial("HazardClonk");
	SetMeshMaterial("HazardClonkTunic", 1);
}

func SetHazardArmorSkin()
{
	SetMeshMaterial("HazardClonkArmor");
	SetMeshMaterial("HazardClonkArmorTunic", 1);
}

public func UpdateHazardHUD()
{
    var weapon = this->GetHandItem(0);

    var hud = this->GetHazardHUD();
    if (hud)
    {
    	hud->~Update(weapon, this, this);
    	ScheduleCall(this, this.UpdateHazardHUD, 1);
    }
}

local ActMap = {

JetpackFlight = {
	Prototype = ActMap.Jump,
	Name = "JetpackFlight",
},

Backflip = {
	Prototype = ActMap.Jump,
	Name = "Backflip",
	Delay = ANIM_BACKFLIP_Length,
	NextAction = "Jump",
}

};

