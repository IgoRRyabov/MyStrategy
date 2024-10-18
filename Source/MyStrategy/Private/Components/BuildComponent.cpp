#include "BuildComponent.h"
#include "BuildingWidget.h"
#include "BasePlayerController.h"

UBuildComponent::UBuildComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	BuildingWidget = CreateDefaultSubobject<UBuildingWidget>("Building Widget");
}

void UBuildComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<ABasePlayerController>(GetOwner());

}

void UBuildComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isBuild)
	{
		auto const res = PlayerController->MouseRaycast(ECC_GameTraceChannel2);
		auto const location = res.Location;

		if (res.GetActor())
			UE_LOG(LogTemp, Log, TEXT("BuildRaycast hit : %s"), *res.GetActor()->GetName());
		
		if (ObjectBuilding)
		{
			ObjectBuilding->SetCollisionProfile("OverlapAll");
			ObjectBuilding->SetActorLocation(location);
		}
	}
}

void UBuildComponent::Building()
{
	ObjectBuilding = GetWorld()->SpawnActor<AObjectForBuilding>(ObjectForBuild);

	// Активировать режим строительства
	isBuild = true;
}