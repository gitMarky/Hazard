
func IsProjectileTarget() { return true; }

func Initialize()
{
	SetOwner(1);
}

func Damage()
{
	Sound("Objects::Arrow::HitGround");

	var particles = {Prototype = Particles_WoodChip(), size = PV_Random(30, 55)};

	var x = PV_Random(GetX()- 3, GetX() + 3);
	var y = PV_Random(GetY()- 3, GetY() + 3);

	var vx = PV_Random(-20, 20);
	var vy = PV_Random(-20, 0);
	
	var lifetime = PV_Random(36 * 7, 36 * 15);

	// cast red and white particles
	Global->CreateParticle("Splinter", x, y, vx, vy, lifetime, particles, 30);
	Global->CreateParticle("Splinter", x, y, vx, vy, lifetime, {Prototype = particles, R = 255, G = 0, B = 0}, 30);

	var self = this;

	if (GetActionTarget())
 		GetActionTarget()->JobDone();
	if (self)
		self->RemoveObject();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Attach = {
	Prototype = Action,
	Name = "Attach",
	Procedure = DFA_ATTACH,
	Length = 1,
	Delay = 0,
	X = 0,
	Y = 0,
	Wdt = 13,
	Hgt = 13,
},

};
