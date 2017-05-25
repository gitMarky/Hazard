static const EMP_SHOCK_FOREVER = -1;

/**
 Adds an EMP shock effect to the target.
 
 @par time the time, in frames, until the effect should end.
           You can pass -1, which means that the effect will last forever,
           or until you call EMPShockEffect with the parameter "1" again.
 */
global func EMPShockEffect(int time)
{
	AssertObjectContext("EMPShockEffect()");

	var effect = EMPShocked();
	
	if (effect)
	{
		effect.Time = 0;    // reset the counter
		effect.time = time; // reset the time
	}
	else
	{
		AddEffect("EMPDamaged", this, 190, 5, nil, nil, time);
		this->~EMPShockStart();
	}
}

global func EMPShocked()
{
	AssertObjectContext("EMPShocked()");

	return GetEffect("EMPDamaged", this);
}

global func FxEMPDamagedStart(object target, proplist fx, int temp, int time)
{
	if (temp) return;

	fx.time = time;
	fx.color = target->GetClrModulation();
	
	var r = 200 * GetRGBaValue(fx.color, RGBA_RED) / 255;
	var g = 200 * GetRGBaValue(fx.color, RGBA_GREEN) / 255;
	var b = 200 * GetRGBaValue(fx.color, RGBA_BLUE) / 255;
	var a = GetRGBaValue(fx.color, RGBA_ALPHA);
	target->SetClrModulation(RGBa(r, g, b, a));
}

global func FxEMPDamagedTimer(object target, proplist fx, int time)
{
	if (fx.time != EMP_SHOCK_FOREVER && fx.time < time) return FX_Execute_Kill;

	// effects
	if (!(target->~Contained()))
	{
		var wdt = target->GetID()->GetDefWidth();
		var hgt = target->GetID()->GetDefHeight();
		target->CreateSparksEffect(2, nil, RandomX(-wdt / 2, wdt / 2), RandomX(-hgt / 2, hgt / 2));

		if (!Random(3))
		{
			var laser = CreateObject(LaserEffect, 0, 0, NO_OWNER);
			var laser_angle = Random(360);
			var laser_range = Sqrt(wdt * wdt / 4 + hgt * hgt / 4);

			var x_end = target->GetX() + Sin(laser_angle, laser_range);
			var y_end = target->GetY() - Cos(laser_angle, laser_range);

			laser->Line(target->GetX(), target->GetY(), x_end, y_end)
	 		->SetWidth(8)
	 		->SetLifetime(5)
	 		->Color(RGBa(255, 200, 0, 190))
	 		->Activate();			
		}
	}
}

global func FxEMPDamagedAdd(object target, proplist fx, string new_effect_name, int new_effect_timer, time)
{
	fx.time = Max(fx.time, time);
}

global func FxEMPDamagedEffect(string new_effect_name, object target, proplist fx, int new_effect_number)
{
	if (new_effect_name == "EMPDamaged")
		return -2;
}

global func FxEMPDamagedStop(object target, proplist fx)
{
	target->SetClrModulation(fx.color);
	target->~EMPShockEnd();
}
