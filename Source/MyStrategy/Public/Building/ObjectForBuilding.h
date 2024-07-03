#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/Material.h"
#include "GameFramework/Actor.h"
#include "ObjectForBuilding.generated.h"

class UBuildingWidget;

UCLASS()
class MYSTRATEGY_API AObjectForBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	AObjectForBuilding();

	UBuildingWidget* GetUserWidget() const {return UserWidget;}
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Mesh Build object")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Mesh Build object")
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Material Build object")
	TArray<UMaterialInstance*> MaterialBuildingInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Material Build object")
	TArray<UMaterial*> MaterialBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Material Build object")
	UMaterial* MaterialBuild;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Interface Build")
	UBuildingWidget* UserWidget;
public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
private:

	int CountActor = 0;
	void SetMaterial(int material);
};
