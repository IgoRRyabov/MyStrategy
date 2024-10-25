#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ResourceExtractionInterface.generated.h"

enum class ETypeResourse;
UINTERFACE(MinimalAPI)
class UResourceExtractionInterface : public UInterface
{
	GENERATED_BODY()
};


class MYSTRATEGY_API IResourceExtractionInterface
{
	GENERATED_BODY()

public:
	virtual void ResourceExtraction();
	virtual void AddResource(ETypeResourse & resType, int & resCount);
};