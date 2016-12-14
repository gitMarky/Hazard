
local startX, startY;
local timer, holder;
local respawn;

// TODO: make bomb carry heavy? this solves most problems (shifting)

func RejectShift() // TODO: this is not actually used by anyone
{
	return true;
}

func IsAlwaysCollectable() // TODO: this is not actually used by anyone
{
	return true;
}

// Get timer
func GetBombTimer()
{
	return timer;
}

func IsAtHome()
{
	return (Abs(GetX() - startX) < 20)
	    && (Abs(GetY() - startY) < 20)
	 	&& (GetOwner() == NO_OWNER);
}

func Init(int x, int y)
{
	startX = x;
	startY = y;
	Exit();
	SetPosition(startX, startY);
	SetOwner(NO_OWNER);
	holder = nil;
	timer = 1000;
	respawn = true;
	CreateEffect(BombFlight, 20, 1);
	// remove potentially existing other effects
	var effect = GetEffect("BombTimer", this);
	if (effect)
		RemoveEffect(nil, this, effect);
}


func IsBouncy(){ return true; } // affected by jump pads


protected func ControlUse(object user, int x, int y)
{
	LaunchBomb(user, 6, Angle(0, 0, x, y));
	return true;
}


/**
 Shoots the bomb.

 @par speed Speed of the bomb.
 @par angle Angle.
*/
func LaunchBomb(object user, int speed, int angle)
{
	var dir = user->GetDir() * 2 - 1;
	
	// adjust angle
	angle = BoundBy(angle + user->GetYDir() * dir, -360, 360);
	// calculate speed
	var xdir = +Sin(angle, speed);
	var ydir = -Cos(angle, speed);
	
	var radius = 5;
	var x = +Sin(angle, radius);
	var y = -Cos(angle, radius);
	
	// effect
	Sound("Goals::BombingRun::BombShot");
	
	var user_xdir = user->GetXDir();
	var user_ydir = user->GetYDir();	

	CreateParticle("Smoke2", PV_Random(x - 5, x + 5), PV_Random(y - 5, y + 5), PV_Random(user_xdir, user_xdir + xdir / 4), PV_Random(user_ydir, user_ydir + ydir / 4), PV_Random(15, 25),
	{
		Prototype = Particles_BombSmoke(),
	}, 10);

	CreateParticle("Thrust", x, y, PV_Random(user_xdir-2, user_xdir+2), PV_Random(user_ydir-2, user_ydir+2), PV_Random(20, 30),
	{
		Prototype = Particles_BombThrust(),
	}, 5);
	
	// TODO: this is not actually used by anyone
	//var no = AddEffect("CollectionException", this, 1, 5);
	//no.except = user;
	Exit(x + xdir / 10, y + ydir / 10, xdir, xdir, ydir, 0);
	DoThrustEffect();
}

func Destruction()
{
	if (respawn)
	{
		var bomb = CreateObject(GetID(), 0, 0, NO_OWNER);
		bomb->Init(startX, startY);
		GameCallEx("OnBombReturned");
		Log("$Returned$");
		Sound("Goals::BombingRun::BombReset", true);
	}
}

func ForceRemove() // so that the bomb can be removed by the rules object.
{
	respawn = false;
	RemoveObject();
}

func Departure()
{
	GameCallEx("OnBombLost");
}

func ReturnToSpawn()
{
	var eff;
	while (eff = GetEffect("BombFlight", this))
		RemoveEffect(nil, this, eff);
	SetSpeed();
	Init(startX, startY);
	GameCallEx("OnBombScored");
}

func Entrance(object into)
{
	// Wer sie sammelt, besitzt. Quasi.
	if (into->GetOwner() != NO_OWNER)
		SetOwner(into->GetOwner());
	
	// does not need to be removed
	//var eff;
	//while (eff = GetEffect("BombFlight", this))
	//	RemoveEffect(nil, this, eff);
	
	// Timer starten
	if (into->GetOCF() & OCF_CrewMember)
	{
		var desired_timer = 1000;
		if (into == holder) desired_timer = timer;

		CreateEffect(BombTimer, 1, 1, into, desired_timer);
		GameCallEx("OnBombTaken", into);
	}
}


func Hit(int xdir, ydir)
{
	if (GBackSolid(-6, 0) || GBackSolid(6, 0) || GBackSolid(-2, 4) || GBackSolid(2, 4))
		SetXDir(-(xdir / 20));
	if (GBackSolid(-4, 3) || GBackSolid(4, 3) || GBackSolid(0, 6) || GBackSolid(0, -6))
		SetYDir(-(ydir / 20));
	DoThrustEffect();
	DoHitEffect();
	return _inherited(xdir, ydir, ...);
}


func OnBouncedByJumpPad(object jumppad)
{
	DoThrustEffect();
}


func Particles_BombSmoke()
{
	return {
		Prototype = Particles_ThrustColored(100, 100, 255),
		Size = PV_Random(8, 14),
		BlitMode = GFX_BLIT_Additive,
	};
}

func Particles_BombThrust()
{
	return {
		Prototype = Particles_ThrustColored(10, 10, 255),
		Size = 10,
		BlitMode = GFX_BLIT_Additive,
	};
}

func DoHitEffect()
{
	CreateParticle("Smoke2", PV_Random(-5, +5), PV_Random(-5, +5), PV_Random(0, GetXDir() / 4), PV_Random(0, GetYDir() / 4), PV_Random(15, 25),
	{
		Prototype = Particles_BombSmoke(),
	}, 10);

	CreateParticle("Thrust", 0, 0, PV_Random(-2, +2), PV_Random(-2, +2), PV_Random(20, 30),
	{
		Prototype = Particles_BombThrust(),
	}, 5);
}

func DoThrustEffect()
{
	var duration = 15;
	var effect = GetEffect("BombThrust", this) ?? CreateEffect(BombThrust, 1, 3, duration);
	effect.counter = duration;
}

/**
 Flight effect.
 */
local BombFlight = new Effect
{
	Start = func()
	{
		this.BombTime = 0;
		this.BombLight = CreateObject(Dummy, 0, 0, NO_OWNER);
		this.BombLight->AddLightAmbience(200);
		this.BombLight->SetLightColor(HSL(0, 255, 255));
		return true;
	},

	Timer = func(int time)
	{
		// light effects
		if (this.BombLight) this.BombLight->SetLightColor(HSL(BoundBy(Abs(Sin(time * 2, 120)), 0, 120), 128, 200));
		
		if (!(Target->Contained()))
		{
			if (Target->GetOwner() != NO_OWNER) // someone threw the bomb somewhere
			{
				var explode_time = 36 * 30;
				// countdown reached? explode
				if (++this.BombTime > explode_time)
				{
					Target->Explode(25);
					return;
				}
				// effects for countdown, a "bip" that goes faster the closer we get to the countdown
				if ((explode_time % (explode_time - this.BombTime)) == 0)
				{
					Target->CreateLEDEffect(RGB(255, 0, 0), 0, -3, 8, 20);
					Target->Sound("Weapon::Bip");
				}
			}
			if (this.BombLight)
			{
				this.BombLight->SetPosition(this.Target->GetX(), this.Target->GetY());
			}
		}
		else // reset bomb if it is contained
		{
			if (this.BombTime) this.BombTime = 0;
			if (this.BombLight)	this.BombLight->RemoveObject();
		}
		return true;
	},

	Stop = func()
	{
		if (this.BombLight) this.BombLight->RemoveObject();
	},
};

/*---- Effect for the bomb timer that gets displayed above the carrier ----*/

local BombTimer = new Effect
{
	Start = func(int temp, object new_holder, int new_timer)
	{
		if (temp) return;
		if (!(Target->Contained())) return FX_Execute_Kill;
		
		Target.holder = new_holder;
		Target.timer = new_timer;
	},
	
	Timer = func ()
	{
		if (!Target->Contained()) return FX_Execute_Kill;
		Target.timer--;
		if (Target.timer <= 0) return Target->Explode(25);
		var angle = 90 * Target.timer / 1000;
		
		Target->Contained()->InfoMessage("<c %x>%d</c>", Target->Contained(), RGB(Cos(angle, 255), Sin(angle, 255), 0), Target.timer);
	},
};

/*---- Effect for bouncing somewhere ----*/

local BombThrust = new Effect
{
	Start = func(int temp, int new_timer)
	{
		if (temp) return;
		
		this.countdown = new_timer;
		this.counter = new_timer;
	},
	
	Timer = func (int time)
	{
		if (this.counter < 0) return FX_Execute_Kill;

		var xdir = Target->GetXDir();
		var ydir = Target->GetYDir();

		var size = Sin(90 * this.counter / this.countdown, 10); // get smaller the closer you get to the timeout

		Target->CreateParticle("Smoke2", 0, 0, PV_Random(xdir / 4, xdir / 3), PV_Random(ydir / 4, ydir / 3), PV_Random(15, 25),
		{
			Prototype = Target->Particles_BombSmoke(),
			Size = size,
		}, 3);
		
		this.counter -= 1;
	},
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = true;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

// TODO: actions do not seem to be in use
local ActMap = {
Fly = {
	Prototype = Action,
	Name = "Fly",
	Procedure = DFA_NONE,
	Length = 1,
	Delay = 0,
	X = 0,
	Y = 0,
	Wdt = 10,
	Hgt = 11,
	NextAction = "Fly",
},

};
