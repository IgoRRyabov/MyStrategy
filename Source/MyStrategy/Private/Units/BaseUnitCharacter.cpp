#include "BaseUnitCharacter.h"
#include "GameData.h"
#include "ObjectForBuilding.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseUnitCharacter::ABaseUnitCharacter()
{
	GetMesh()->bReceivesDecals = false;
	DecalComponent = CreateDefaultSubobject<UDecalComponent>("Decal");
	DecalComponent->SetupAttachment(RootComponent);
	DecalComponent->SetRelativeLocation(FVector{0,0,-68});
	DecalComponent->SetRelativeRotation(FRotator{90,0,0});
	DecalComponent->SetRelativeScale3D(FVector{3,3,3});
	DecalComponent->DecalSize = FVector{10,20,20};
	DecalComponent->SetVisibility(false);

	GetCapsuleComponent()->SetCollisionProfileName("UnitCollision");

	unitId = globalIdUnit;
	globalIdUnit++;
}

void ABaseUnitCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->GetClass()->ImplementsInterface(UEnterInterface::StaticClass()))
	{
		CollisionObject = OtherActor;
		EnterBuildUnit();
		//UE_LOG(LogTemp, Log, TEXT("Interface find in  : %s"), *OtherComp->GetName());
	}
}

void ABaseUnitCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void ABaseUnitCharacter::EnterBuildUnit()
{
	if (!CollisionObject) return;
	if (ObjectEnter != CollisionObject) return;
	
	if(isWantEnterBuilding)
	{
		//Вход в здание
		if (!CollisionObject->Implements<UEnterInterface>()) return;
		
		auto object = Cast<IEnterInterface>(CollisionObject);
		if(EnterBuilding(object))
		{
			if (CollisionObject->Implements<UBuildInterface>())
			{
				const auto obj = Cast<IBuildInterface>(CollisionObject);
				if (countRes)
				{
					obj->RequestResources(typeRes, countRes);
					UE_LOG(LogTemp, Log, TEXT("!!!!!   countRes unit ==  : %d   !!!!!"), countRes);
				}
			}
		}
	}
}

void ABaseUnitCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Test
	typeRes = ETypeResourse::Gold;
	countRes = 5;
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABaseUnitCharacter::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ABaseUnitCharacter::OnOverlapEnd);
}

bool ABaseUnitCharacter::EnterBuilding(IEnterInterface* object)
{
	if (object->AddUnits(this))
	{
		SetActorEnableCollision(false);
		SetActorHiddenInGame(true);
		GetCharacterMovement()->StopActiveMovement();
		return true;
	}
	return false;
}

void ABaseUnitCharacter::HealingUnit()
{
	
}

void ABaseUnitCharacter::VisibleDecalSet(bool value)
{
	IActiveSelect::VisibleDecalSet(value);

	if(DecalComponent)
		DecalComponent->SetVisibility(value);
}

void ABaseUnitCharacter::SetVisibilityUnitWidget(ESlateVisibility Visibility)
{}


