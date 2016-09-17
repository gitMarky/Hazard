#include Projectile_LaserBeam

func OnHitObject(object target)
{
	if (target) PushBack(ExcludedFromHitCheckCall(), target); // prevent hitting this object again
	SetHitCheckCallCounter(); // allow hitting other objects
}

func OnHitCheckCall(proplist hitcheck)
{
	var x_end = hitcheck.oldx;
	var y_end = hitcheck.oldy;
	var x_start = GetX();
	var y_start = GetY();
	UpdateHitCheckCoordinates(x_start, y_start, x_end, y_end);
	SetHitCheckCallCounter(); // so that further hitchecks are issued
	
	if (x_start != x_end && y_start != y_end)
	{
		SetPosition(x_end, y_end);
		DoHitCheckCall();
	}
}

func ShouldRemoveOnHit(){ return false;}
