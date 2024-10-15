#pragma once

#include "CoreMinimal.h"
#include "BaseUnitCharacter.h"
#include "Components/BoxComponent.h"
#include "Materials/Material.h"
#include "GameFramework/Actor.h"
#include "GameData.h"
#include "ObjectForBuilding.generated.h"

class ABasePlayerController;
class UBuildingWidget;
class ABaseUnitCharacter;

struct SResourseForBuilding;

struct SResourseForBuilding
{
	int Gold;
	int Wood;
	int Stone;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateTest, ETypeBuild, TypeBuild);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateResouse, ETypeResourse, TypeResourse, float, value);

UCLASS(Abstract)
class MYSTRATEGY_API AObjectForBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	AObjectForBuilding();
	FDelegateTest OnNewBuilding;
	FOnUpdateResouse OnUpdateResouse;
	
	UBuildingWidget* GetUserWidget() const {return UserWidget;}
	ETypeBuild GetTypeBuilding() const {return TypeBuild;}
	
	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Mesh Build object")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Mesh Build object")
	UBoxComponent* BoxComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Material Build object")
	TArray<UMaterial*> MaterialBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Interface Build")
	UBuildingWidget* UserWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Type Build")
	TEnumAsByte<ETypeBuild> TypeBuild;
};

enum BuildState
{
	StartBuilding,
	FirstStage,
	SecondStage,
	FinalStage
};


