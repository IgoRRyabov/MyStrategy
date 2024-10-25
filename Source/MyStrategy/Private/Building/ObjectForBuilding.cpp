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
	//BoxComponent->SetCollisionProfileName("BuildCollision");
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AObjectForBuilding::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AObjectForBuilding::OnOverlapEnd);
	BoxComponent->SetupAttachment(StaticMeshComponent);
}

void AObjectForBuilding::BiuldingFinish()
{
	isBuildingBuild = true;
	for (TTuple<ETypeResourse, int> ForBuilding : ResourseForBuilding)
	{
		UE_LOG(LogTemp, Log, TEXT("Count ResourseForBuilding: %d"), ForBuilding.Value);
	}

	ResourceExtraction();
}

void AObjectForBuilding::UpdateWarehouse(ETypeResourse & resType, int & resCount)
{
	if(Warehouse.Find(resType))
	{
		Warehouse.Emplace(resType, resCount + *Warehouse.Find(resType));
		UE_LOG(LogTemp, Log, TEXT("Warehouse count ==  %d"), *Warehouse.Find(resType));
		resCount = 0;
	}
	else
	{
		Warehouse.Emplace(resType, resCount);
		UE_LOG(LogTemp, Log, TEXT("Warehouse count ==  %d"), *Warehouse.Find(resType));
		resCount = 0;
	}
}

void AObjectForBuilding::BeginPlay()
{
	Super::BeginPlay();

	for (TTuple<ETypeResourse, int> countres : Warehouse)
	{
		countResources += countres.Value;
	}

	if (countResources > maxCountResource)
		{UE_LOG(LogTemp, Log, TEXT("Count resources %d > maxCountResource %d"), countResources, maxCountResource);}
	else
		UE_LOG(LogTemp, Log, TEXT("Count resources %d <= maxCountResource %d"), countResources, maxCountResource);
}

void AObjectForBuilding::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InterfaceOverlapBegin(OtherActor);
	//UE_LOG(LogTemp, Log, TEXT("Objeсt Overlap Start! %s"), *OverlappedComp->GetName());
}

void AObjectForBuilding::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InterfaceOverlapEnd(OtherActor);
	//UE_LOG(LogTemp, Log, TEXT("Objeсt Overlap End! %s"), *OverlappedComponent->GetName());
}

void AObjectForBuilding::InterfaceOverlapBegin(AActor* OtherActor)
{
	IEnterInterface::InterfaceOverlapBegin(OtherActor);
	if (!isBuildingBuild)
	{
		CountObjectOverlap++;
		//UE_LOG(LogTemp, Log, TEXT("Count Objeсt Overlap : %d"), CountObjectOverlap);
	}
}

void AObjectForBuilding::InterfaceOverlapEnd(AActor* OtherActor)
{
	IEnterInterface::InterfaceOverlapEnd(OtherActor);
	if (!isBuildingBuild)
	{
		CountObjectOverlap--;
		//UE_LOG(LogTemp, Log, TEXT("Count Objeсt Overlap : %d"), CountObjectOverlap);
	}
}

bool AObjectForBuilding::AddUnits(AActor* unit)
{
	IEnterInterface::AddUnits(unit);
	if (!isBuildingBuild) return false;
	
	if(unit->IsA(ABaseUnitCharacter::StaticClass()))
	{
		CountUnitInBuilding = UnitsInBuiding.Num();
		if (CountUnitInBuilding < MaxCountUnitInBuilding)
		{
			//UE_LOG(LogTemp, Log, TEXT("CountUnitInBuilding : %d"), CountUnitInBuilding);
			auto unitEnter = Cast<ABaseUnitCharacter>(unit);
			// Добавление юнита в здание
			if(UnitsInBuiding.IsEmpty()) 
			{
				UnitsInBuiding.Add(unitEnter->unitId, unitEnter);
			}
			else
			{
				UnitsInBuiding.FindOrAdd(unitEnter->unitId, unitEnter);
			}
			CanExtractResource = true;
			ResourceExtraction();
			return true;
		}
	}
	
	return false;
}

void AObjectForBuilding::MinusUnits(AActor* unit)
{
	IEnterInterface::MinusUnits(unit);
	if(UnitsInBuiding.IsEmpty()) return;

	if(unit->IsA(ABaseUnitCharacter::StaticClass()))
	{
		auto unitEnter = Cast<ABaseUnitCharacter>(unit);
		CountUnitInBuilding = UnitsInBuiding.Num();
		UnitsInBuiding.Remove(unitEnter->unitId);
		if(UnitsInBuiding.IsEmpty())
		{
			CanExtractResource = false;
		}
	}
}

void AObjectForBuilding::SetActive()
{
	IActiveSelect::SetActive();
}

void AObjectForBuilding::DeActive()
{
	IActiveSelect::DeActive();
}

void AObjectForBuilding::VisibleDecalSet(bool value)
{
	IActiveSelect::VisibleDecalSet(value);
}

void AObjectForBuilding::RequestResources(ETypeResourse & resType, int & resCount)
{
	IBuildInterface::RequestResources(resType, resCount);

	UpdateWarehouse(resType, resCount);
}

void AObjectForBuilding::ResourceExtraction()
{
	IResourceExtractionInterface::ResourceExtraction();

	if (!isBuildingBuild) return;

	if (CanExtractResource)
		GetWorld()->GetTimerManager().SetTimer(ExtractionResourceTimer,this, &AObjectForBuilding::AddResource, 1.f, false);
}

void AObjectForBuilding::AddResource()
{
	IResourceExtractionInterface::AddResource();
	//if (!countExtractionResource) return;
	auto res = countExtractionResource;
	if (Warehouse.Find(ExtractionResource)!= nullptr)
	{
		res += *Warehouse.Find(ExtractionResource);
	}

	auto countRes = countResources + countExtractionResource;
	if (countRes < maxCountResource)
	{
		countResources += countExtractionResource;
		Warehouse.Emplace(ExtractionResource, res);
	}
	
	UE_LOG(LogTemp, Log, TEXT("Count extraxtin res : %d"), *Warehouse.Find(ExtractionResource));
	UE_LOG(LogTemp, Log, TEXT("Count res in build ==  : %d"), countResources);
	
	ResourceExtraction();
}

bool AObjectForBuilding::CanBuild() const
{
	bool result = CountObjectOverlap > 0;
	return !result;
}
