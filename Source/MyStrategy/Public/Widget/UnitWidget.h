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

	UFUNCTION(BlueprintCallable)
	void HealingUnit(float healthValue)
	{
		HealthUnit = healthValue;
	};
	
	UFUNCTION(BlueprintCallable)
	void HealingUnitButton(float healthValue);

	void SetActiveHealing(bool isActive) {ActiveHealing = isActive;}
private:
	bool ActiveHealing = false;;
};
