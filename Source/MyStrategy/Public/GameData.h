#pragma once

#include "CoreMinimal.h"
#include "BaseUnitCharacter.h"
#include "BuildingIconWidget.h"
#include "GameData.generated.h"

class AObjectForBuilding;


USTRUCT(BlueprintType)
struct FGameData : public FTableRowBase
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

USTRUCT(Blueprintable)
struct FResourse
{
	GENERATED_BODY()
	
	int Gold;
	int Wood;
};

UENUM()
enum ETypeResourse
{
	BaseResourse = 0,
	Gold,
	Wood
};

USTRUCT(BlueprintType)
struct FBuildingObjectData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AObjectForBuilding> BuildingObjectRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBuildingIconWidget> BuildingIcontRef;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* IconBuild;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName NameBuilding;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TEnumAsByte<ETypeResourse>, int> ResourseForBuilding;
	
};

inline extern bool LeftMouseClick = false;;
inline extern bool CanSelectUnit = true;
inline extern int GlobalDataOneDay = 60;
static int globalIdUnit = 0;
/// 
/// @param min кол-во необходимчых минут
/// @return кол-во минут
inline int GetTimerMin(int min){ return min * 60; };

UENUM()
enum ETypeBuild
{
	Default = 0,
	TownHall
};

UENUM()
enum BuildState
{
	StartBuilding,
	FirstStage,
	SecondStage,
	FinalStage
};

