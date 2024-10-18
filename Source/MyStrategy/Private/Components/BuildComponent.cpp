#include "BuildComponent.h"
#include "BuildingWidget.h"
#include "BasePlayerController.h"
#include "BuildingWidget.h"
#include "ManagerBuildingComponent.h"
#include "GameData.h"

UBuildComponent::UBuildComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	BuildingWidget = CreateDefaultSubobject<UBuildingWidget>("Building Widget");
}

void UBuildComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<ABasePlayerController>(GetOwner());

	check(ObjectForBuild);
}

void UBuildComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isBuild)
	{
		auto const res = PlayerController->MouseRaycast(ECC_GameTraceChannel4);
		auto const location = res.Location;

		ObjectBuild->SetActorLocation(location);
		ObjectBuild->SetCollisionPorfile("OverlapAll");
	}
}

void UBuildComponent::Building()
{
	ObjectBuild = GetWorld()->SpawnActor<AObjectForBuilding>(ObjectForBuild);
	isBuild = true;
}
