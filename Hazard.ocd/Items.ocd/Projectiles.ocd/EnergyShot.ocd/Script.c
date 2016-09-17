#include Projectile_Bullet

protected func Initialize()
{
	SetObjectBlitMode(GFX_BLIT_Additive);
}

private func OnLaunch()
{
	SetAction("Travel");
	SetLightColor(RGB(70, 50, 255));
	SetLightRange(30, 30);
}

private func OnLaunched()
{
	CreateTrail(0, 0);
	if (trail)
	{
		trail->SetGraphics("Laser");
		trail->SetAction("Laser");
	}
}


private func ProjectileColor(int time)
{
	var progress = 100 * time / lifetime;
	var value = Max(0, 127 - progress);

	return RGBa(127, value, 255, Max(0, 255 - progress * 2));
}

private func TrailColor(int time)
{
	return ProjectileColor(time);
}
