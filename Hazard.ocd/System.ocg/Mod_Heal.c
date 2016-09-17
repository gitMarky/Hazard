/**
	Heals the object over time for /amount/ HP.
	Calling the function multiple times results in faster healing (as opposed to longer healing).
*/
global func Heal(int amount, int rate)
{
	AssertObjectContext();

	// Add effect.
	var fx = this->AddEffect("HealingOverTime", this, 1, rate ?? 36);
	fx.healing_amount = amount;
	fx.done = 0;
	return fx;
}
