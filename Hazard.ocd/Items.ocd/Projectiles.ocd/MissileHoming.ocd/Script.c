#include Projectile_Missile

local homing_target;


public func Acceleration() { return 4; }
public func ExplodeDelay() { return 70; }
public func MaxSpeed() { return 160; }


public func HomingBegin() { return 15; }
public func MaxHomingDist() { return 400; }
public func MaxHomingAngle() { return 60; }


func ControlSpeed()
{
	DoHoming();
	_inherited(...);
}

func DoHoming()
{
	// nur lenken wenn schon etwas fliegend
	if (GetActTime() >= this->HomingBegin())
	{
		if (homing_target)
		{
			FollowTarget();
		}
		else
		{
			homing_target = FindTarget();

			if (homing_target)
			{
				Sound("Weapon::BipBipBip");
			}
		}
	}
}

func FindTarget()
{
	return FindMostValuableTarget(this->MaxHomingDist(), GetShooter());
}


private func FollowTarget()
{
    var target_angle = Angle(GetX(), GetY(), homing_target->GetX(), homing_target->GetY());
    var my_angle = GetR();

    var difference = Normalize(target_angle - my_angle, -180);
    var turn = Min(Abs(difference), 6);

    SetR(my_angle + turn * Sign(difference));
}
