local base, bulb;

func Connect(object base, object bulb)
{
	this.base = base;
	this.bulb = bulb;
	
	SetPosition(base->GetX(), base->GetY());
	
	Update();
}

func Update()
{
	var r = -Angle(base->GetX(), base->GetY(), bulb->GetX(), bulb->GetY());
	if (r < 0 && r > -180)
		r -= 2;

	var xoff = 0;
	var yoff = 0;
	var d = ObjectDistance(base, bulb);
	
	var fsin = Sin(r, 1000), fcos = Cos(r, 1000);
	SetObjDrawTransform
	(
		+fcos / 2,
		+fsin * d,
		(1000 - fcos) * xoff - fsin * yoff,
		-fsin / 2,
		+fcos * d,
		(1000 - fcos) * yoff + fsin * xoff
	);
}

func NoSerialize() // TODO: implement properly
{
	return !false;
}

