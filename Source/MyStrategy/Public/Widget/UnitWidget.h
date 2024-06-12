#pragma once

#include "CoreMinimal.h"

#include "Widget/BaseUserWidget.h"
#include "UnitWidget.generated.h"

class UBaseUserWidget;
class ABaseUnitCharacter;
UCLASS()
class MYSTRATEGY_API UUnitWidget : public UBaseUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Setting Unit")
	float HealthUnit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Setting Unit")
	float ArmorUnit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Setting Unit")
	ESlateVisibility SlateVisibility;

	UFUNCTION(BlueprintCallable)
	void HealingUnit(float healthValue)
	{
		HealthUnit = healthValue;
	};

	// UFUNCTION(BlueprintCallable)
	// void HealingUnitButton(float healthValue)
	// {
	// 	const auto UnitOwner1 = GetOwningLocalPlayer();
	// 	const auto UnitOwner = Cast<ABaseUnitCharacter>(UnitOwner1);
	// 	if(UnitOwner)
	// 		UnitOwner->HealingUnit();
	// };
	
	UFUNCTION(BlueprintCallable)
	void HealingUnitButton(float healthValue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Setting Unit")
	ABaseUnitCharacter* OwnerUnit;

	void SetOwnerUnit(ABaseUnitCharacter* OwnerUnitValue);

	void SetActiveHealing(bool isActive) {ActiveHealing = isActive;}
private:
	bool ActiveHealing = false;;
};
