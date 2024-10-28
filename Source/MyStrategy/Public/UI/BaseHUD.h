#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

UCLASS()
class MYSTRATEGY_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

	ABaseHUD();
	
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Reference")
	UUserWidget* MainDisplayWidget;
};
