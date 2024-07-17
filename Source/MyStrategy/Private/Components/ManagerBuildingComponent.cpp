#include "Components/ManagerBuildingComponent.h"


UManagerBuildingComponent::UManagerBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UManagerBuildingComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UManagerBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UManagerBuildingComponent::AddCountBuilding(ETypeBuild TypeBuilding)
{
	SumCountBuildint++;
	switch (TypeBuilding)
	{
		case ETypeBuild::TownHall:
			TownHallCountBuildint++;
			break;
		default:
			break;
	}

	UE_LOG(LogTemp, Log, TEXT("SumCountBuildint : %d"), SumCountBuildint);
	UE_LOG(LogTemp, Log, TEXT("TownHallCountBuildint : %d"), TownHallCountBuildint);
}

void UManagerBuildingComponent::Test()
{
	UE_LOG(LogTemp, Log, TEXT("Test"));
}
