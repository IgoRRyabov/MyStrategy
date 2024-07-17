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

	void SetGold(float value)
	{
		CountGold += FMath::Max(0, value);
		//UE_LOG(LogTemp, Log, TEXT("CountGoldNow : %f"), CountGold);
	}
	float GetGold() const {return CountGold;}
	
	UFUNCTION()
	void UpdateResourse(ETypeResourse TRes, float value);
	UFUNCTION()
	bool GetResourse(TMap<TEnumAsByte<ETypeResourse>, int> PRes);
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TEnumAsByte<ETypeResourse>, int> PlayerResourse;
private:
	/*кол-во золото у игрока*/
	int CountGold = 100;
};
