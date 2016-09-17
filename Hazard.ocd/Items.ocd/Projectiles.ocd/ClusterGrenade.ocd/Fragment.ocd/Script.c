#include Grenade_Normal

func OnLaunched()
{
	_inherited(...);
	SetGraphics(Format("%d", RandomX(1, 4)));
}

func Hit()
{
	Detonate();
}

func ExplodeDelay()
{
	return 220;
}

func IsProjectileTarget()
{
	return false;
}
