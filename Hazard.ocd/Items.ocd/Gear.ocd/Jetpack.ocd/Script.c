#include Gear_Basic

//wieviel Zeit bis zum nächsten Boost
local timeleft;
local jetpack_user;
local jetpack_graphics;

func GetGearType(){	return GEAR_Backpack;}
func IsEquipment(){	return true;} // TODO: no idea what this is used for

func Definition(id def)
{
	def.MeshTransformation = Trans_Mul(Trans_Rotate(45, 0, 1, 0), Trans_Rotate(10, 0, 0, 1), Trans_Scale(600, 800, 700));
	def.PictureTransformation = Trans_Mul(Trans_Rotate(45, 0, 1, 0), Trans_Rotate(-20, 1, 0, 0), Trans_Rotate(20, 0, 0, 1), Trans_Scale(750, 1000, 875));
}


func Initialize()
{
	_inherited(...);
	SetGraphics(nil, BackpackGraphic);
	SetMeshMaterial("JetpackTexture");
}


func GearEffect(object user)
{
	jetpack_user = user;
	//Places a backpack onto the clonk
	//jetpack_graphics = jetpack_user->AttachMesh(this, "skeleton_body", "main", Trans_Mul(Trans_Rotate(180, 1, 0, 0), Trans_Scale(700, 600, 700), Trans_Translate(4000, -1000, 0)));
	jetpack_graphics = jetpack_user->AttachMesh(this, "skeleton_body", "main", Trans_Mul(Trans_Rotate(180, 1, 0, 0), Trans_Scale(800, 600, 800), Trans_Translate(4000, -1000, 0)));
}

func GearEffectReset(object user)
{
	if(jetpack_graphics)
	{
		jetpack_user->DetachMesh(jetpack_graphics);
		jetpack_graphics = nil;
	}

	jetpack_user = nil;
}

func ControlUpDouble(object user)
{
	if (IsReadyToUse(user))
	{
		FlyUpward(user);
		return true;
	}
}

func ControlRightDouble(object user)
{
	if (IsReadyToUse(user) && (user->GetDir() == DIR_Right))
	{
		FlyForward(user);
		return true;
	}
}


func ControlLeftDouble(object user)
{
	if (IsReadyToUse(user) && (user->GetDir() == DIR_Left))
	{
		FlyForward(user);
		return true;
	}
}


func IsReadyToUse(object user)
{
	return user->~HasGear(Gear_Jetpack) && ReadyToFly(user);

}

func FlyUpward(object user)
{
	SetJetpackAction(user);
	user->SetXDir(GetXDir() / 3 - 10 + 20 * user->GetDir());
	user->SetYDir(GetYDir() / 3 - 60);
	
	StartToFly(user);
}

func FlyForward(object user)
{
	SetJetpackAction(user);
	user->SetXDir(user->GetXDir() / 3 - 50 + 100 * user->GetDir());
	user->SetYDir(user->GetYDir() / 3 - 15);
	
	StartToFly(user);
}

func StartToFly(object user)
{
	AddEffect("JetpackDelay", user, 170, 5, this);
	AddEffect("Thrust", user, 170, 1, this);
	timeleft = 15;
}


func ReadyToFly(object user)
{
	// User is flying?
	if (user->~IsJumping() || user->GetAction() == "Dive")
	{
		// Are we not delayed?
		if (!GetEffect("JetpackDelay", user))
			return true;
	}
	return false;
}

func FxThrustStart(object user, proplist fx)
{
	Sound("Weapon::FlameThrower::Flamer", nil, nil, nil, +1);
}

func FxThrustTimer(object user, proplist fx, int timer)
{
	if (timer > 35) return FX_Execute_Kill;
	
	/* copied most of the code from the missile: */
	var dist = Distance(0, 0, user->GetXDir(), user->GetYDir());
	var angle = Angle(0, 0, user->GetXDir(), user->GetYDir());
	var maxx = +Sin(angle, dist / 10);
	var maxy = -Cos(angle, dist / 10);
	var ptrdist = 66;
	
	for (var i = 0; i < dist; i += ptrdist)
	{
		
		var x = -maxx * i / dist + user->GetX() - 4 * (user->GetDir() * 2 - 1);
		var y = -maxy * i / dist + user->GetY() + 3;
		
		var rand = RandomX(-30, 30);
		var xdir = +Sin(angle + rand, -20);
		var ydir = -Cos(angle + rand, -20);
		
		if (timer < 22)
		{
			CreateParticle("Thrust", x, y, xdir / 2, ydir / 2, PV_Random(10, 15),
			{
				Prototype = Particles_ThrustColored(255, 200, 200),
				Size = PV_Random(8, 12),
			});
		}
		CreateParticle("Smoke2", x, y, xdir, ydir, PV_Random(30, 40),
		{
			Prototype = Particles_ThrustColored(220, 200, 180),
			Size = PV_Random(12, 16),
		});
	}
}

func FxThrustStop(object user, proplist fx)
{
	user->Sound("Weapon::FlameThrower::Flamer", nil, nil, nil, -1);
}

func FxJetpackDelayTimer(object user, proplist fx)
{
	timeleft--;
	if (timeleft <= 0)
		return -1;
} 


func FxJetpackDelayStop(object user, proplist fx)
{
}


func SetJetpackAction(object user)
{
	if (GetActMapVal("Name", "JetpackFlight", user->GetID()))
		user->SetAction("JetpackFlight");
}

// properties

local Name = "$Name$";
local Description = "$Description$";
