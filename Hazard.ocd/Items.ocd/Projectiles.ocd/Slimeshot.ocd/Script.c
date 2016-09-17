#include Library_Projectile

func OnLaunched()
{
	if (!damage) damage = 5 + Random(5);
	AddAlienFlareEffect(200);
	SetObjectBlitMode(GFX_BLIT_Additive);
}


func OnHitLandscape()
{
	CreateObject(SlimeGlob, 0, 0, GetOwner())->~Glob2Ground(this.damage);
	RemoveObject();
}


func OnHitObject(object target, proplist effect)
{
	CreateObject(SlimeGlob, 0, 0, GetOwner())->~AttachTo(target);
	RemoveObject();
}
