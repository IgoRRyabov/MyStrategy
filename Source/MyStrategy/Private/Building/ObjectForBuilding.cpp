#pragma once

#include "Building/ObjectForBuilding.h"

#include "BasePlayerController.h"
#include "BuildingWidget.h"
#include "Components/ActorComponent.h"

AObjectForBuilding::AObjectForBuilding()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Build Mesh");
	RootComponent = StaticMeshComponent;
	UserWidget = CreateDefaultSubobject<UBuildingWidget>("Build Widget");
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AObjectForBuilding::OnOverlapBegin);
	StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &AObjectForBuilding::OnOverlapEnd);
	if(!BlockBuild.IsEmpty())
		StaticMeshComponent->SetStaticMesh(BlockBuild[0]);
	
}

void AObjectForBuilding::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->SetMaterial(0, MaterialBuilding[1]);
	StaticMeshComponent->SetCollisionProfileName("OverlapAll");
	MaxNumberStageBuiding = BlockBuild.Max();
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
		if(!IsBuilding) SetMaterial(0);
	}else
	{
		if(!IsBuilding) SetMaterial(1);
	}

	if(OtherActor->IsA(ABaseUnitCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Log, TEXT("Unit in Build: %s "), *OtherActor->GetName());
	}
}

void AObjectForBuilding::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CountActor--;
	
	if(CountActor > 0)
	{
		if(!IsBuilding) SetMaterial(0);
	}else
	{
		if(!IsBuilding) SetMaterial(1);
	}
}

void AObjectForBuilding::Building()
{
	if(!GetWorld()) return;
	
	GetWorld()->GetTimerManager().SetTimer(TimerBuilding, this, &AObjectForBuilding::StartBuilding, 1.f, false);
}

void AObjectForBuilding::SetMaterial(int material)
{
	StaticMeshComponent->SetMaterial(0, MaterialBuilding[material]);
}

void AObjectForBuilding::SetCollisionProfile(FName CollProfile) const
{
	StaticMeshComponent->SetCollisionProfileName(CollProfile);
}

void AObjectForBuilding::StartBuilding()
{
	if(!BuildingStart)
	{
		if(!isCountResourseOK())
		{
			UE_LOG(LogTemp, Log, TEXT("Not Gold!!!!"));
			return;
		}
	}
	ScoreBuilding += PointBuilding;
		
	if(ScoreBuilding > MaxScoreBuilding)
	{
		if(NumberStageBuiding > MaxNumberStageBuiding)
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerBuilding);
			UE_LOG(LogTemp, Log, TEXT("Max Stage Building: %d "), MaxNumberStageBuiding);
			DelegateTest.Broadcast(TypeBuild);
			ResourseExtraction();
			return;
		}
		SetMeshBuild(NumberStageBuiding);
		UE_LOG(LogTemp, Log, TEXT("Stage Building: %d "), NumberStageBuiding);
		NumberStageBuiding++;
	}
	Building();
}

void AObjectForBuilding::SetMeshBuild(int NumberStageBuilding)
{
	if(NumberStageBuilding >= MaxNumberStageBuiding) return;
	
	StaticMeshComponent->SetStaticMesh(BlockBuild[NumberStageBuilding]);
	ScoreBuilding = 0;
}

void AObjectForBuilding::ResourseExtraction()
{
	GetWorld()->GetTimerManager().SetTimer(TimerResourse, this, &AObjectForBuilding::ResourseExtractionStart, GetTimerMin(1), false);
}

bool AObjectForBuilding::isCountResourseOK()
{
	return BuildingStart = BasePlayerController->GetManagerResoursesComponent()->GetResourse(ResourseForBuilding);
}

void AObjectForBuilding::ResourseExtractionStart()
{
	OnUpdateResouse.Broadcast(ETypeResourse::Gold, 10);
	ResourseExtraction();
}

