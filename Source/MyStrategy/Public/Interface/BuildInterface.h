#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameData.h"
#include "BuildInterface.generated.h"

UINTERFACE(MinimalAPI)
class UBuildInterface : public UInterface
{
	GENERATED_BODY()
};

class MYSTRATEGY_API IBuildInterface
{
	GENERATED_BODY()

public:
	//template<typename key, typename val>
	//virtual void RequestResources(TMap<int, int> arg1);

	virtual void RequestResources(ETypeResourse &resType, int &resCount);
};
