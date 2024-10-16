#include "Interface/EnterInterface.h"

void IEnterInterface::InterfaceOverlapBegin(AActor* OtherActor)
{
}

void IEnterInterface::InterfaceOverlapEnd(AActor* OtherActor)
{
}

bool IEnterInterface::AddUnits(AActor* unit)
{
	return false;
}

void IEnterInterface::MinusUnits(AActor* unit)
{
}
