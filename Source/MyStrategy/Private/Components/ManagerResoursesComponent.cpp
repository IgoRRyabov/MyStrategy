#include "ManagerResoursesComponent.h"
#include "BaseHUD.h"
#include "BasePlayerController.h"
#include "GameData.h"
#include "Kismet/GameplayStatics.h"

UManagerResoursesComponent::UManagerResoursesComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UManagerResoursesComponent::UpdateResourse(ETypeResourse TRes, float value)
{
	SetResouse(TRes, value);
}

bool UManagerResoursesComponent::GetResourse(TMap<ETypeResourse, int> PRes) const
{
	if(PlayerResourse.IsEmpty() || PRes.IsEmpty())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Error !!!!"));
		return false;	
	}
	return true;
}

void UManagerResoursesComponent::BeginPlay()
{
	Super::BeginPlay();

	auto const PlayerControllerRef = Cast<ABasePlayerController>(GetOwner());
	MainHUD = Cast<ABaseHUD>(PlayerControllerRef->GetHUD());
	MainHUD->SetResourseComponent(this);
	/// Test
	/// DelegateUpdateResourse.Broadcast(ETypeResourse::Gold, 999);
}

void UManagerResoursesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UManagerResoursesComponent::SetResouse(ETypeResourse TRes, float value)
{
	if (PlayerResourse.Find(TRes))
	{
		PlayerResourse.Emplace(TRes, *PlayerResourse.Find(TRes) + value);
	}
	else
	{
		PlayerResourse.Emplace(TRes, value);
	}
	DelegateUpdateResourse.Broadcast(TRes, *PlayerResourse.Find(TRes));
}

