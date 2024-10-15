#pragma once

#include "Building/ObjectForBuilding.h"
#include "BuildingWidget.h"

AObjectForBuilding::AObjectForBuilding()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Build Mesh");
	RootComponent = StaticMeshComponent;
	UserWidget = CreateDefaultSubobject<UBuildingWidget>("Build Widget");
	TypeBuild = Default;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Collision Box");
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AObjectForBuilding::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AObjectForBuilding::OnOverlapEnd);
	BoxComponent->SetupAttachment(StaticMeshComponent);
}

void AObjectForBuilding::BeginPlay()
{
	Super::BeginPlay();
}

void AObjectForBuilding::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InterfaceOverlapBegin(OtherActor);
}

void AObjectForBuilding::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InterfaceOverlapEnd(OtherActor);
}

void AObjectForBuilding::InterfaceOverlapBegin(AActor* OtherActor)
{
	IEnterInterface::InterfaceOverlapBegin(OtherActor);
}

void AObjectForBuilding::InterfaceOverlapEnd(AActor* OtherActor)
{
	IEnterInterface::InterfaceOverlapEnd(OtherActor);
}

void AObjectForBuilding::AddUnits(AActor* unit)
{
	IEnterInterface::AddUnits(unit);
	if(unit->IsA(ABaseUnitCharacter::StaticClass()))
	{
		auto unitEnter = Cast<ABaseUnitCharacter>(unit);
		// Добавление юнита в здание
		if(UnitsInBuiding.IsEmpty()) 
		{
			UnitsInBuiding.Add(unitEnter->unitName, unitEnter);
		}
		else
		{
			UnitsInBuiding.FindOrAdd(unitEnter->unitName, unitEnter);
		}
	}
}

void AObjectForBuilding::MinusUnits(AActor* unit)
{
	IEnterInterface::MinusUnits(unit);
	
}

