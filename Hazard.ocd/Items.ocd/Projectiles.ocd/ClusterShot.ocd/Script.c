#include Projectile_Bullet

protected func Initialize()
{
	//SetObjectBlitMode(GFX_BLIT_Additive, );
	SetGraphics(nil, GetID(), 1, GFXOV_MODE_ExtraGraphics, nil, GFX_BLIT_Additive);
}



public func OnHitLandscape()
{
	Detonate();
}

public func HitObject() // this is not "OnHitObject" on purpose, because we want the object not to do damage twice
{
	Detonate();
}

public func OnHitNothing()
{
	Detonate();
}

private func Detonate()
{
	Explode(damage);
}

