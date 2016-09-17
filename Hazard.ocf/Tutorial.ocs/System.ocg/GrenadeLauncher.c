#appendto Weapon_GrenadeLauncher

public func IsUpgradeable(id upgrade) { return false; }

func Initialize()
{
	_inherited(...);
	firemode_standard.condition = this.HasNoFragMode;
	firemode_fragmentation.condition = this.HasFragMode;
	firemode_emp.condition = this.HasEMPMode;
}

func HasNoFragMode(){ return !HasFragMode();}
func HasFragMode(){ return GetActiveSequence().seq_progress >= 16; }
func HasEMPMode(){ return GetActiveSequence().seq_progress >= 24; }

