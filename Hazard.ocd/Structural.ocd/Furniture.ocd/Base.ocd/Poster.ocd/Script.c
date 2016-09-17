
func Initialize()
{
	SetAction("Poster");
}

func SetRandom()
{
	var columns = 4;
	var random = Random(15);
	var x = random % columns;
	var y = 0;
	while (random > columns) { columns -= 1; y += 1; }

	Set(x, y);
}

func Set(int x, int y)
{
	SetPhase(x);
	SetDir(y);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Poster = {
	Prototype = Action,
	Name = "Poster",
	Directions = 4,
	Length = 4,
	Delay = 0,
	X = 0,
	Y = 0,
	Wdt = 46,
	Hgt = 38,
	FacetBase = 0,
	NextAction = "Hold",
},

};
