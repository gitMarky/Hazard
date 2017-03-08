
static const ANIM_BACKFLIP_Length = 26;

// Called when CON_Left/Right/Up/Down controls are issued/released
// Return whether handled
func ObjectControlMovement(int plr, int ctrl, int strength, bool release, bool repeat)
{
	if (!this) return false;
	
	// movement is only possible when not contained
	if (Contained()) return false;
	
	// this is for controlling movement with Analogpad
	if (!release)
		if (strength != nil && strength < CON_Gamepad_Deadzone)
			return true;
	
	// save previous control upon releasing a button
	var double = false;
	if (release)
	{
		RemoveEffect("IntPrevCtrl", this);
		AddEffect("IntPrevCtrl", this, 1, 10, this, nil, ctrl);
	}
	else
	{
		var fx = GetEffect("IntPrevCtrl", this);
		if (fx)
		{
			if (fx.ctrl == ctrl)
			{
				double = true;
			}
			RemoveEffect("IntPrevCtrl", this);
		}
	}
	
	if (ControlJetpack(ctrl, double) || ControlAgility(ctrl, double))
	{
		// do nothing!
		return true;
	}
	else
	{
		return _inherited(plr, ctrl, strength, release, repeat, ...);
	}
}


func ControlJetpack(int ctrl, bool double)
{
	if (!double) return false;
	
	var jetpack = this->~HasGear(Gear_Jetpack);
	if (!jetpack) return false;
	
	if (ctrl == CON_Up)
	{
		return jetpack->ControlUpDouble(this);
	}
	else if (ctrl == CON_Left)
	{
		return jetpack->ControlLeftDouble(this);
	}
	else if (ctrl == CON_Right)
	{
		return jetpack->ControlRightDouble(this);
	}
	else
	{
		return false;
	}
}


func ControlAgility(int ctrl, bool double)
{
	if (!CanUseAgility()) return false;
	if (!double) return false;
	
	var jumping = this->~IsJumping() || GetAction() == "Dive";
	var walking = this->~IsWalking() && Abs(GetXDir(100)) > (3 * this.ActMap.Walk.Speed / 4); // only if you are fast, otherwise there is a strange unwanted backflip when moving normally
	var scaling = false;
	var ydir = nil, strength = nil;

	if (jumping)
	{
		strength = -30;
	}
	else if (scaling)
	{
		strength = -40;
		ydir = -60;
	}
	
	var may_flip = walking || jumping || scaling;

	if (ctrl == CON_Left)
	{
		if (may_flip)
		{
			if(GetDir() == DIR_Left) ForwardFlip(strength, false, ydir);
			else BackFlip(strength, false, ydir);
			return true;
		}
	}
	else if (ctrl == CON_Right)
	{
		if (may_flip)
		{
			if(GetDir() == DIR_Right) ForwardFlip(strength, false, ydir);
			else BackFlip(strength, false, ydir);
			return true;

		}
	}
	else if (ctrl == CON_Up)
	{
		if (jumping && GetYDir() <= 5) return ExtraJump();
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

func GetRelativeJumpStrength()
{
	return this.ActMap.Jump.Speed * 100 / GetID().ActMap.Jump.Speed;
}

func ExtraJump()
{
	PreventAgility();
	var jump = GetRelativeJumpStrength();
	SetYDir(-40 * jump / 100);
	SetXDir(GetXDir() / 2);

	SetAction("WallJump");
	var side = "L";
	if(GetDir() == DIR_Left) side = "R";
	PlayAnimation(Format("JumpWall.%s", side), CLONK_ANIM_SLOT_Movement, Anim_Linear(0, 0, GetAnimationLength("JumpWall.L"), 8*5, ANIM_Hold), Anim_Linear(0, 0, 1000, 5, ANIM_Remove));
}

func CanUseAgility()
{
	return !GetEffect("PreventAgility", this);
}

func PreventAgility()
{
	AddEffect("PreventAgility", this, 111, 5, this);
}

func FxPreventAgilityTimer()
{
	if(this->~IsJumping() || GetAction() == "Dive" || GetAction() == "Backflip")
	{
		return FX_OK;
	}
	else
	{
		return FX_Execute_Kill;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////

protected func BackFlip(int strength, bool no_jump_calculation, int ydir)
{
	OnStartBackFlip();
	AddFlipBoost(!GetDir(), strength, no_jump_calculation, ydir);
	PreventAgility();
}

protected func ForwardFlip(int strength, bool no_jump_calculation, int ydir)
{
	if (!strength && !ydir)
	{
		strength = -20;
		ydir = -45;
	}
	OnStartForwardFlip();
	AddFlipBoost(GetDir(), strength, no_jump_calculation, ydir);
	PreventAgility();
}

func AddFlipBoost(int dir, int strength, bool no_jump_calculation, int ydir)
{
	dir = dir * 2 - 1;
	ydir = ydir ?? -24;


	var jump;
	if (no_jump_calculation)
	{
		jump = strength;
	}
	else
	{
		jump = GetRelativeJumpStrength();
		jump = BoundBy(jump + strength, 0, 300);
	}
	SetXDir(40 * dir * jump / 100);
	SetYDir(ydir * jump / 100);

	// TODO: fix this in the original animations script in OC: it should be easier to create new dust particles, avoid duplicated code
	if (GetMaterialVal("DigFree", "Material", GetMaterial(0,10)))
	{
		var clr = GetAverageTextureColor(GetTexture(0,10));
		var particle_dir = GetDir() * 2 - 1;
		
		var particles =
		{
			Prototype = Particles_Dust(),
			R = (clr >> 16) & 0xff,
			G = (clr >> 8) & 0xff,
			B = clr & 0xff,
		};
		CreateParticle("Dust", PV_Random(particle_dir * -2, particle_dir * -1), 8, PV_Random(particle_dir * 2, particle_dir * 1), PV_Random(-2, -5), PV_Random(36, 2 * 36), particles, 6);
	}
}

func OnStartAnyFlip()
{
	Sound("Clonk::Movement::Roll");
	if (GetAction() != "Backflip") SetAction("Backflip");
}

func OnStartBackFlip()
{
	OnStartAnyFlip();
	// TODO: play animation in reverse
	PlayAnimation("KneelRoll", CLONK_ANIM_SLOT_Movement, Anim_Linear(0, 0, 1500, ANIM_BACKFLIP_Length, ANIM_Remove), Anim_Linear(0, 0, 1000, 5, ANIM_Remove));
}

func OnStartForwardFlip()
{
	OnStartAnyFlip();
	PlayAnimation("KneelRoll", CLONK_ANIM_SLOT_Movement, Anim_Linear(0, 0, 1500, ANIM_BACKFLIP_Length, ANIM_Remove), Anim_Linear(0, 0, 1000, 5, ANIM_Remove));
}

func FxIntPrevCtrlStart(object target, proplist fx, temp, ctrl)
{
	if (temp) return;
	fx.ctrl = ctrl;
}
