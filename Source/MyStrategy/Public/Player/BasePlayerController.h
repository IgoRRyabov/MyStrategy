#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "BaseUnitCharacter.h"
#include "BaseCameraPawn.h"
#include "BasePlayerController.generated.h"

class UBuildComponent;

UCLASS()
class MYSTRATEGY_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABasePlayerController();

	UFUNCTION(BlueprintImplementableEvent, Category="CustomEvent")
	void SetActiveUnit(ABaseUnitCharacter* ActUnit);

	UFUNCTION(BlueprintImplementableEvent)
	void SetDeactiveUnit() const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();

	UFUNCTION(BlueprintCallable)
	ABaseUnitCharacter* GetActiveCharacter() {return ActiveCharacter;}
	
	UFUNCTION(BlueprintCallable)
	ABaseCameraPawn* GetCameraPawn() {return PawnCamera;}

	FHitResult MouseRaycast(ECollisionChannel CollisionChannel = ECC_Visibility);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "Effect Mouse Click"))
	UParticleSystem* ParticleEmitter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "Effect Mouse Click"))
	bool isMousePressed = false;
	
	UFUNCTION(BlueprintCallable)
	FVector GetMouseClickPosition() {return MouseClickPosition;}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Active Unit")
	ABaseUnitCharacter* ActiveCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Active Unit")
	UParticleSystem* EmitterMousePosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Setting Unit")
	FDataTableRowHandle UnitDataRow;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Pawn")
	ABaseCameraPawn* PawnCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Pawn")
	UBuildComponent* BuildComponent;
	
	UFUNCTION(BlueprintCallable)
	bool isActiveUnits() {return (ActiveCharacter) ? true : false;}
	
	UFUNCTION(BlueprintCallable)
	float ActiveUnitHealth() {return ActiveCharacter ? ActiveCharacter->GetPercentHealthUnit() : 0;};
private:
	
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;
	
	void MousePressed();
	void MouseReleased();

	void CameraScrollY(float value);
	void CameraScrollX(float value);
	
	
	FVector MouseClickPosition;
	void HitMouse();
	void MoveUnitToPosition();
	void DecalSetVisible(ABaseUnitCharacter* Unit, bool isActive);
	
};
