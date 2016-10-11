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

func Entrance(object clonk)
{
	var self = this;
	_inherited(...);
	
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
	
	var available_ammo = GetStackCount();
	var remaining_ammo = AmmoID()->MaxAmmo() - clonk->~GetAmmo(AmmoID());

	var transferrable = Min(remaining_ammo, available_ammo);

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
