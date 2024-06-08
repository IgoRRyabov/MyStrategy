#pragma once

#include "CoreMinimal.h"
#include "BaseUnitCharacter.h"
#include "UnitData.generated.h"

USTRUCT(BlueprintType)
struct FUnitData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHealth;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Intelligence;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Experience;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<ABaseUnitCharacter> UnitCharacter;
};