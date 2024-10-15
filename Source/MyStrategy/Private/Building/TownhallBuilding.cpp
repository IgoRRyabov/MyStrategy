#include "Building/TownhallBuilding.h"
#include "GameData.h"

void ATownhallBuilding::AddResourse(int value)
{
	Resourse += value;
	if(Resourse > MaxResourse) Resourse = MaxResourse;
	TypeBuild = TownHall;
}

void ATownhallBuilding::BeginPlay()
{
	Super::BeginPlay();
}
