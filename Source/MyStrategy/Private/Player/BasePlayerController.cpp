#include "Player/BasePlayerController.h"

#include "BaseUnitCharacter.h"
//#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BaseCameraPawn.h"

ABasePlayerController::ABasePlayerController()
{
	bShowMouseCursor = true;
}



void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


	InputComponent->BindAction(FName("MouseClick"), IE_Pressed, this, &ABasePlayerController::MousePressed);
	InputComponent->BindAction(FName("MouseClick"), IE_Released, this, &ABasePlayerController::MouseReleased);
	InputComponent->BindAxis("MouseY", this,  &ABasePlayerController::CameraScrollY);
	InputComponent->BindAxis("MouseX", this,  &ABasePlayerController::CameraScrollX);
	InputComponent->BindAction(FName("MouseRightButton"), IE_Pressed,this,  &ABasePlayerController::MoveUnitToPosition);
	// if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	// {
	// 	
	// }
	// else
	// {
	// 	UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	// }
}




void ABasePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	

	
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	PawnCamera = Cast<ABaseCameraPawn>(GetPawn());
	//check(PawnCamera);
}

void ABasePlayerController::MousePressed()
{
	isMousePressed = true;
	HitMouse();
}

void ABasePlayerController::MouseReleased()
{
	isMousePressed = false;
}

void ABasePlayerController::CameraScrollY(float value)
{
	if(!PawnCamera) return;
	PawnCamera->CameraScrollY(value);
}
void ABasePlayerController::CameraScrollX(float value)
{
	if(!PawnCamera) return;
	PawnCamera->CameraScrollX(value);
}

void ABasePlayerController::HitMouse()
{
	FHitResult Hit;
	bool isHit;
	if(isMousePressed)
	{
		isHit = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
		if(isHit)
		{
			const auto LocationHit = &Hit.Location;
			MouseClickPosition = Hit.Location;
			//UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
			//if(!ParticleEmitter) return;
			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleEmitter, FVector{MouseClickPosition}, FRotator::ZeroRotator, true);
			

			if(Hit.GetActor()->IsA(ABaseUnitCharacter::StaticClass()))
			{
				auto const PlayerValue = Cast<ABaseUnitCharacter>(Hit.GetActor());
				UE_LOG(LogTemp, Log, TEXT("Trace hit Base Unit Character : %s"), *Hit.GetActor()->GetName());

				if(PlayerValue == ActiveCharacter)
				{
					ActiveCharacter->VisibleDecalSet(false);
					ActiveCharacter = nullptr;
					UE_LOG(LogTemp, Log, TEXT("Diactivate Unit : "));
					return;
				}
				
				if(!ActiveCharacter)
				{
					ActiveCharacter = Cast<ABaseUnitCharacter>(Hit.GetActor());
					DecalDiactivated(ActiveCharacter, true);
					return;

				}
				DecalDiactivated(ActiveCharacter, false);
				ActiveCharacter = Cast<ABaseUnitCharacter>(Hit.GetActor());
				DecalDiactivated(ActiveCharacter, true);

				
			}
			else
			{
				if(!EmitterMousePosition && MouseClickPosition == FVector::Zero()) return;
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmitterMousePosition, MouseClickPosition);
			}
		}
	}
}

void ABasePlayerController::MoveUnitToPosition()
{
	
	if(!ActiveCharacter) return;

	FHitResult Hit;
	bool isHit = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	if(!isHit) return;
	
	ActiveCharacter->MoveOnPosition(Hit.Location);
	UE_LOG(LogTemp, Log, TEXT("Unit Go to Position"));
}

void ABasePlayerController::DecalDiactivated(ABaseUnitCharacter* Unit, bool isActive)
{
	Unit->VisibleDecalSet(isActive);
	UE_LOG(LogTemp, Log, TEXT("Visible Decal Player : %s : %d"), *Unit->GetName(), isActive);
}
