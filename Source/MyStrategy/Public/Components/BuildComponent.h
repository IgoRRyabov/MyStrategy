#pragma once

#include "CoreMinimal.h"
#include "Building/ObjectForBuilding.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "BuildComponent.generated.h"

class ABasePlayerController;
class ABaseCameraPawn;
class UStaticMeshComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSTRATEGY_API UBuildComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBuildComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	ABasePlayerController* PlayerController;

	void StartBuilding();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Building Mesh")
	TSubclassOf<AObjectForBuilding> ObjectForBuilding;


	AObjectForBuilding* BuildObject;
private:

	bool isBuild = false;

	void Building();

	FVector LocationBuild;
};
