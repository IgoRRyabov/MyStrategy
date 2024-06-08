#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "BaseUnitCharacter.generated.h"

class UDecalComponent;
class UWidget;
UCLASS()
class MYSTRATEGY_API ABaseUnitCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseUnitCharacter();
	
	UFUNCTION(BlueprintImplementableEvent, Category= "Custom Event")
	void MoveOnPosition(const FVector& Position);

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Decal select Unit")
	UDecalComponent* DecalComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Image Unit")
	UTexture2D* ImageUnit;

public:	
	void VisibleDecalSet(bool value) const;
};
