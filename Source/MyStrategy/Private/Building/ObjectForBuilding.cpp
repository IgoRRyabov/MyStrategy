#include "Building/ObjectForBuilding.h"
#include "Components/ActorComponent.h"

AObjectForBuilding::AObjectForBuilding()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Build Mesh");
	RootComponent = StaticMeshComponent;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Collision");
}

void AObjectForBuilding::BeginPlay()
{
	Super::BeginPlay();
	//BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AObjectForBuilding::OnOverlapBegin);
	//BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AObjectForBuilding::OnOverlapEnd);
	UE_LOG(LogTemp, Log, TEXT("Start"));
}

void AObjectForBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectForBuilding::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Start Overlap"));
	static int CountActor;
	CountActor++;
	if(OtherActor)
		UE_LOG(LogTemp, Log, TEXT("Overlap Actor: %s, CountActor = %d"), *OtherActor->GetName(), CountActor);
}

void AObjectForBuilding::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Log, TEXT("End Overlap"));
	static int CountActor;
	CountActor--;
	if(OtherActor)
		UE_LOG(LogTemp, Log, TEXT("Overlap Actor: %s, CountActor = %d"), *OtherActor->GetName(), CountActor);
}


