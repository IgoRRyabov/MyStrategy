#include "Player/BasePlayerController.h"

#include "BaseUnitCharacter.h"
//#include "Kismet/GameplayStatics.h"
#include "UnitData.h"
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
	InputComponent->BindAction(FName("MouseRightButton"), IE_Pressed,this,  &ABasePlayerController::MoveUnitToPosition);
	
	InputComponent->BindAxis("MouseY", this,  &ABasePlayerController::CameraScrollY);
	InputComponent->BindAxis("MouseX", this,  &ABasePlayerController::CameraScrollX);
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
	if(auto UnitData = UnitDataRow.DataTable->FindRow<FUnitData>("UnitTest", ""))
		UE_LOG(LogTemp, Log, TEXT("Succes DataTable : %f"), UnitData->Experience);
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
	if(isMousePressed)
	{
		const auto Hit = MouseRaycast();
		if(Hit.GetActor()->IsA(ABaseUnitCharacter::StaticClass()))
		{
			auto const PlayerValue = Cast<ABaseUnitCharacter>(Hit.GetActor());
			UE_LOG(LogTemp, Log, TEXT("Trace hit Base Unit Character : %s"), *Hit.GetActor()->GetName());

			if(ActiveCharacter && PlayerValue == ActiveCharacter)
			{
				DecalSetVisible(PlayerValue, false);
			}
			else if(ActiveCharacter)
			{
				DecalSetVisible(ActiveCharacter, false);
				ActiveCharacter = PlayerValue;
				DecalSetVisible(PlayerValue, true);
			}
			else
			{
				DecalSetVisible(PlayerValue, true);
				ActiveCharacter = PlayerValue;
			}
		}else
		{
			if(!EmitterMousePosition && MouseRaycast().Location != FVector::Zero()) return;
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmitterMousePosition, MouseRaycast().Location);
		}
	}
}

void ABasePlayerController::MoveUnitToPosition()
{
	if(!ActiveCharacter) return;
	
	ActiveCharacter->MoveOnPosition(MouseRaycast().Location);
	UE_LOG(LogTemp, Log, TEXT("Unit Go to Position"));
}

void ABasePlayerController::DecalSetVisible(ABaseUnitCharacter* Unit, bool isActive)
{
	Unit->VisibleDecalSet(isActive);
	
	if(isActive)
		SetActiveUnit(Unit, isActive);
	else
	{
		SetDeactiveUnit();
		ActiveCharacter = nullptr;
	}
	UE_LOG(LogTemp, Log, TEXT("Visible Decal Player : %s : %d"), *Unit->GetName(), isActive);
}

FHitResult ABasePlayerController::MouseRaycast()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	return Hit;
}

