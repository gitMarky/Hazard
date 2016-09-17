#include Grenade_Cluster


func CastClusters()
{
	for (var i = RandomX(5, 6);  i > 0; --i)
	{
		var fragment = CreateObject(Grenade_Napalm_Fragment, 0, 0, GetController());
		
		fragment->Shooter(user)
				->Weapon(this.weapon_ID)
				->DamageAmount(this.damage)
 	            ->DamageType(this.damage_type)
		        ->Velocity(15)
				->Range(PROJECTILE_Range_Infinite);

		fragment->Launch(Random(360), nil);
	}
}


func ExplodeDelay() { return 40;}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
