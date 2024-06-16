#include "BuildComponent.h"
#include "BasePlayerController.h"


UBuildComponent::UBuildComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	//StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Building Mesh");
}

void UBuildComponent::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = Cast<ABasePlayerController>(GetOwner());
	
	UE_LOG(LogTemp, Log, TEXT("Build Component parent : %s"), *PlayerController->GetName());
	
}

void UBuildComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(isBuild)
	{
		auto const HitMouse =  PlayerController->MouseRaycast(ECollisionChannel::ECC_GameTraceChannel1);//ECollisionChannel::ECC_BuildChannel);
		// if(HitMouse.GetActor())
		// {
		// 	UE_LOG(LogTemp, Log, TEXT("Location to Build Object : %s"), *HitMouse.GetActor()->GetName());
		// }
		// else
		// {
		// 	UE_LOG(LogTemp, Log, TEXT("Error Trace Engine Channel"));
		// }
		LocationBuild = HitMouse.Location;
		if(!BuildObject)
		{
			BuildObject = GetWorld()->SpawnActor<AObjectForBuilding>(ObjectForBuilding);
		}
		if(BuildObject)
		{
			BuildObject->SetActorLocation(LocationBuild);
			
		}
		
	}else if(BuildObject)
	{
		BuildObject = nullptr;
	}
}

void UBuildComponent::StartBuilding()
{
	if(isBuild)
		isBuild = false;
	else
	{
		isBuild = true;
		Building();
	}
}

void UBuildComponent::Building()
{
	
}

