#include "BuildComponent.h"
#include "BuildingWidget.h"
#include "BasePlayerController.h"
#include "BuildingWidget.h"
#include "UnitData.h"

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
	
}

void UBuildComponent::StartBuilding(FName name)
{
	UE_LOG(LogTemp, Log, TEXT("Trace hit Base Unit Character : %s"), *name.ToString());
}


void UBuildComponent::Building()
{
	
}

void UBuildComponent::CancerBuilding(AObjectForBuilding* ObjectBuild)
{
	
}
