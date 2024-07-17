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

UCLASS()
class MYSTRATEGY_API AObjectForBuilding : public AActor
{
	
	GENERATED_BODY()
	
public:	
	AObjectForBuilding();
	FDelegateTest DelegateTest;
	FOnUpdateResouse OnUpdateResouse;
	
	UBuildingWidget* GetUserWidget() const {return UserWidget;}
	ETypeBuild GetTypeBuilding() const {return TypeBuild;}
	
	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool IsOverlapObj() {return (CountActor > 0);}

	void SetIsBuilding(bool active){IsBuilding = active; SetCollisionProfile("BlockAll");};

	float GetHealth() const {return Health;}
	float GetArmor() const {return Armor;}
	void SetHealth(float value) {Health = value;}
	void SetArmor(float value) {Armor = value;}
	void Building();
	void SetPlayerController(ABasePlayerController* PControl) {BasePlayerController = PControl;}
	//void SetBuildingResourse(FResourse BRes) {BuildingResourse = BRes;}
	
	/*Ресурсы необходимые для строительства*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TEnumAsByte<ETypeResourse>, int> ResourseForBuilding;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
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

	ETypeBuild TypeBuild;
	
	/* Кол-во акторов мешающих строительству*/
	int CountActor = 0;
	void SetMaterial(int material);
	bool IsBuilding = false;
	void SetCollisionProfile(FName CollProfile) const;
	
	float Health = 100;
	float Armor = 100;
	
	/* кол-во юнитов в здании*/
	int countUnit = 0;
	int MaxCountUnit = 0;
	void SetMaxCountUnit(int value) {MaxCountUnit = value;};
	/* юниты в здании*/
	TArray<ABaseUnitCharacter*> Unit;
	/*Мэши дома для поэтапного строительства*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Building")
	TArray<UStaticMesh*> BlockBuild;
	FTimerHandle TimerBuilding;
	FTimerHandle TimerResourse;
	void StartBuilding();
	
	/* Текущий эиап строительства*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Building")
	int NumberStageBuiding = 0;
	/* Кол-во этапов строительства всего*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Building")
	int MaxNumberStageBuiding = 0;

	/* Очки строительства*/
	int ScoreBuilding;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Building")
	int MaxScoreBuilding = 3;
	/*Очки строительства добавляемые за один ход*/
	int PointBuilding = 1;

	void SetMeshBuild(int NumberStageBuilding);
	virtual void ResourseExtraction();
	
	TMap<ETypeResourse, int> Storage;
	/*Ресурсов для строительства достаточно?*/
	bool CountResourseOK = false;

	bool isCountResourseOK();
	
	
	
private:
	void ResourseExtractionStart();
	ABasePlayerController* BasePlayerController;
	bool BuildingStart = false;
};

enum BuildState
{
	StartBuilding,
	FirstStage,
	SecondStage,
	FinalStage
};


