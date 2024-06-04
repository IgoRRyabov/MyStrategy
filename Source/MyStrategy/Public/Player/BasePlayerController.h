#pragma once

#include "CoreMinimal.h"
#include "BaseCameraPawn.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "BaseUnitCharacter.h"
#include "Particles/ParticleEmitter.h"
#include "BasePlayerController.generated.h"



UCLASS()
class MYSTRATEGY_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABasePlayerController();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "Effect Mouse Click"))
	UParticleSystem* ParticleEmitter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "Effect Mouse Click"))
	bool isMousePressed = false;
	
	UFUNCTION(BlueprintCallable)
	FVector GetMouseClickPosition() {return MouseClickPosition;}
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

	ABaseUnitCharacter* ActiveCharacter;
};
