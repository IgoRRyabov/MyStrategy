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

	if(!CountBuilding.Find(TypeBuilding))
		CountBuilding.Add(TypeBuilding);
	CountBuilding.Add(TypeBuilding, *CountBuilding.Find(TypeBuilding) + 1);
	
	//UE_LOG(LogTemp, Log, TEXT("SumCountBuilding : %d"), SumCountBuildint);
	//UE_LOG(LogTemp, Log, TEXT("Type = %d, Count =  : %d"), TypeBuilding, *CountBuilding.Find(TypeBuilding));
}
