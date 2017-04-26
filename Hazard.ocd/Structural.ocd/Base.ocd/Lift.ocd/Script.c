/*-- Lift --*/

#include Library_LiftPlate

// Lokale Variable: Feuerfarbe :')
local UpperY, LowerY, WaitComDir, WaitY;
local rgb;

func Initialize()
{
	_inherited();
	
	AddTimer(this.Sparks, 4);
	rgb = {R = RandomX(40, 160), G = RandomX(40, 160), B = RandomX(40, 160)};
}

func SparksParticles(int size)
{
	return {
		Prototype = Particles_Magic(),
		BlitMode = GFX_BLIT_Additive,
		R = rgb.R, G = rgb.G, B = rgb.B,
		Size = size ?? 5,
	};
}

func Sparks()
{
	var ydir = GetYDir() / 4;

	CreateParticle("Magic", 0, -20, PV_Random(-1, 1), PV_Random(ydir -1, ydir +1), 20, SparksParticles(RandomX(5, 13)));
	CreateParticle("Magic", 0, +20, PV_Random(-1, 1), PV_Random(ydir -1, ydir +1), 20, SparksParticles(RandomX(5, 13)));
}

func FlareUp()
{
	CreateParticle("Magic", 0, -20, PV_Random(-4, 4), PV_Random(-2, -4), 20, SparksParticles(RandomX(13, 21)), 3);
}

func FlareDown()
{
	CreateParticle("Magic", 0, +20, PV_Random(-4, 4), PV_Random(+2, +4), 20, SparksParticles(RandomX(13, 21)), 3);
}


func SpeedToY()
{
	var result = _inherited(...);

	if (GetYDir() < 0)
		FlareDown();
	else
		FlareUp();
		
	return result;
}

func Rectangle_Unstuck()
{
	return Find_InRect(-25, 0, 50, 25);
}

/* Serialisierung */

func Serialize(array extra) // TODO: Saving mechanism
{
	extra[GetLength(extra)] = Format("SetYTop(%d)", UpperY);
	extra[GetLength(extra)] = Format("LocalN(\"rgb\")=%d", rgb);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
