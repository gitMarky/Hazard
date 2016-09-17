
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// internal properties

local closed;       // offen?
local lock;         // Tür ist verschließbar (geht nicht automatisch auf)
local destroyed;    // zerstört
local maxdmg;

static const DOOR_LOCK_Locked = 0;
static const DOOR_LOCK_OpenManually = 1;
static const DOOR_LOCK_OpenAutomatically = 2;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// settings

func GetMaxDamage(){	return maxdmg;}
func IsDestroyable(){	return maxdmg != -1;}
func SetMaxDamage(int max){	maxdmg = max;}

func Lock(bool auto_open)
{
	lock = DOOR_LOCK_OpenManually;
	if (auto_open)
		lock = DOOR_LOCK_OpenAutomatically;
		
	return this;
}

func Unlock()
{
	lock = DOOR_LOCK_Locked;
	return this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// callbacks

func OnDestroyed(){}
func OnOpen(){}
func OnClose(){}


func Initialize()
{
	closed = true;
	Unlock();
	SetMaxDamage(50); // default
	CreateEffect(IntCheckOpen, 1, 5);

	UpdateTransferZone();
}

func UpdateTransferZone()
{
	SetTransferZone(-15, -GetObjWidth() / 2, 30, GetObjWidth());
}

func ControlTransfer(object obj, int x, int y)
{
	if (lock && closed) return false;
	
	var dir = 1;
	if (obj->GetX() < GetX())
		dir = -1;
	
	if (closed) return obj->AddCommand("MoveTo", nil, GetX() + 10 * dir, GetY());
	
	// door is open -> move through \o/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// interface: add a lock

// TODO
func SetKeycardLock(int passcode, int dir, bool autoclose)
{
//	var x = (dir * 2 - 1) * (GetObjWidth() / 2 + 15);
//	var keycard = CreateObject(LKEY, x, 0, GetOwner());
//	keycard->Set(this, passcode);
//	Lock(autoclose);
//	return keycard;
}

func SetPasscodeLock(int code, int dir, bool autoclose)
{
//	var x = (dir * 2 - 1) * (GetObjWidth() / 2 + 10);
//	var passcode = CreateObject(PKEY, x, 0, GetOwner());
//	passcode->Set(this, code);
//	Lock(autoclose);
//	return passcode;
}

func SetSwitchLock(int dir, bool autoclose)
{
	var x = (dir * 2 - 1) * (GetObjWidth() / 2 + 8);
	var switch = CreateObject(SWTH, x, 0, GetOwner());
	switch->SetSwitchTarget(this);
	Lock(autoclose);
	return switch;
}

func Access()
{
	if (closed)
	{
		Open();
	}
	else if (lock != DOOR_LOCK_OpenAutomatically)
	{
		Close();
	}
}

func SwitchOn()
{
	Open();
}

func SwitchOff()
{
	Close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// interface: open and close

func Open()
{
	if (destroyed || !closed) return;

	OnOpen();
	closed = false;
}

func Close()
{
	if (destroyed || closed) return;

	OnClose();
	closed = true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// more callbacks

func Damage(int change, int by_player)
{
	if (GetDamage() > GetMaxDamage() && IsDestroyable() && !destroyed)
	{
		SetSolidMask(0);
		RemoveEffect("IntCheckOpen", this);
		destroyed = true;
		OnDestroyed();
	}
}

func IsProjectileTarget()
{
	if (!closed || destroyed)
		return false;
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// door control: automatically open and close the door

local IntCheckOpen = new Effect
{
	Timer = func ()
	{
		return Target->CheckOpen();
	},
};

func CheckOpen()
{
	// do nothing if destroyed
	if (destroyed) return FX_Execute_Kill;
	// do nothing if locked
	if (lock == DOOR_LOCK_OpenManually) return;
	
	// close again
	if (!closed)
	{
		if (!SomeonesApproaching()) Close();
	}
	// or open it
	else if (!lock)
	{
		if (SomeonesApproaching()) Open();
	}
}

func SomeonesApproaching()
{
	var people = [];
	
	for (var i = 0; i < 2; ++i)
	{
		people = FindObjects
		(
			Find_InRect(-35 * i, -GetObjHeight() / 2, 35, GetObjHeight()),
			Find_OCF(OCF_Alive),
			Find_Not(Find_Func("IsAlien"))
		);
		if (GetLength(people) > 0)
		{
			return true;
		}
	}
	return false;
}

func IsSideDoor(){	return true;}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// interaction with switches, key cards, etc.

// Adapt appearance in the interaction bar.
public func GetInteractionMetaInfo(object switch)
{
	var description = "$CloseDoor$";
	if (closed) description ="$OpenDoor$";
	return { Description = description, IconName = nil, IconID = this->GetID() };
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// save object

func Serialize(array extra) // TODO: properly implement saving a door
{
//	extra[GetLength(extra)] = Format("SetMaxDamage(%d)", maxdmg);
//	if (lock)
//		extra[GetLength(extra)] = Format("Lock(%v)", lock == DOOR_LOCK_OpenAutomatically);
//	if (destroyed)
//	{
//		extra[GetLength(extra)] = "SetSolidMask()";
//		extra[GetLength(extra)] = "RemoveEffect(\"CheckOpen\",this(),0)";
//		extra[GetLength(extra)] = "LocalN(\"destroyed\")=true";
//	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
