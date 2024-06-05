#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseUnitCharacter.generated.h"

class UDecalComponent;

UCLASS()
class MYSTRATEGY_API ABaseUnitCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseUnitCharacter();
	
	UFUNCTION(BlueprintImplementableEvent, Category= "Custom Event")
	void MoveOnPosition(const FVector& Position);
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Decal select Unit")
	UDecalComponent* DecalComponent;
	
	
public:	
	void VisibleDecalSet(bool value) const;
};