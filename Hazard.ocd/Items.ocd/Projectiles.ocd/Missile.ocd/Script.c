#include Grenade_Normal


local speed;

public func Acceleration() { return 5; }
public func ExplodeDelay() { return 60; }
public func MaxSpeed() { return 180; }


public func Launch(int angle, proplist deviation)
{
	SetR(angle);
	_inherited(angle, deviation, ...);
}

private func OnLaunch()
{
	exploded = false;
	speed = 0;
	SetAction("Travel");
	AddEffect("Grenade", this, 1, 1, this);
}

protected func ControlSpeed()
{
	if(speed < this->MaxSpeed())
		speed = BoundBy(speed + this->Acceleration(), 0, this->MaxSpeed());

	velocity_x =  Sin(GetR(), speed);
	velocity_y = -Cos(GetR(), speed);

	if (GetAction() == "Travel")
	{
		SetXDir(velocity_x);
		SetYDir(velocity_y);
	}
}

func HandleTrail()
{
	var distance = Distance(0, 0, GetXDir(), GetYDir());
	var max_x = +Sin(GetR(), distance / 10);
	var max_y = -Cos(GetR(), distance / 10);
	var off_x = max_x;
	var off_y = max_y;
	var particle_distance = 25;

	for(var i = 0; i < distance; i += particle_distance)
	{
		var x = -max_x * i / distance;
		var y = -max_y * i / distance;

		var rand = RandomX(-30, 30);
		var xdir = +Sin(GetR() + rand, 20);
		var ydir = -Cos(GetR() + rand, 20);
		
		var size_thrust = RandomX(8, 10);
		var size_smoke = RandomX(10, 12);

		CreateParticle("Thrust", x - off_x, y - off_y, GetXDir()/2, GetYDir()/2, PV_Random(5, 10),
		{
			Prototype = Particles_ThrustColored(255, 200, 200),
			Size = size_thrust,
		});
		CreateParticle("Smoke2", 2 * (x - off_x), 2 * (y - off_y) + 1, xdir, ydir, PV_Random(30, 40),
		{
			Prototype = Particles_ThrustColored(220, 200, 180),
			Size = size_smoke,
		});
	}
}


func Hit()
{
	Detonate();
}

func OnDetonation()
{
	BlastObjects(GetX(), GetY(), damage / 2);
	BlastObjects(GetX(), GetY(), damage / 2);
	Explode(damage);
}

func Damage()
{
	if (GetDamage() > 20) Detonate();
}


func EMPShock()
{
	SetAction("Idle");
}

func NoDecoDamage() { return true; }
func IsMachine() { return true; }

// TODO
//public func OnDmg(int iDmg, int iType) {
//	if(iType == DMG_Bio)		return(100);
//	if(iType == DMG_Fire)		return(100);
//}
