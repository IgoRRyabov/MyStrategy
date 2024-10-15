#include "BaseUnitCharacter.h"

#include "ObjectForBuilding.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"

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
}

void ABaseUnitCharacter::BeginPlay()
{
	Super::BeginPlay();

	//check(BaseUserWidget);
	if(BaseUserWidget)
	{
		BaseUserWidget->HealthUnit = HealthUnit / MaxHealthUnit;
		BaseUserWidget->ArmorUnit = ArmorUnit / MaxArmorUnit;
		BaseUserWidget->SlateVisibility = ESlateVisibility::Hidden;
		UE_LOG(LogTemp, Log, TEXT("User Widget : %s"), *BaseUserWidget->GetName());
		BaseUserWidget->SetOwnerUnit(this);
	}
	
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

void ABaseUnitCharacter::SetVisibilityUnitWidget(ESlateVisibility Visibility)
{
	if(BaseUserWidget)
		BaseUserWidget->SlateVisibility = Visibility;
}

void ABaseUnitCharacter::VisibleDecalSet(bool value) const
{
	if(DecalComponent)
		DecalComponent->SetVisibility(value);
}

