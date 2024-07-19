#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData.h"
#include "ManagerResoursesComponent.generated.h"

struct FResourse;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSTRATEGY_API UManagerResoursesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UManagerResoursesComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetResouse(ETypeResourse TRes, float value)
	{
		*PlayerResourse.Find(TRes) += FMath::Max(0, value);
		UE_LOG(LogTemp, Log, TEXT("CountResSet : %d"), TRes);
		UE_LOG(LogTemp, Log, TEXT("CountResSet : %d"), *PlayerResourse.Find(TRes));
	}
	float GetGold() const {return CountGold;}
	
	UFUNCTION()
	void UpdateResourse(ETypeResourse TRes, float value);
	UFUNCTION()
	bool GetResourse(TMap<TEnumAsByte<ETypeResourse>, int> PRes);
	
protected:
	virtual void BeginPlay() override;

	// Все ресурсы игрока
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TEnumAsByte<ETypeResourse>, int> PlayerResourse;
private:
	/*кол-во золото у игрока*/
	int CountGold = 100;
};
