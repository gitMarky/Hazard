#include Library_ConfigurableRule

global func NoAmmo()
{
  return ObjectCount(Find_ID(Rule_NoAmmo));
}

// Can be chosen by the chooser
public func GameConfigIsChoosable()
{
    return false;
}

public func GameConfigConflictingRules()
{
    return [/*Rule_WeaponChoice*/];
}

local Name = "$Name$";
local Description = "$Description%";
