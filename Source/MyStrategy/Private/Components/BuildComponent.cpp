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

}

void UBuildComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(isBuild)
	{
		//CanSelectUnit = false;
		auto const HitMouse = PlayerController->MouseRaycast(ECollisionChannel::ECC_GameTraceChannel1);
		
		LocationBuild = HitMouse.Location;
		
		if(BuildingRef)
		{
			BuildingRef->SetActorLocation(LocationBuild);
			if(LeftMouseClick)
			{
				UE_LOG(LogTemp, Log, TEXT("Cancel Building Start!! "));

				if(BuildingRef->IsOverlapObj())
				{
					CancerBuilding();
				}
				else
				{
					Building();
				}
			}
		}
	}
	
}

void UBuildComponent::StartBuilding(FName name)
{
	LeftMouseClick = false;
	isBuild = false;
	//UE_LOG(LogTemp, Log, TEXT("Trace hit Base Unit Character : %s"), *name.ToString());
	const auto Test = ObjectDataHandle.DataTable->FindRow<FBuildingObjectData>(name, " ");
	if(!isBuild)
	{
		BuildObj = Test->BuildingObjectRef;
		if(!BuildingRef)
		{
			BuildingRef = GetWorld()->SpawnActor<AObjectForBuilding>(BuildObj);
			//BuildingRef->SetBuildingResourse(Test->ResourseForBuilding);
			BuildingRef->ResourseForBuilding = Test->ResourseForBuilding;
		}
		isBuild = true;
	}
}


void UBuildComponent::Building()
{
	BuildingRef->SetIsBuilding(true);
	BuildingRef->Building();
	BuildingRef->OnNewBuilding.AddDynamic(PlayerController->GetManagerBuildingComponent(), &UManagerBuildingComponent::AddCountBuilding);
	BuildingRef->OnUpdateResouse.AddDynamic(PlayerController->GetManagerResoursesComponent(), &UManagerResoursesComponent::UpdateResourse);
	BuildingRef->SetPlayerController(PlayerController);
	ResetBuildingValue();
}

void UBuildComponent::CancerBuilding()
{
	BuildingRef->Destroy();
	ResetBuildingValue();
	//UE_LOG(LogTemp, Log, TEXT("Cancel Building End!! "));
}

void UBuildComponent::ResetBuildingValue()
{
	isBuild = false;
	//CanSelectUnit = false;
	LeftMouseClick = false;
	BuildingRef = nullptr;
}
