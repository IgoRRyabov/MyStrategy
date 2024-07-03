#pragma once

#include "CoreMinimal.h"
#include "Widget/BaseUserWidget.h"
#include "BuildingIconWidget.generated.h"

UCLASS()
class MYSTRATEGY_API UBuildingIconWidget : public UBaseUserWidget
{
	GENERATED_BODY()

public:

	void SetIcon(UTexture2D* IconRef) {Icon = IconRef; SetBrushIcon(Icon);};
	void SetName(FName name) {NameBuilding = name;};
protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category= "Set Brush")
	void SetBrushIcon(UTexture2D* IconRef);
private:

	UPROPERTY(VisibleAnywhere, Category= "Icon")
	UTexture2D* Icon;

	UPROPERTY(VisibleAnywhere, Category= "Icon")
	FName NameBuilding;

	UFUNCTION(BlueprintCallable)
	void Start();
};
