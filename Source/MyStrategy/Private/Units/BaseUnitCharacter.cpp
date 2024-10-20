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
	
	BaseUserWidget = CreateDefaultSubobject<UUnitWidget>("Unit Widget");

	GetCapsuleComponent()->SetCollisionProfileName("UnitCollision");

	unitId = globalIdUnit;
	globalIdUnit++;
}

void ABaseUnitCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->GetClass()->ImplementsInterface(UEnterInterface::StaticClass()))
	{
		if(true)//isWantEnterBuilding)
		{
			//Вход в здание
			auto object = Cast<IEnterInterface>(OtherActor);
			if(EnterBuilding(object))
			{
				if (OtherActor->Implements<UBuildInterface>())
				{
					const auto obj = Cast<IBuildInterface>(OtherActor);
					obj->RequestResources(typeRes, countRes);
					UE_LOG(LogTemp, Log, TEXT("countRes unit ==  : %d"), countRes);
				}
			}
		}
		//UE_LOG(LogTemp, Log, TEXT("Interface find in  : %s"), *OtherComp->GetName());
	}
}

void ABaseUnitCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void ABaseUnitCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Test
	typeRes = ETypeResourse::Gold;
	countRes = 150;
	
	//check(BaseUserWidget);
	if(BaseUserWidget)
	{
		BaseUserWidget->HealthUnit = HealthUnit / MaxHealthUnit;
		BaseUserWidget->ArmorUnit = ArmorUnit / MaxArmorUnit;
		BaseUserWidget->SlateVisibility = ESlateVisibility::Hidden;
		UE_LOG(LogTemp, Log, TEXT("User Widget : %s"), *BaseUserWidget->GetName());
		BaseUserWidget->SetOwnerUnit(this);
	}

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
	static uint8 countHealth = 0;
	if(countHealth < 5 && HealthUnit < MaxHealthUnit)
	{
		countHealth++;
		HealthUnit += 5;
		GetWorld()->GetTimerManager().SetTimer(TimerHealing, this, &ABaseUnitCharacter::HealingUnit,  1.f, true);

		(HealthUnit > MaxHealthUnit) ? BaseUserWidget->HealingUnit(1) : BaseUserWidget->HealingUnit(HealthPercent());
	}
	else
	{
		countHealth = 0;
		GetWorld()->GetTimerManager().ClearTimer(TimerHealing);
		BaseUserWidget->SetActiveHealing(false);
	}
}

void ABaseUnitCharacter::VisibleDecalSet(bool value)
{
	IActiveSelect::VisibleDecalSet(value);

	if(DecalComponent)
		DecalComponent->SetVisibility(value);
}

void ABaseUnitCharacter::SetVisibilityUnitWidget(ESlateVisibility Visibility)
{
	if(BaseUserWidget)
		BaseUserWidget->SlateVisibility = Visibility;
}


