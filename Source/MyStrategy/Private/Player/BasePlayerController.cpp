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
	InputComponent->BindAction(FName("Build"), IE_Pressed, this, &ABasePlayerController::BuildingPressed);
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
		const auto Hit = MouseRaycast(ECC_GameTraceChannel1);
		if(Hit.IsValidBlockingHit())
		{
			if(Hit.GetActor()->Implements<UActiveSelect>())
			{
				auto const Object = Cast<AActor>(Hit.GetActor());
				UE_LOG(LogTemp, Log, TEXT("Trace hit object = %s"), *Hit.GetActor()->GetName());

				if(ActiveCharacter && Object == ActiveCharacter)
				{
					DecalSetVisible(ActiveCharacter, false);
				}
				else if(ActiveCharacter)
				{
					DecalSetVisible(ActiveCharacter, false);
					ActiveCharacter = Object;
					DecalSetVisible(Object, true);
				}
				else
				{
					ActiveCharacter = Object;
					DecalSetVisible(ActiveCharacter, true);
				}
			}
		}
	}
}

void ABasePlayerController::MoveUnitToPosition()
{
	if(!ActiveCharacter) return;

	if (!ActiveCharacter->IsA(ABaseUnitCharacter::StaticClass())) return;
	
	const auto actCharact = Cast<ABaseUnitCharacter>(ActiveCharacter);
	actCharact->MoveOnPosition(MouseRaycast(ECC_GameTraceChannel1).Location);
}

void ABasePlayerController::DecalSetVisible(AActor* object, bool isActive)
{
	auto const obj = Cast<IActiveSelect>(object);
	obj->VisibleDecalSet(isActive);
	
	if(isActive)
	{
		//SetActiveUnit(obj);
		//Unit->HealingUnit();
		//obj->SetVisibilityUnitWidget(ESlateVisibility::Visible);
	}
	else
	{
		//SetDeactiveUnit();
		//obj->SetVisibilityUnitWidget(ESlateVisibility::Hidden);
		ActiveCharacter = nullptr;
	}
	UE_LOG(LogTemp, Log, TEXT("Visible Decal Player : %s : %d"), *object->GetName(), isActive);
}

void ABasePlayerController::BuildingPressed()
{
	if (!BuildComponent) return;
	BuildComponent->Building();
}

FHitResult ABasePlayerController::MouseRaycast(ECollisionChannel CollisionChannel) const
{
	FHitResult Hit;
	GetHitResultUnderCursor(CollisionChannel, true, Hit);
	return Hit;
}

