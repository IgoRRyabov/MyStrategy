#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildWidget.generated.h"

class UImage;
UCLASS()
class MYSTRATEGY_API UBuildWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Name Build in DataTable")
	FName NameBuilding;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(BindWidget))
	UImage* Image;
};
