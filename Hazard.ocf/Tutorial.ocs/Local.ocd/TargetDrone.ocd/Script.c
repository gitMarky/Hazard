local drop, move, move_precision;
local xpos, ypos, x, y, xdir, ydir, xrange, yrange;
local exploded;

func Hit()
{
	Detonate();
}

func Detonate()
{
	if (GetEffect("ObjFade", this)) exploded = true;
	if (exploded) return;
	exploded = true;

	Sound("Fire::Blast3");

	var target;
	if (target = FindObject(Find_ID(Target), Find_ActionTarget(this)))
		target->Damage();

	Explode(20);
}

func Damage()
{
	Detonate();
}

func IsMachine()
{
	return true;
}

func EMPShock()
{
	move = 0;
	SetAction("Falling");
	EMPShockEffect(EMP_SHOCK_FOREVER);
}

func Initialize()
{
	SetAction("Fly");
	FadeIn();
	var targ = CreateObject(Target, 0, 0, 1);
	targ->SetAction("Attach", this);
	
	SetLightRange(50, 30);
}

func JobDone()
{
	if (drop)
	{
		CreateObject(drop);
		drop = nil;
		Detonate();
	}
	else
	{
		FadeOut(25, true);
		SetAction("Falling");
	}
}

func StartMoving(int Dirx, int Diry, int Rangex, int Rangey, int xstart, int ystart, int precision)
{
	var adjustment = 10;
	move_precision = precision ?? 10;
	xdir = Dirx; // * move_precision / 10;
	ydir = Diry; // * move_precision / 10;
	xrange = Rangex * adjustment;
	yrange = Rangey * adjustment;
	x = xstart * adjustment;
	y = ystart * adjustment;
	xpos = GetX() * move_precision;
	ypos = GetY() * move_precision;
	move = 1;
}

func Move()
{
	if (!move) return;

	// sort-of deceleration for a more natural looking movement
	var div_x = 1;
	var div_y = 1;
	if (Abs(x) >= xrange/2 && Abs(xdir) > 2) div_x = 2;
	if (Abs(y) >= yrange/2 && Abs(ydir) > 2) div_y = 2;

	// move
	x += xdir / div_x;
	y += ydir / div_y;

	// change direction at the bounds, prevent overshooting
	if (Abs(x) >= xrange)
	{
		xdir *= -1;
		x = BoundBy(x, -xrange, +xrange);
	}
	if (Abs(y) >= yrange)
	{
		ydir *= -1;
		y = BoundBy(y, -yrange, +yrange);
	}

	// update
	SetPosition((xpos + x) / move_precision, (ypos + y) / move_precision);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BorderBound = 7;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = 
{
	Fly =
	{
		Prototype = Action,
		Name = "Fly",
		Procedure = DFA_FLOAT,
		Directions = 2,
		FlipDir = 1,
		Length = 1,
		Delay = 1,
		X = 0,
		Y = 0,
		Wdt = 17,
		Hgt = 15,
		NextAction = "Fly",
		StartCall = "Move"
	},
	Falling = 
	{
		Prototype = Action,
		Name = "Falling",
		Procedure = DFA_NONE,
		Directions = 2,
		FlipDir = 1,
		Length = 1,
		Delay = 1,
		X = 0,
		Y = 0,
		Wdt = 17,
		Hgt = 15,
		NextAction = "Falling"
	}
};
