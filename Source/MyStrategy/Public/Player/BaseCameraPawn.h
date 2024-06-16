#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "BaseCameraPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MYSTRATEGY_API ABaseCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	ABaseCameraPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void CameraScrollY(float value);
	UFUNCTION(BlueprintCallable)
	void CameraScrollX(float value);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Scroll Offset")
	float MultiOffsetCameraPos = 600.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Camera")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Camera")
	UCameraComponent* CameraComponent;

	APlayerController* PlayerController;
	UFUNCTION(BlueprintCallable)
	UCameraComponent* GetCameraComponent() const {return CameraComponent;}
};
