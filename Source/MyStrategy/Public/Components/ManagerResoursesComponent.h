#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData.h"
#include "ManagerResoursesComponent.generated.h"

struct FResourse;
class ABaseHUD;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDelegateUpdateResourse, ETypeResourse, TRes, int, count);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSTRATEGY_API UManagerResoursesComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	FDelegateUpdateResourse DelegateUpdateResourse;
	
	UManagerResoursesComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void SetResouse(ETypeResourse TRes, float value);
	
	float GetGold() const {return CountGold;}
	
	UFUNCTION()
	void UpdateResourse(ETypeResourse TRes, float value);
	UFUNCTION()
	bool GetResourse(TMap<ETypeResourse, int> PRes) const;

	ABaseHUD* MainHUD;
protected:
	virtual void BeginPlay() override;

	// Все ресурсы игрока
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ETypeResourse, int> PlayerResourse;
private:
	/*кол-во золото у игрока*/
	int CountGold = 100;
};
