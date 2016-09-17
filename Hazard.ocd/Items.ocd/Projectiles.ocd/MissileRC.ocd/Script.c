
#include Projectile_Missile

local turn;

public func Acceleration() { return 2; }
public func ExplodeDelay() { return 180; }
public func MaxSpeed() { return 75; }

func TurnSpeed(){	return 15; }


func Accelerate()
{
	// r drag
	if (!(GetActTime() % 3))
		SetRDir(GetRDir() * 14 / 15);
}

func ControlLeft()
{
	SetRDir(-TurnSpeed());
}

func ControlRight()
{
	SetRDir(TurnSpeed());
}

func ControlDown()
{
	SetRDir(0);
}

func ControlUp()
{
	SetRDir(0);
}

func ControlThrow()
{
	Hit();
}

func ControlDig()
{
	ReleaseControl();
}

func ReleaseControl()
{
	SetPlrView(GetShooter()->GetOwner(), GetShooter());
	SetCursor(GetShooter()->GetOwner(), GetShooter(), true);
}

func ActivateControl(object user)
{
	this.user = user;
	if (GetShooter() == GetCursor(GetOwner()))
	{
		SetPlrView(GetShooter()->GetOwner(), this);
		this->SetPlrViewRange(100);
		SetCursor(GetShooter()->GetOwner(), this, true);
	}
}
