#include "Components/ManagerBuildingComponent.h"

#include "BasePlayerController.h"


UManagerBuildingComponent::UManagerBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UManagerBuildingComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ABasePlayerController>(GetOwner());
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
	
	UE_LOG(LogTemp, Log, TEXT("SumCountBuilding : %d"), SumCountBuildint);
	UE_LOG(LogTemp, Log, TEXT("Type = %d, Count =  : %d"), TypeBuilding, *CountBuilding.Find(TypeBuilding));
}

void UManagerBuildingComponent::UpdateCountBuild(ETypeBuild type)
{
	PlayerController->GameStat.sumCountBuild++;
	
	UE_LOG(LogTemp, Log, TEXT("SumCountBuilding : %d"), PlayerController->GameStat.sumCountBuild);
	switch (type)
	{
	case ETypeBuild::Default :
		PlayerController->GameStat.countDefaultBuild++;
		UE_LOG(LogTemp, Log, TEXT("Type = DefaultBuild, Count =  : %d"), PlayerController->GameStat.countDefaultBuild);
		break;
	case ETypeBuild::TownHall :
		PlayerController->GameStat.countTownBuild++;
		UE_LOG(LogTemp, Log, TEXT("Type = TownHall, Count =  : %d"), PlayerController->GameStat.countTownBuild);
		break;
	}
}
