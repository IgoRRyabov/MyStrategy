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
		auto const res = PlayerController->MouseRaycast(ECC_GameTraceChannel4);
		auto const location = res.Location;

		if (ObjectBuilding)
		{
			ObjectBuilding->SetCollisionProfile("OverlapAll");
			ObjectBuilding->SetActorLocation(location);
			if (PlayerController->isMousePressed)
			{
				if(ObjectBuilding->CanBuild())
				{
					EndBuilding();
				}else
				{
					ErrorBuild();
				}
			}
		}
	}
}

void UBuildComponent::Building()
{
	ObjectBuilding = GetWorld()->SpawnActor<AObjectForBuilding>(ObjectForBuild);

	// Активировать режим строительства
	isBuild = true;
}

void UBuildComponent::ErrorBuild()
{
	if (!ObjectBuilding) return;
	ObjectBuilding->Destroy();
	isBuild = false;
}

void UBuildComponent::EndBuilding()
{
	if (!ObjectBuilding) return;
	ObjectBuilding = nullptr;
	isBuild = false;
}
