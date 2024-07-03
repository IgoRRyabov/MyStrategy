#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "BaseUserWidget.generated.h"

class ABaseUnitCharacter;

UCLASS()
class MYSTRATEGY_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Setting Unit")
	ESlateVisibility SlateVisibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Setting Unit")
	ABaseUnitCharacter* OwnerUnit;
	
	virtual void SetOwnerUnit(ABaseUnitCharacter* OwnerUnitValue);
	virtual void BeginPlay() {};
protected:
	
	
private:
};
