#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonBuildingWidget.generated.h"

class UImage;
class AObjectForBuilding;
class UVerticalBox;
class UBuildWidget;
struct FBuildingObjectData;
class UTextBlock;

UCLASS()
class MYSTRATEGY_API UButtonBuildingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Data Table")
	// FDataTableRowHandle DataTableRowHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Data Table")
	UDataTable* DataTableObjectForBuild;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Data Table")
	TArray<UBuildWidget*> BuildWidgets;

	UBuildWidget* WidgetTest;
};
