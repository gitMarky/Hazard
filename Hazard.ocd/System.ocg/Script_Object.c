global func GetPhysicalEnergy()
{
	AssertObjectContext("GetPhysicalEnergy()");
	
	return this->GetEnergy() * 1000;
}
