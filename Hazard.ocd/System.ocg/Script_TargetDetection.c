
global func FindMostValuableTarget(int distance, object shooter, object origin)
{
	AssertObjectContext("FindMostValuableTarget()");

	return GetMostValuableTarget(FindProjectileTargets(distance, shooter, origin));
}

global func GetMostValuableTarget(targets)
{
	var target;
  
	// choose most valuable target
	for(var t in targets)
	{
		if (!target)
		{
			target = t;
			continue;
		}
		if(t->GetValue() > target->GetValue())
		{
			target = t;
			break;
		}
	}

	return target;
}

global func FindProjectileTargets(int distance, object shooter, object origin)
{
	AssertObjectContext("FindProjectileTargets()");
	shooter = shooter ?? this;
	origin = origin ?? this;

	return FindObjects(Find_Distance(distance),
					   Find_NoContainer(),
					   Find_Layer(GetObjectLayer()),
					   Find_Or(Find_Func("IsProjectileTarget", origin, shooter), Find_OCF(OCF_Alive)),
					   Find_PathFree(origin),
					   Find_Exclude(origin),
					   Find_Exclude(shooter),
					   Sort_Distance());
}
