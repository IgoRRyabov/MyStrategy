#pragma once

#include "Building/ObjectForBuilding.h"
#include "BuildingWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/ActorComponent.h"

AObjectForBuilding::AObjectForBuilding()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Build Mesh");
	RootComponent = StaticMeshComponent;
	UserWidget = CreateDefaultSubobject<UBuildingWidget>("Build Widget");
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AObjectForBuilding::OnOverlapBegin);
	StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &AObjectForBuilding::OnOverlapEnd);
	
}

void AObjectForBuilding::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->SetMaterial(0, MaterialBuilding[1]);
}

void AObjectForBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectForBuilding::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CountActor++;

	if(CountActor > 0)
	{
		SetMaterial(0);
	}else
	{
		SetMaterial(1);
	}
}

void AObjectForBuilding::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CountActor--;
	
	if(CountActor > 0)
	{
		SetMaterial(0);
	}else
	{
		SetMaterial(1);
	}
}

void AObjectForBuilding::SetMaterial(int material)
{
	StaticMeshComponent->SetMaterial(0, MaterialBuilding[material]);
}


