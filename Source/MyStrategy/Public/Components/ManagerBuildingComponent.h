#pragma once

#include "CoreMinimal.h"
#include "GameData.h"
#include "Components/ActorComponent.h"
#include "ManagerBuildingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSTRATEGY_API UManagerBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UManagerBuildingComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void AddCountBuilding(ETypeBuild TypeBuilding);
	
	UFUNCTION()
	void Test();
private:
	// Кол-во построенных зданий
	int SumCountBuildint = 0;
	int TownHallCountBuildint = 0;
	
	
};
