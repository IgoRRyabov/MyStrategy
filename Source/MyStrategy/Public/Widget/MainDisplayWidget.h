#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainDisplayWidget.generated.h"

class UTextBlock;
class UBorder;
class UButtonBuildingWidget;
enum class ETypeResourse;
struct FBuildingObjectData;

UCLASS()
class MYSTRATEGY_API UMainDisplayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	void UpdateRes(ETypeResourse TRes, int value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Button")
	UButtonBuildingWidget* ButtonBuildingWidget;
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GoldCount")
	int GoldCount = 0;

	void SetGoldCount(int value);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateEvent();
	
	UFUNCTION(BlueprintCallable)
	void CreateButtonBuildWidget();
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UBorder* BorderBuildWidget;
	
};

