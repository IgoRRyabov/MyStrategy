#include "ManagerResoursesComponent.h"
#include "GameData.h"


UManagerResoursesComponent::UManagerResoursesComponent()
{
	PrimaryComponentTick.bCanEverTick = false;;

}

void UManagerResoursesComponent::UpdateResourse(ETypeResourse TRes, float value)
{
	SetResouse(TRes, value);
}

bool UManagerResoursesComponent::GetResourse(TMap<ETypeResourse, int> PRes)
{
	if(PlayerResourse.IsEmpty() || PRes.IsEmpty())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Error !!!!"));
		return false;	
	}
	//if(*PRes.Find(Gold) > *PlayerResourse.Find(Gold)) return false;
	//*PlayerResourse.Find(Gold) = *PlayerResourse.Find(Gold) - *PRes.Find(Gold);
	
	//UE_LOG(LogTemp, Log, TEXT("CountGoldNow : %d"), *PlayerResourse.Find(Gold));
	return true;
}

void UManagerResoursesComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UManagerResoursesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

