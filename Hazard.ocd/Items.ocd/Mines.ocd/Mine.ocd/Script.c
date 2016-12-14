#include Library_UpgradeableObject

local triggered;

static const MINE_PLACEMENT_Invalid = 0;
static const MINE_PLACEMENT_Wall = 1;
static const MINE_PLACEMENT_Background = 2;

public func HoldingEnabled() { return true; }

public func ControlUseStart(object user, int x, int y)
{
	var preview = GetMinePreview();
	if (!preview)
	{
		preview = CreateEffect(IntMinePreview, 1, 1, user);
	}
	return true;
}

public func RejectUse(object clonk)
{
	return !clonk->HasHandAction(false, false, true);
}


public func ControlUseHolding(object user, int x, int y)
{
	var preview = GetMinePreview();
	if (preview) preview->Update(x, y);
	return true;
}

public func ControlUseStop(object user, int x, int y)
{
	var preview = GetMinePreview();
	if (preview) preview->TryActivateMine(user, x, y);
	return true;
}

public func ControlUseCancel(object user, int x, int y)
{
	var preview = GetMinePreview();
	if (preview) preview->CancelActivateMine(user, x, y);
	return true;
}

func GetMinePreview()
{
	return GetEffect("IntMinePreview", this);
}

local IntMinePreview = new Effect
{
	Start = func (int temporary, object user)
	{
		this.mine_preview = this.mine_preview ?? CreateObject(Dummy);
		this.mine_preview.Visibility = VIS_Owner;
		this.mine_preview.Plane = 5000;
		this.mine_preview->SetOwner(user->GetOwner());
		this.mine_preview->SetGraphics(nil, Target->GetID(), 1, GFXOV_MODE_Object, nil, nil, Target);
		this.mine_user = user;
		this.mine_x = 0;
		this.mine_y = 0;
		this.mine_r = 0;
		this.mine_placement = MINE_PLACEMENT_Invalid;
		this.mine_ok = false;
		this.mine_progress = this.mine_preview->CreateProgressBar(GUI_PieProgressBar, Target->MinePlacementDelay(), 0, nil, user->GetOwner(), {x = 0, y = 0}, VIS_Owner, { size = 250, color = RGBa(150, 150, 150, 50)});
	},

	Timer = func (int time)
	{
		if (this.mine_preview)
		{
			if (this.mine_user)
			{
				this.mine_preview->SetPosition(this.mine_user->GetX() + this.mine_x, this.mine_user->GetY() + this.mine_y);
				Target->SetR(this.mine_r);
			}

			if (this.mine_progress && time <= Target->MinePlacementDelay() + 10)
			{
				//var mod = Min(255, 255 * time / Target->MinePlacementDelay());
				//var a = Min(100, 100 * time / Target->MinePlacementDelay());
				//this.mine_progress.color = BoundBy(255 - mod, mod, 0, 100 + a);
				this.mine_progress->SetValue(time);
				this.mine_progress->Update();
			}
			else
			{
				if (this.mine_progress) this.mine_progress->Close();
			}

			this.mine_ok = time >= Target->MinePlacementDelay() && this.mine_placement == MINE_PLACEMENT_Wall;
			var color;
			if (this.mine_ok)
			{
				color = RGBa(0, 255, 0, 128);
			}
			else
			{
				color = RGBa(255, 0, 0, 128);
			}
			this.mine_preview->SetClrModulation(color, 1);
		}
		else
		{
			return FX_Execute_Kill;
		}
	},
	
	Update = func (int x, int y)
	{
		var angle = Angle(0, 0, x, y);
		var dist = Distance(0, 0, x, y);
		var pos = Target->GetWall(angle, dist);

		var p1 = Target->GetWall(angle - 5, dist + 2);
		var p2 = Target->GetWall(angle + 5, dist + 2);

		var r;
		if (p1 && p2)
		{
			r = Angle(p1.X, p1.Y, p2.X, p2.Y) + 90;
		}
		
		this.mine_x = pos.X;
		this.mine_y = pos.Y;
		this.mine_r = r;
		this.mine_placement = pos.Placement;
	},
	
	TryActivateMine = func (object user, int x, int y)
	{
		if (this.mine_ok)
		{
			Target->Exit();
			Target->SetPosition(this.mine_user->GetX() + this.mine_x, this.mine_user->GetY() + this.mine_y);
			Target->SetR(this.mine_r);
			Target->ActivateMine(user);
		}
		else // cancel
		{
			this->CancelActivateMine(user, x, y);
		}
	},
	
	CancelActivateMine = func (object user, int x, int y)
	{
		RemoveEffect(nil, Target, this);
	},
	
	Destruction = func ()
	{
		if (this.mine_preview) this.mine_preview->RemoveObject();
		if (this.mine_progress) this.mine_progress->Close();
	},
};

func ActivateMine(object user)
{	
	SetOwner(user->GetOwner());

	this.Collectible = false;
	
	SetVertex(1, 1, 2, 2);
	SetVertex(2, 1, 2, 2);
	SetAction("Activate");

	CreateObject(Helper_MineFlag, 0, 0, GetOwner())->Set(this);
	return true;
}


/**
 returns true if there is a wall in direction in which "clonk" looks
 and puts the offset to the wall into "xo, yo" - looking from the clonk
 */
func GetWall(int angle, int max_dist)
{
	// initialize with defaults
	max_dist = Min(max_dist ?? MinePlacementMaxDist(), MinePlacementMaxDist());
	var place_x = +Sin(angle, max_dist);
	var place_y = -Cos(angle, max_dist);

	var solid = false;

	// hit a wall?
	for (var dist = MinePlacementMinDist(); dist <= max_dist; dist++)
	{
		var x = +Sin(angle, dist);
		var y = -Cos(angle, dist);
		if (GBackSolid(x, y))
		{
			place_x = x;
			place_y = y;
			solid = true;
			break;
		}
	}
	
	var placement = MINE_PLACEMENT_Invalid;
	
	if (!solid)
	{
		if (GetMaterial(place_x, place_y) != Material("Sky") // not a wall, but not sky?
		&& !GBackSemiSolid(place_x, place_y)) // never place in liquids!
		{
			placement = MINE_PLACEMENT_Background; // must be a background wall
		}
	}
	else
	{
		placement = MINE_PLACEMENT_Wall;
	}
	
	// save everything as a proplist :)
	return {
		X = place_x,
		Y = place_y,
		Placement = placement,
	};
}


func Warning()
{	
	var a = 190;
	if (GetAction() == "Active")
		a = 95 + 120 * GetDamage() / MaxDamage();
	else
		Sound("Weapon::Bip");

	CreateLEDEffect(RGBa(255, 64, 0, a), Sin(GetR(), WarningDist()), -Cos(GetR(), WarningDist()), 6); 
}

func OnActive()
{
	SetClrModulation(RGBa(255, 255, 255, 55));
}

func Check()
{
	var obj;
	for (obj in FindProjectileTargets(MineExplosionRadius(), this, this)) 
	{
		// only moving objects
		if (obj->GetXDir() || obj->GetYDir() || obj->GetAction() == "ScaleLadder")
		{
			// except mines
			if (!(obj->~IsMine()))
			{
				DoDamage(MaxDamage()); // trigger!
				return;
			}
		}
	}
}


func Damage(int change)
{
	if (GetAction() != "Idle")
		SetClrModulation(RGBa(255, 255, 255, 55 + 200 * GetDamage() / MaxDamage()));
	if (GetDamage() >= MaxDamage())
		Trigger();
}

func Trigger()
{
	if (triggered) return;
	triggered = true;
	Sound("Weapon::BipBipBip");
	ScheduleCall(this, this.Triggered, MineExplosionDelay());
}

func Triggered()
{
	Explode(45);
}

func RejectEntrance()
{
	if (GetAction() != "Idle") return true;
	return false;
}

func MaxDamage(){	return 30;}
func MineExplosionRadius(){	return 30;}
func MineExplosionDelay(){	return 10;}
func MinePlacementDelay(){ return 30;}   // hold 'use' this many frames before the mine can be used
func MinePlacementMinDist(){ return 5;}  // mine must be placed at least this far from the clonk
func MinePlacementMaxDist(){ return 20;} // mine must be placed at most this far from the clonk
func WarningDist(){ return 3;}
func IsProjectileTarget(){	return true;}

func IsEquipment(){	return true;}
func IsMine(){	return true;}

/* Upgrade */

public func IsUpgradeable(id upgrade)
{
	if (HasUpgrade(upgrade)) return false;

	return upgrade == Upgrade_Laser || upgrade == Upgrade_WeaponPart;
}

public func GetUpgradeDescription(id upgrade)
{
	if (upgrade == Upgrade_Laser)
	{
		return "$UpgradeToLaser$";
	}
	else if (upgrade == Upgrade_WeaponPart)
	{
		return "$UpgradeToWeaponPart$";
	}
}

public func OnUpgrade(id upgrade)
{
	var clonk = Contained();
	if(upgrade == Upgrade_Laser)
	{
		if (clonk) clonk->~HelpMessage("$UpgradedToLaser$", clonk);
		ChangeDef(LMIN);
	}
  	else if(upgrade == Upgrade_Slime)
  	{
		if (clonk) clonk->~HelpMessage("$UpgradedToWeaponPart$", clonk);
		ChangeDef(SMIN);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = true;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Activate = {
	Prototype = Action,
	Name = "Activate",
	Procedure = DFA_NONE,
	Length = 5,
	Delay = 20,
	FacetBase = 1,
	NextAction = "Active",
	EndCall = "OnActive",
	PhaseCall = "Warning",
},

Active = {
	Prototype = Action,
	Name = "Active",
	Procedure = DFA_NONE,
	Length = 4,
	Delay = 5,
	FacetBase = 1,
	NextAction = "Active",
	EndCall = "Warning",
	PhaseCall = "Check",
},

};
