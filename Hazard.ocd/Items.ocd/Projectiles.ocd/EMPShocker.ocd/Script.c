#include Projectile_Bullet

func UpdateLight()
{
	AddLightAmbience(damage);
	SetLightColor(LIGHT_COLOR_EMP_SHOCK);
}


private func OnLaunch()
{
	SetAction("Travel");
	UpdateLight();
}

private func OnLaunched()
{
	Sound("Weapon::Motegun::ShockerLoop", nil, nil, nil, 1);
}


/* Fliegen */

public func Travelling()
{
	var self = this;
	
	_inherited(...);
	
	if (self) HandleEmpSize();
}

func HandleEmpSize()
{
	var particle = { Prototype = Particles_EmpShock(GetClrModulation()),
			 		 Size = PV_Random(2 * damage / 3, 3 * damage / 2),};
	

	CreateParticle("EMPShock", 0, 0, GetXDir(), GetYDir(), 20, particle, 1);

	var laser = CreateObject(LaserEffect, 0, 0, NO_OWNER);
	var laser_angle = Random(360);
	var laser_range = BoundBy(damage + RandomX(-10, 10), 5, 55);

	var x_end = GetX() + Sin(laser_angle, laser_range);
	var y_end = GetY() - Cos(laser_angle, laser_range);

	laser->Line(GetX(), GetY(), x_end, y_end)
	 ->SetWidth(5)
	 ->SetLifetime(5)
	 ->Color(GetClrModulation())
	 ->Activate();

	this.damage -= 1;
	if(this.damage <= 0) Remove();
}

//TODO/* Treffer */
//
//private func HitObject(object pObject) {
//  var angle = Angle(GetX(),GetY(),GetX(pObject),GetY(pObject));
//  var dist = Distance(GetX(),GetY(),GetX(pObject),GetY(pObject));
//
//  //Objekte schocken (Objekt auf schockbarkeit prüfen)
//  if(pObject->~IsMachine())
//   if(pObject->~EMPShock())
//    {
//    var laser = CreateObject(LASR, 0,0, GetOwner());
//    laser->Set(angle, 10, dist, 20, pObject, pObject);
//    SetClrModulation(Color(GetActTime()), laser);
//    Sound("EMPShock");
//    }
//
//  if(GBackSolid())
//    Remove();
//}
//
//private func Hit() {
//  Sparks(20,Color(GetActTime()));
//  for(var i = 0 ; i < 7 ; i++)
//  {
//    var laser = CreateObject(LASR, 0,0, GetOwner());
//    laser->Set(Random(360), 5, RandomX(10,30), 5, laser, laser);
//    SetClrModulation(Color(GetActTime()), laser);    
//  }
//
//  Remove();
//}


private func ProjectileColor(int time)
{
	var progress = 20 * time / lifetime;
	var value = Max(0, 255 - progress);
	
	return RGBa(value, value, 255, Max(0, 155 - progress * 3));
}

private func TrailColor(int time)
{
	var progress = 40 * time / lifetime;
	var value = Min(255, 155 + progress);
	
	return RGBa(value, value, 255, Max(0, 115 - progress * 2));
}
