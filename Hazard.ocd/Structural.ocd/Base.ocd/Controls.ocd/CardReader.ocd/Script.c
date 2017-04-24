/*-- Keycard-Terminal --*/


local card_id, target, locked;


public func IsContainer() { return true; }

local MaxContentsCount = 1;

protected func RejectCollect(id itemid, object item)
{
	if (ContentsCount()) return true; // already has a card?
	return !CheckCard(item);
}

public func Ejection(object item)
{
	locked = true; // lock if someone takes the keycard
	return _inherited(item, ...);
}


func CheckCard(object keycard)
{
	if (!keycard) return false;
	
	if (!(keycard->~IsKeycard()))
	{
		Sound("CommandFailure1");
		return false;
	}

	if (HasCorrectCode(keycard))
	{
		Sound("Beep");
		CreateLEDEffect(RGB(0, 255, 0), 5, -7, nil, 50);
	}
	else
	{
		// die falsche... :(
		Sound("Error");
		CreateLEDEffect(RGB(255, 0, 0), 5, -7, nil, 50);
	}
}

func OperateCardReader(object user)
{
	var keycard = Contents();
	
	if (!keycard) // try to pick the right one from the inventory
	{
		var keycards = FindObjects(Find_Container(user), Find_Func("IsKeycard"));
		
		for (var card in keycards)
		{
			if (HasCorrectCode(card))
			{
				keycard = card;
				Collect(keycard);
				break;
			}
		}
	}
	
	// operate the switch?
	
	if (locked || !keycard)
	{
		Sound("CommandFailure1");
		user->Message("$Keycard$");
		return false;
	}
	else
	{
		// it's the right one! // TODO: use switch library once it exists
		if (target)
			target->~Access();
	}
}


func HasCorrectCode(object keycard)
{
	return keycard->GetKeyNumber() & card_id;
}


func CreateKeyCard()
{
	var keycard = CreateObject(KCRD, 0, 0, GetOwner());
	keycard->SetKeyNumber(card_id);
	return keycard;
}


func Set(object target, int number)
{
	card_id = number;
	this.target = target;
	locked = true;
}

/* Serialisierung */

// TODO: implement saving mechanism
//func Serialize(array extra)
//{
//	if (target)
//		extra[GetLength(extra)] = [Format("Set(Object(%%d),%i)", card_id), target];
//}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// interaction

func IsInteractable(object user){	return true;}


// Adapt appearance in the interaction bar.
public func GetInteractionMetaInfo(object clonk)
{
	var info;
	if (target) info = target->~GetInteractionMetaInfo(this); 
	return info ?? { Description = "$Control$", IconName = nil, IconID = GetID() };
}

// Called on player interaction.
public func Interact(object user)
{
	if (!IsInteractable(user)) return true;
	return OperateCardReader(user);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
