
global func HelpMessage(string message, object target, a, b, c, d, e, f, g, h)
{
	if (!this)
	{
		FatalError("This function has to be called from object context.");
	}

	if (GetPlrExtraData(GetOwner(), "Hazard_NoHelpMsg"))
	{
		target->PlayerMessage(GetOwner(), message, a, b, c, d, e, f, g, h);
	}
}

global func InfoMessage(string message, object target, a, b, c, d, e, f, g, h)
{
	if (!this)
	{
		FatalError("This function has to be called from object context.");
	}

	target->PlayerMessage(GetOwner(), message, a, b, c, d, e, f, g, h);
}
