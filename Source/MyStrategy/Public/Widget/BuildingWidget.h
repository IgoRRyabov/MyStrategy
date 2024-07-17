#pragma once

#include "CoreMinimal.h"
#include "GameData.h"
#include "Widget/BaseUserWidget.h"
#include "BuildingWidget.generated.h"

class AObjectForBuilding;
class UBuildingIconWidget;

UCLASS()
class MYSTRATEGY_API UBuildingWidget : public UBaseUserWidget
{
	GENERATED_BODY() 
	UBuildingWidget();
public:
	

	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Data Table")
	FDataTableRowHandle ObjectDataHandle;
	
	TArray<FBuildingObjectData*> BuildingObjectData;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Array Build Icon Widget")
	TArray<UBuildingIconWidget*> BuildingIconWidgets;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Array Build Icon Widget")
	UBuildingIconWidget* UBuild;
protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category= "Add Widget")
	void AddVertexIconBuild(UBuildingIconWidget* BuildingIconWidgetsRef);
};


