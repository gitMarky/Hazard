#appendto RelaunchContainerEx

/**
 Callback when the contained crew is relaunched.
 This happens after the crew has left the container and
 before the container is removed. 
 */
public func OnRelaunchCrew(object crew)
{
	crew->~AddSpawnEffect(crew->GetColor());
}