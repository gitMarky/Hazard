#appendto Rule_TeamAccount

public func GetGameConfigurationIcon(int team)
{
	if (team == 1) return Icon_TeamLeft;
	if (team == 2) return Icon_TeamRight;
	return Icon_Teams;
}
