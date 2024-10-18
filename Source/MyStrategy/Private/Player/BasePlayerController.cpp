#pragma once

#include "BasePlayerController.h"
#include "BaseUnitCharacter.h"
#include "GameData.h"
#include "Kismet/GameplayStatics.h"
#include "ManagerBuildingComponent.h"
#include "BuildComponent.h"

ABasePlayerController::ABasePlayerController()
{
	bShowMouseCursor = true;

	BuildComponent = CreateDefaultSubobject<UBuildComponent>("Build Component");
	PawnCamera = CreateDefaultSubobject<ABaseCameraPawn>("Pawn Camera");
	ManagerBuildingComponent = CreateDefaultSubobject<UManagerBuildingComponent>("Manager Building Component");
	ManagerResoursesComponent = CreateDefaultSubobject<UManagerResoursesComponent>("Manager Resourses Component");
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


	InputComponent->BindAction(FName("MouseClick"), IE_Pressed, this, &ABasePlayerController::MousePressed);
	InputComponent->BindAction(FName("MouseClick"), IE_Released, this, &ABasePlayerController::MouseReleased);
	InputComponent->BindAction(FName("MouseRightButton"), IE_Pressed,this,  &ABasePlayerController::MoveUnitToPosition);
	InputComponent->BindAction(FName("BuildButton"), IE_Pressed,this,  &ABasePlayerController::BuildPressed);

	//InputComponent->BindAxis("MouseY", this,  &ABasePlayerController::CameraScrollY);
	//InputComponent->BindAxis("MouseX", this,  &ABasePlayerController::CameraScrollX);

	//InputComponent->BindAction(FName("StartBuilding"), IE_Pressed, BuildComponent,  &UBuildComponent::StartBuilding);
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
	// if(auto UnitData = UnitDataRow.DataTable->FindRow<FUnitData>("UnitTest", ""))
	// 	UE_LOG(LogTemp, Log, TEXT("Succes DataTable : %f"), UnitData->Experience);
}

void ABasePlayerController::MousePressed()
{
	isMousePressed = true;
	LeftMouseClick = false;
	HitMouse();
}

void ABasePlayerController::MouseReleased()
{
	LeftMouseClick = true;
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
	if(isMousePressed)// && CanSelectUnit)
	{
		const auto Hit = MouseRaycast();
		if(Hit.IsValidBlockingHit())
		{
			if(Hit.GetActor()->IsA(ABaseUnitCharacter::StaticClass()))
			{
				auto const PlayerValue = Cast<ABaseUnitCharacter>(Hit.GetActor());
				//UE_LOG(LogTemp, Log, TEXT("Trace hit Base Unit Character : %s"), *Hit.GetActor()->GetName());

				if(ActiveCharacter && PlayerValue == ActiveCharacter)
				{
					DecalSetVisible(ActiveCharacter, false);
				}
				else if(ActiveCharacter)
				{
					DecalSetVisible(ActiveCharacter, false);
					ActiveCharacter = PlayerValue;
					DecalSetVisible(PlayerValue, true);
				}
				else
				{
					ActiveCharacter = PlayerValue;
					DecalSetVisible(ActiveCharacter, true);
				}
			}
		}
	}
}

void ABasePlayerController::MoveUnitToPosition()
{
	if(!ActiveCharacter) return;
	
	ActiveCharacter->MoveOnPosition(MouseRaycast().Location);
}

void ABasePlayerController::DecalSetVisible(ABaseUnitCharacter* Unit, bool isActive)
{
	Unit->VisibleDecalSet(isActive);
	
	if(isActive)
	{
		SetActiveUnit(Unit);
		//Unit->HealingUnit();
		Unit->SetVisibilityUnitWidget(ESlateVisibility::Visible);
	}
	else
	{
		SetDeactiveUnit();
		Unit->SetVisibilityUnitWidget(ESlateVisibility::Hidden);
		ActiveCharacter = nullptr;
	}
	UE_LOG(LogTemp, Log, TEXT("Visible Decal Player : %s : %d"), *Unit->GetName(), isActive);
}

void ABasePlayerController::BuildPressed()
{
	BuildComponent->Building();
}

FHitResult ABasePlayerController::MouseRaycast(ECollisionChannel CollisionChannel)
{
	FHitResult Hit;
	GetHitResultUnderCursor(CollisionChannel, true, Hit);
	return Hit;
}

