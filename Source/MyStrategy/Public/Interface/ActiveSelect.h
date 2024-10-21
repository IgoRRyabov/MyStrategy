#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActiveSelect.generated.h"

UINTERFACE(MinimalAPI)
class UActiveSelect : public UInterface
{
	GENERATED_BODY()
};

class MYSTRATEGY_API IActiveSelect
{
	GENERATED_BODY()

public:
	virtual void SetActive();
	virtual void DeActive();
	virtual void VisibleDecalSet(bool value);
};
