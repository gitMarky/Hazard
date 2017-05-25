#include Projectile_Bullet

local emp_shock;

func UpdateLight()
{
	AddLightAmbience(damage);
	SetLightColor(LIGHT_COLOR_EMP_SHOCK);
}


private func OnLaunch()
{
	emp_shock = { last_x = GetX(), last_y = GetY(), };
	SetAction("Travel");
	StayOnHit();
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
	
	if (self) HandleEmpHit();
	if (self) HandleEmpSize();
}

func HandleEmpHit()
{
	// this should actually be part of the hit check effect
	var possible_targets = [];
	
	// update coordinates
	var oldx = emp_shock.last_x;
	var oldy = emp_shock.last_y;
	var newx = GetX();
	var newy = GetY();
	emp_shock.last_x = newx;
	emp_shock.last_y = newy;
	
	// start the search
	var distance = Distance(oldx, oldy, newx, newy);
	
	var steps = Max(1, distance / 5);
	
	for (var i = steps; i > 0; --i)
	{
		var curx = i * (oldx - newx) / steps;
		var cury = i * (oldy - newy) / steps;
		
		var new_targets = FindObjects(Find_Distance(damage, curx, cury), Find_Func("IsMachine"), Find_NoContainer());
		
		possible_targets = Concatenate(possible_targets, new_targets);
	}
	
	RemoveDuplicates(possible_targets);
	
	for (var target in possible_targets)
	{
		DoDamageObject(target);
	}
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


func DoDamageObject(object target)
{
	if (target)
	{
		if (target->~IsMachine() && target->~EMPShock())
		{
			var laser = CreateObject(LaserEffect, 0, 0, NO_OWNER);
			laser->Line(GetX(), GetY(), target->GetX(), target->GetY())
			 ->SetWidth(10)
			 ->SetLifetime(20)
			 ->Color(GetClrModulation())
			 ->Activate(); 

			target->Sound("Weapon::Motegun::EMPShock");
		}
	}
}

func OnHitLandscape()
{
	RemoveOnHit(); // tell the library that we can be removed now

	CreateSparksEffect(20, GetClrModulation());
	for(var i = 0; i < 7 ; ++i)
	{
	
		var laser = CreateObject(LaserEffect, 0, 0, NO_OWNER);
		
		laser->SetRotation(Random(360))
			 ->SetRange(RandomX(10, 30))
			 ->SetWidth(5)
			 ->SetLifetime(5)
			 ->Color(GetClrModulation())
			 ->Activate(); 
	}
}


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
