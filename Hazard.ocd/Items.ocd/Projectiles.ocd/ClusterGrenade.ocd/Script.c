#include Grenade_Normal

func Hit()
{
	Detonate();
}

func OnDetonation()
{
	CastClusters();
	_inherited(...);
}

func CastClusters()
{
	var dist = 4;
	for (var i = RandomX(8, 11);  i > 0; --i)
	{
		var launch_angle = Random(360);
		var fragment = CreateObject(Grenade_Cluster_Fragment, Sin(launch_angle, dist), -Cos(launch_angle, dist), GetController());

		fragment->Shooter(user)
				->Weapon(this.weapon_ID)
				->DamageAmount(this.damage)
 	            ->DamageType(this.damage_type)
		        ->Velocity(30)
				->Range(PROJECTILE_Range_Infinite);

		fragment->Launch(launch_angle, nil);
	}
}

func ExplodeDelay() { return 50;}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
