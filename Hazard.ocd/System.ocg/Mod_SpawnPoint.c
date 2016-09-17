#appendto SpawnPoint

// the particle effect

local effect_angle;

func SpawnPointEffectInterval(){ return 2;}

func EffectTimer(int time)
{
	effect_angle = (effect_angle + 5) % 360;
	
	for (var index = 0; index < GetLength(spawn_object); ++index)
	{
		SetObjDrawTransform(1000, 0, 0, 0, 1000, Sin(effect_angle, 3000) - 2000, GetOverlay(index));
	}

	if (!Random(4)) CreateParticle("Magic", PV_Random(-5, 5), PV_Random(0, 5), 0, -5, PV_Random(30, 35),
	{
		Prototype = Particles_Magic(),
		R = 210, G = 210, B = 255,
		Alpha = PV_Linear(155, 0),
		Size = 2,
		BlitMode = GFX_BLIT_Additive,
	}, 1);
}

// collection of an object

private func EffectCollect(object item, object clonk)
{
	_inherited(item, clonk, ...);
	
	// load weapons
	if (item && item->~IsHazardWeapon())
	{
		var firemode = item->GetFiremode();
		if (firemode)
		{
			item->DoAmmo(firemode.ammo_id, firemode.ammo_load);
		}
	}
}
