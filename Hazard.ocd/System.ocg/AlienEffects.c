
//global func AlienSplatter(int iSize, int iX, int iY, int iColor)
//{
//	// not on sky
//	if (GetMaterialVal("Density", "Material", GetMaterial(iX, iY)) != 0 || GetMaterial(iX, iY) == -1)
//		return;
//	
//	// behind everything (like the burn mark of the explosion)
//	var boom;
//	if (!ObjectCount(BOOM))
//	{
//		boom = CreateObject(BOOM, 0, 0, -1);
//	}
//	else
//	{
//		boom = FindObject(BOOM);
//	}
//	
//	var r = Random(360);
//	var xdir = Sin(r, 100);
//	var ydir = -Cos(r, 100);
//	CreateParticle("AlienSplatter", iX, iY, xdir, ydir, iSize * 5, iColor, boom, 1);
//}

//global func AlienBlood(int iSize, int iX, int iY, int iColor, object attach)
//{
//	
//	var rand = Random(360);
//	for (var i = 0; i < 5; ++i)
//	{
//		var size = iSize * RandomX(10, 20) / 15 * GetCon() / 100;
//		var angle = rand + i * RandomX(50, 80);
//		var xdir = Sin(angle, 100);
//		var ydir = -Cos(angle, 100);
//		var xoff = Sin(angle, iSize / 2 - 5);
//		var yoff = -Cos(angle, iSize / 2 - 5);
//		CreateParticle("AlienBlood", iX + xoff, iY + yoff, xdir, ydir, iSize * 5, iColor, attach);
//	}
//}

//global func AlienHive(int iSize, int iX, int iY, int iColor, object attach, bool foreground)
//{
//	
//	// not on sky
//	//if(GetMaterialVal("Density","Material",GetMaterial(iX,iY)) != 0
//	//   || GetMaterial(iX,iY) == -1) return();
//	
//	var boom;
//	// to which object (if any)
//	if (attach)
//		boom = attach;
//	else if (!foreground)
//	{
//		if (!ObjectCount(BOOM))
//			boom = CreateObject(BOOM, 0, 0, -1);
//		else
//			boom = FindObject(BOOM);
//	}
//	
//	var r = Random(360);
//	var xdir = Sin(r, 100);
//	var ydir = -Cos(r, 100);
//	CreateParticle("AlienHive", iX, iY, xdir, ydir, iSize * 5, iColor, boom, !foreground);
//}

/* Alienpartikel */

global func AddAlienFlareEffect(int size)
{
	if (!this)
	{
		FatalError("This function must be called from object context!");
	}
	
	AddEffect("AlienFlareEffect", this, 1, 1, nil, nil, size);
}

global func FxAlienFlareEffectStart(object target, proplist fx, int temp, int size)
{
	fx.size = size;
}

global func FxAlienFlareEffectTimer(object target, proplist fx, int time)
{
	var xdir = target->GetXDir() / 3;
	var ydir = target->GetYDir() / 3;
	
	if (!target->Contained()) CreateParticle(
		"FireSparkHazard",
		target->GetX(), target->GetY(),
		PV_Random(xdir -3, xdir + 3), PV_Random(ydir - 3, ydir + 3),
		PV_Random(20, 80),
		{
			Prototype = Particles_SmokeTrail(),
			R = 160, G = 255, B = 0,
			Size = PV_Random((fx.size - 100) / 25, (fx.size + 100) / 25),
			BlitMode = GFX_BLIT_Additive,
		}, 1);
}
