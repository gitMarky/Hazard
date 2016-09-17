local top;


func Set(int strength, int angle_top, int angle_base)
{
	SetR(angle_base);
	if (!top)
	{
		top = CreateObject(JPTP, 0, 0, GetOwner());
		top->SetAction("Attach", this);
	}
	top->SetR(angle_top);
	top->SetStrength(strength);
	top.Plane = this.Plane - 1;
}


func SaveScenarioObject(proplist props)
{
	if (!_inherited(...))
		return false;
	
	if (GetR())
		props->AddCall("Set", this, "Set", top->GetStrength(), top->GetR(), GetR());
	else
		props->AddCall("Set", this, "Set", top->GetStrength(), top->GetR());
	
	return true;
}

