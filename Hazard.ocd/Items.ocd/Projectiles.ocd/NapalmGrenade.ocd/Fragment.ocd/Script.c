#include Grenade_Normal

local explode_delay;

func OnLaunched()
{
	explode_delay = RandomX(50, 90);
	SetGraphics(Format("%d", RandomX(1, 4)), Grenade_Cluster_Fragment);
	SetLightRange(10, 30);
	SetLightColor(FIRE_LIGHT_COLOR);
	_inherited(...);
}

func Hit()
{
	Detonate();
}

func ExplodeDelay()
{
	return explode_delay;
}


func Detonate()
{
	if (!exploded)
	{
		var flames = 8;
		var flame_angle = 180;

		for(var i = 0; i < flames ; ++i)
		{
		    flame_angle += 360 / flames + RandomX(-30, 30);
		    var strength = RandomX(30,40);
			var x = +Cos(flame_angle, strength);
			var y = -Sin(flame_angle, strength);
		    
			var flame = CreateObject(Projectile_Flame, x / 10,  y / 10, GetController());

			flame->Shooter(user)
					->Weapon(this.weapon_ID)
					->DamageAmount(this.damage)
	 	            ->DamageType(this.damage_type)
			        ->Velocity(15)
					->Range(PROJECTILE_Range_Infinite)
					->Lifetime(40);
	
			flame->Launch(Random(360), nil);
		}
		
		Sound("Fire::Inflame");
		RemoveObject();
	}
}

func IsProjectileTarget()
{
	return false;
}
