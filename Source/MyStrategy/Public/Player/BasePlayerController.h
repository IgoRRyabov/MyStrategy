#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "BaseUnitCharacter.h"
#include "BaseCameraPawn.h"
#include "ManagerResoursesComponent.h"
#include "BasePlayerController.generated.h"

class UBuildComponent;
class UManagerBuildingComponent;

UCLASS()
class MYSTRATEGY_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABasePlayerController();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category= "Widget Event")
	void AddVertBoxElement(UBuildingWidget* UserWidget);
	
	UFUNCTION(BlueprintImplementableEvent, Category="CustomEvent")
	void SetActiveUnit(ABaseUnitCharacter* ActUnit);
	
	UFUNCTION(BlueprintImplementableEvent, Category="CustomEvent")
	void SetDeactiveUnit() const;

	UFUNCTION(BlueprintImplementableEvent, Category="CustomEvent")
	void OnDeath();

	UFUNCTION(BlueprintCallable)
	ABaseUnitCharacter* GetActiveCharacter() {return ActiveCharacter;}
	
	UFUNCTION(BlueprintCallable)
	ABaseCameraPawn* GetCameraPawn() {return PawnCamera;}

	FHitResult MouseRaycast(ECollisionChannel CollisionChannel = ECC_MouseRaycast);

	UBuildComponent* GetBuildComponent() const {return BuildComponent;}
	UManagerBuildingComponent* GetManagerBuildingComponent() const {return ManagerBuildingComponent;}
	UManagerResoursesComponent* GetManagerResoursesComponent() const {return ManagerResoursesComponent;}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "Effect Mouse Click"))
	bool isMousePressed = false;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "Effect Mouse Click"))
	UParticleSystem* ParticleEmitter;

	
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Building")
	UBuildComponent* BuildComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Building")
	UManagerBuildingComponent* ManagerBuildingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Building")
	UManagerResoursesComponent* ManagerResoursesComponent;
	
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
