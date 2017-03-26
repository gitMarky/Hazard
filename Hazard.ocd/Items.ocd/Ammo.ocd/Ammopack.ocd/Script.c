#include Library_Stackable

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ammo definitions

public func IsAmmoPacket() { return true; }
public func AmmoID()       { return Ammo_Standard; }
public func AmmoCount()    { return 100; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// stackable definitions

public func MaxStackCount() { return AmmoID()->MaxAmmo(); }
public func InitialStackCount() { return AmmoCount(); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// add ammo


/*
 Callback from the spawn point.
 
 @par spawn_point This spawn point contains the object.
 @par into This object tries to collect the object.

 @return true if the object should not be collected.
 */
func RejectCollectionFromSpawnPoint(object spawn_point, object into)
{
	var transferrable = GetTransferrableAmmo(into);
	
	// Collect ammo only if something is transferrable
	if (transferrable == 0)
	{
		return true;
	}
	else
	{
		return _inherited(spawn_point, into, ...);
	}
}

func Entrance(object clonk)
{
	var self = this;
	_inherited(clonk, ...);
	
	if (self) TransferAmmoTo(clonk);
}

protected func ControlUse(object clonk, int x, int y)
{
	TransferAmmoTo(clonk);
	return true;
}

public func TransferAmmoTo(object clonk)
{
	if (!clonk)
	{
		FatalError("This function expects an object that is not nil!");
	}

	if (!(clonk->~IsAmmoManager())) return;
	
	var transferrable = GetTransferrableAmmo(clonk);

	// not if he has too much already
	if (transferrable == 0)
	{
		clonk->InfoMessage("$NotMoreAmmo$", clonk, AmmoID());
	}
	else
	{
		// message
		clonk->HelpMessage("$Collected$", clonk, transferrable, AmmoID());
		// transfer the stuff
		clonk->DoAmmo(AmmoID(), transferrable);
		// update this object
		DoStackCount(-transferrable);
	}
}


func GetTransferrableAmmo(object clonk)
{
	if (clonk->~IsAmmoManager())
	{
		var available_ammo = GetStackCount();
		var remaining_ammo = AmmoID()->MaxAmmo() - clonk->~GetAmmo(AmmoID());

		return Min(remaining_ammo, available_ammo);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = true;

protected func Hit()
{
	Sound("Hits::GeneralHit?");
}
