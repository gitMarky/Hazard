#appendto Cloud

func Initialize()
{
	_inherited(...);
	rain = 960;
	mode = CLOUD_ModeRaining;
}

// Instant full evaporation
func Evaporation() 
{
	rain = 960;
	mode_time = 0;
}

func MoveCloud()
{
	// stay in place
}

func RainDrop()
{
	_inherited(...);
	return false; // this way the cloud will rain forever
}
