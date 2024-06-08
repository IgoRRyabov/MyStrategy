#pragma once

#include "CoreMinimal.h"
#include "BaseCameraPawn.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "BaseUnitCharacter.h"
#include "Components/WidgetComponent.h"
#include "BasePlayerController.generated.h"



UCLASS()
class MYSTRATEGY_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABasePlayerController();

	UFUNCTION(BlueprintImplementableEvent, Category="CustomEvent")
	void SetActiveUnit(ABaseUnitCharacter* ActUnit, bool isActive) const;

	UFUNCTION(BlueprintImplementableEvent)
	void SetDeactiveUnit() const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();
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
	
	UFUNCTION(BlueprintCallable)
	bool isActiveUnits() {return (ActiveCharacter) ? true : false;}
	
	UFUNCTION(BlueprintCallable)
	ABaseUnitCharacter* GetActiveCharacter() {return ActiveCharacter;}

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
	
	ABaseCameraPawn* PawnCamera;
	FVector MouseClickPosition;
	void HitMouse();
	void MoveUnitToPosition();
	void DecalSetVisible(ABaseUnitCharacter* Unit, bool isActive);
	FHitResult MouseRaycast();
	
};
