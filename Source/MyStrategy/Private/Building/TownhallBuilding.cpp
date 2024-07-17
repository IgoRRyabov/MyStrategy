#include "Building/TownhallBuilding.h"
#include "GameData.h"

void ATownhallBuilding::AddResourse(int value)
{
	Resourse += value;
	if(Resourse > MaxResourse) Resourse = MaxResourse;
	TypeBuild = ETypeBuild::TownHall;
}

void ATownhallBuilding::BeginPlay()
{
	Super::BeginPlay();

	SetMaxCountUnit(5);
}
