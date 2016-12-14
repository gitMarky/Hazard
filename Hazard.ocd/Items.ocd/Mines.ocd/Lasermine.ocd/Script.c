#include MINE

local shooter;
local last_explosion;
local laser;

func ActivateMine(object user)
{
	shooter = user;
	_inherited(user);
}

func OnActive()
{
	_inherited(...);
	StartLaser();
}

func Check()
{
	// do nothing
}

func StartLaser()
{
	// create a laser effect that is used for drawing the laser line
	laser = CreateObject(LaserEffect, 0, 0, NO_OWNER);
	laser->SetWidth(2)->Color(RGB(255, 0, 0));
	// start a hit check
	ScheduleCall(this, this.CheckLaser, 1);
}

func CheckLaser()
{
	var self = this;

	// create a projectile that checks whether it hits objects or the landscape
	var beam = CreateObject(Projectile_LaserBeam, 0, 0, GetController());
	beam->SetPosition(GetX() + Sin(GetR(), 3), GetY() - Cos(GetR(), 3));

	beam->Shooter(shooter)
		->Weapon(GetID())
		->DamageAmount(0)
 	    ->Range(200)
	    ->HitScan();

	// override the projectile functions, so that it calls functions in the mine
	beam.OnHitObject = GetID().OnHitObject;
	beam.OnLandscape = GetID().OnHitLandscape;
	beam.OnHitScan = GetID().OnHitScan;
	beam.mine = this;

	// launch the projectile
	beam->Launch(GetR());
	
	if (self) // mine could be removed at this point
	{
		// start another hit check
		ScheduleCall(self, self.CheckLaser, 1);
	}
}

// added to the laser projectile
func OnHitObject(object target)
{
	if (!this.mine) return RemoveObject();
	this.mine->LaserHit(target);
}

// added to the laser projectile
func OnHitLandscape()
{
	// do nothing
}

// added to the laser projectile
func OnHitScan(int x_start, int y_start, int x_end, int y_end)
{
	if (this.mine)
	{
		this.mine->LaserLine(x_start, y_start, x_end, y_end);
	}
	RemoveObject();
}

func LaserLine(int x_start, int y_start, int x_end, int y_end)
{
	if (laser)
	{
		laser->Line(x_start, y_start, x_end, y_end)->Activate();
	}
}

func LaserHit(object target)
{
	// harmlos sein bis sie aktiviert ist
	if (GetAction() != "Active") return;
	if (GetActTime() - last_explosion < 10) return;
	

	// wenn sich das Ziel nicht bewegt, ignorieren
	var xdir = target->GetXDir();
	var ydir = target->GetYDir();
	if (xdir == 0 && ydir == 0) return;

	// ausrechnen in welche Richtung geschleudert wird
	var distance = 5;
	var angle = Angle(0, 0, target->GetXDir(), target->GetYDir()) + GetR();
	while (angle >= 360) angle -= 360;
	while (angle < 0) angle += 360;
	if (angle >= 180) distance *= -1;
	
	var x = target->GetX() + Cos(GetR(), distance) - GetX();
	var y = target->GetY() - Sin(GetR(), distance) - GetY();
	CreateObject(Dummy, x, y, NO_OWNER)->Explode(15);
	DoDamage(5);
	
	last_explosion = GetActTime();
}

func Destruction()
{
	if (laser) laser->RemoveObject();
	_inherited(...);
}

func MineExplosionRadius(){	return 10;}
func IsUpgradeable(id upgrade){ return false;}

func IsProjectileTarget(object projectile, object shooter)
{
	if (projectile.mine && projectile.mine == this) return false;
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
