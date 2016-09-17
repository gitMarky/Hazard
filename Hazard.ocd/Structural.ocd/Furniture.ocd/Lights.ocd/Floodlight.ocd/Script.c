local bulb;

func Initialize()
{
	bulb = CreateObject(FLHH, 0, 0, NO_OWNER);
	bulb->ConnectTo(this);
}

//func ControlLeft()
//{
//	bulb->TurnLeft();
//}
//
//func ControlRight()
//{
//	bulb->TurnRight();
//}
//
//func ControlUp()
//{
//	bulb->Stop();
//}
//
//func ControlDigDouble()
//{
//	bulb->Switch();
//}

func GetLight()
{
	return bulb;
}

func SetRotation(int rotation, int rotation_base)
{
	rotation = BoundBy(rotation, -90, 90);
	SetR(rotation_base ?? 0);

	bulb->SetR(rotation + GetR());
	bulb->RotateLight();
	return this;
}

// Crane may not grab me! // TODO: why does this exist, if it is not identified as being grabbable by the crane?
func NoCrane()
{
	return true;
}

local Name = "$Name$";
