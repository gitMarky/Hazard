#include Projectile_TankBullet

local launch_dir = 0;

func SetLaunchDir(int dir)
{
	launch_dir = dir;
	return this;
}

func OnLaunched()
{
	velocity_x = RandomX(4, 6) * 10;
	velocity_y = launch_dir * RandomX(4, 6) * 10;
	SetXDir(velocity_x);
	SetYDir(velocity_y);
	SetR(-20 * launch_dir);
	return true;
}
