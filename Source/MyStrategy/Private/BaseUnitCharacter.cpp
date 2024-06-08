#include "BaseUnitCharacter.h"
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
	
}

void ABaseUnitCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseUnitCharacter::VisibleDecalSet(bool value) const
{
	DecalComponent->SetVisibility(value);
}

