#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "Building/ObjectForBuilding.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "BuildComponent.generated.h"

class ABasePlayerController;
class ABaseCameraPawn;
class UStaticMeshComponent;
class AObjectForBuilding;
class UBuildingWidget;
struct FBuildingObjectData;

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

	void StartBuilding(FName name);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Building Mesh")
	TArray<TSubclassOf<AObjectForBuilding>> ObjectForBuilding;

	UFUNCTION(BlueprintCallable)
	UBuildingWidget* GetBuildingWidget() {return BuildingWidget;};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Building")
	UBuildingWidget* BuildingWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Data Table")
	FDataTableRowHandle ObjectDataHandle;

	FBuildingObjectData* BuildingObjectData;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Data Table")
	TMap<FName, UTexture2D*> IconBuild;
private:

	bool isBuild = false;
	void Building();
	void CancerBuilding();
	FVector LocationBuild;
	void ResetBuildingValue();
	TSubclassOf<AObjectForBuilding> BuildObj;
	AObjectForBuilding* BuildingRef;
};
