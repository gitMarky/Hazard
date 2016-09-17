#include Grenade_Normal

local alreadyhit;
local laser_angle;

func OnDetonation()
{
	alreadyhit = [];
	laser_angle = Random(360);

	AddLightAmbience(50);
	SetLightColor(LIGHT_COLOR_LASER);
	Sound("Weapon::Grenade::LaserGrenade");
	SetXDir();
	SetYDir();
	SetAction("Float");
}

func Detonating()
{
	var laser = CreateObject(Projectile_LaserBeam, 0, 0, GetController());

	laser->Shooter(user)
		 ->Weapon(this.weapon_ID)
		 ->DamageAmount(this.damage)
 	     ->DamageType(this.damage_type)
 	     ->Range(200)
 	     ->LaserWidth(8)
 	     ->LaserLifetime(20)
 	     // TODO: ->Reflections(3)
	     ->HitScan();

	laser->Launch(laser_angle);
	
	laser_angle += RandomX(20,50) + 180;
	
	if (GetActTime() >= 10) RemoveObject();
}

func Detonated()
{
	RemoveObject();
}

// TODO
//func LaserStrike(object pObj)
//{
//  if(!pObj)
//    return();
//
//  // Objekt wurde schon mal getroffen -> weniger schaden
//  if(alreadyhit->AddItem(pObj))
//    DoDmg(iDamage, DMG_Energy, pObj);
//  else
//    DoDmg(iDamage/10, DMG_Energy, pObj);
//  
//  return(1);
//}


func ExplodeDelay() {   return 45;}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Float = {
	Prototype = Action,
	Name = "Float",
	Procedure = DFA_FLOAT,
	Length = 10,
	Delay = 1,
	FacetBase = 1,
	PhaseCall = "Detonating",
},

};
