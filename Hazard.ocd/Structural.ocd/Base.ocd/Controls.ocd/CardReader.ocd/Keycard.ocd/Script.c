/*-- Keycard --*/


local keynumber;

protected func Initialize()
{
	var look = Random(5)+1;
	if (look != 1)
		SetGraphics(Format("%d", look));
}

public func SetKeyNumber(int number)
{
    keynumber = number;
}

public func GetKeyNumber()
{
    return keynumber;
}

public func IsKeycard()
{
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = true;
