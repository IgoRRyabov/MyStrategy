#include "Player/BaseCameraPawn.h"
#include "ScreenPass.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseCameraPawn::ABaseCameraPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Component");
	SpringArmComponent->TargetArmLength = 0.f;
	SpringArmComponent->bEnableCameraLag = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->AddLocalRotation(FRotator(-70, 0, 0));
}

void ABaseCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
}

void ABaseCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCameraPawn::CameraScrollY(float value)
{
	if(!PlayerController) return;
	float PositionMouseX;
	float PositionMouseY;

	int ViewportSizeX;
	int ViewportSizeY;
	PlayerController->GetMousePosition(PositionMouseX, PositionMouseY);
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	auto PercMousePosX = PositionMouseX / ViewportSizeX;

	if(PercMousePosX > 0.98f)
	{
		double Offset = MultiOffsetCameraPos * GetWorld()->GetDeltaSeconds();
		FVector VectorOffsetX = {0, Offset, 0};
		AddActorWorldOffset(VectorOffsetX);
	}else if(PercMousePosX < 0.02f)
	{
		double Offset = MultiOffsetCameraPos * GetWorld()->GetDeltaSeconds();
		FVector VectorOffsetX = {0, -Offset, 0};
		AddActorWorldOffset(VectorOffsetX);
	}
}

void ABaseCameraPawn::CameraScrollX(float value)
{
	if(!PlayerController) return;
	float PositionMouseX;
	float PositionMouseY;

	int ViewportSizeX;
	int ViewportSizeY;
	PlayerController->GetMousePosition(PositionMouseX, PositionMouseY);
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto PercMousePosY = PositionMouseY / ViewportSizeY;

	if(PercMousePosY > 0.98f)
	{
		double Offset = MultiOffsetCameraPos * GetWorld()->GetDeltaSeconds();
		FVector VectorOffsetY = {-Offset, 0, 0};
		AddActorWorldOffset(VectorOffsetY);
	}else if(PercMousePosY < 0.02f)
	{
		double Offset = MultiOffsetCameraPos * GetWorld()->GetDeltaSeconds();
		FVector VectorOffsetY = {Offset, 0, 0};
		AddActorWorldOffset(VectorOffsetY);
	}
}
