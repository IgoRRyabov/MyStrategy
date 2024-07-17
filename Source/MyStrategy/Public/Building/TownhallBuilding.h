#pragma once

#include "CoreMinimal.h"
#include "Building/ObjectForBuilding.h"
#include "TownhallBuilding.generated.h"


UCLASS()
class MYSTRATEGY_API ATownhallBuilding : public AObjectForBuilding
{
	GENERATED_BODY()

public:
void AddResourse(int value);
	
private:
	int Resourse = 0;
	/* Максимальное количество ресурсов на складе*/
	int MaxResourse = 100;

	virtual void BeginPlay() override;
};
