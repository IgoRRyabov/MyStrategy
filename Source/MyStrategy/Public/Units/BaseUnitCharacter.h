#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/ActiveSelect.h"
#include "BaseUnitCharacter.generated.h"

class UDecalComponent;
class UWidget;
enum class ETypeResourse;

UCLASS(Abstract)
class MYSTRATEGY_API ABaseUnitCharacter : public ACharacter, public IActiveSelect
{
	GENERATED_BODY()

public:
	ABaseUnitCharacter();
	
	UFUNCTION(BlueprintImplementableEvent, Category= "Custom Event")
	void MoveOnPosition(const FVector& Position);

	UFUNCTION(BlueprintCallable)
	void HealingUnit();
	
	float GetPercentHealthUnit() const {return HealthUnit/MaxHealthUnit;};
	virtual void VisibleDecalSet(bool value) override;

	void SetVisibilityUnitWidget(ESlateVisibility Visibility);

	UFUNCTION(BlueprintCallable)
	float GetHealthUnit() const {return HealthUnit;}
	UFUNCTION(BlueprintCallable)
	float GetMaxHealthUnit() const {return MaxHealthUnit;}

	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	int unitId;

	// Персонжу необходимо войти в здание
	void SetIsWantEnterBuilding(bool isVal) {isWantEnterBuilding = isVal;}

	void EnterBuildUnit();
	AActor* ObjectEnter;
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Decal select Unit")
	UDecalComponent* DecalComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Image Unit")
	UTexture2D* ImageUnit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health Unit")
	float HealthUnit = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health Unit")
	float ArmorUnit = 100;
private:
	
	float MaxHealthUnit = 100;
	float MaxArmorUnit = 100;

	FTimerHandle TimerHealing;
	float HealthPercent() {return HealthUnit / MaxHealthUnit;};

	/*
	 * Персонажу нужно зайти в здание?
	 */
	bool isWantEnterBuilding = false;

	/*
	 * Персонаж входит в здание
	 */
	bool EnterBuilding(class IEnterInterface* object);

	//Переносимые персонажем ресурсы
	ETypeResourse typeRes;
	int countRes;

	AActor* CollisionObject;
};
