#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnterInterface.generated.h"

class AActor;

UINTERFACE(MinimalAPI)
class UEnterInterface : public UInterface
{
	GENERATED_BODY()
};

class MYSTRATEGY_API IEnterInterface
{
	GENERATED_BODY()

public:
	virtual void InterfaceOverlapBegin(class AActor* OtherActor);
	virtual void InterfaceOverlapEnd(class AActor* OtherActor);
	virtual bool AddUnits(class AActor* unit);
	virtual void MinusUnits(class AActor* unit);
};
