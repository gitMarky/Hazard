#appendto Environment_Configuration

/**
 In Hazard the configuration of spawn points is not possible.
 @return bool {@c false}.
 */
public func CanConfigureSpawnPoints()
{
	return false;
}

public func GetGameConfigurationIcon()
{
	return Icon_Configuration;
}
