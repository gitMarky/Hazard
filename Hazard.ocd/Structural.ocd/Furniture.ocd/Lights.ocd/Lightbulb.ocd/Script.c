local bulb;

func Initialize()
{
	bulb = CreateObject(BULB);
	bulb->Init(this, 50);
}

func SetCableLength(int length)
{
	bulb->SetCableLength(length);
	return this;
}

func Destruction()
{
	if (bulb) bulb->RemoveObject();
}

func GetLight()
{
	return bulb;
}

func Serialize(array extra) // TODO: Implement saving object
{
//	_inherited(extra);
//	extra[GetLength(extra)] = Format("Set(%d)", bulb->LocalN("length"));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
