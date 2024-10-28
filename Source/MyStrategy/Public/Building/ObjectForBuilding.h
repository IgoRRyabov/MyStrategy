#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Materials/Material.h"
#include "GameFramework/Actor.h"
#include "GameData.h"
#include "Interface/BuildInterface.h"
#include "Interface/EnterInterface.h"
#include "Interface/ResourceExtractionInterface.h"
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateBuilding, ETypeBuild, TypeBuild);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateResouse, ETypeResourse, TypeResourse, float, value);

UCLASS(Abstract)
class MYSTRATEGY_API AObjectForBuilding : public AActor, public IEnterInterface, public IActiveSelect, public IBuildInterface,
public IResourceExtractionInterface
{
	GENERATED_BODY()
	
public:
	AObjectForBuilding();
	
	FDelegateBuilding OnNewBuilding; // Событие при строительстве дома
	FOnUpdateResouse OnUpdateResouse; // Событие добычи ресурсов
	/*
	 * Получить тип здания
	 */
	ETypeBuild GetTypeBuilding() const {return TypeBuild;}

	/*
	 *Обработка столкновения со зданием
	 */
	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//EnterInterface function
	virtual void InterfaceOverlapBegin(class AActor* OtherActor) override;
	virtual void InterfaceOverlapEnd(class AActor* OtherActor) override;
	virtual bool AddUnits(AActor* unit) override;
	virtual void MinusUnits(AActor* unit) override;

	//ActiveSelect function
	virtual void SetActive() override;
	virtual void DeActive() override;
	virtual void VisibleDecalSet(bool value) override;

	//BuildInterface function
	virtual void RequestResources(ETypeResourse & resType, int & resCount) override;

	// ResourceExtractionInterface function
	virtual void ResourceExtraction() override;
	virtual void AddResource(ETypeResourse & resType, int & resCount) override;
	/// 
	/// @return Здание можно строить?
	UFUNCTION(Blueprintable)
	bool CanBuild() const;

	// Изменение коллизии обекта
	void SetCollisionProfile(FName nameCollision) const {StaticMeshComponent->SetCollisionProfileName("NoCollision");
		BoxComponent->SetCollisionProfileName(nameCollision);};
	void SetDefaultCollision() const{StaticMeshComponent->SetCollisionProfileName("BlockAll");
		BoxComponent->SetCollisionProfileName("OverlapAll");};
	void BuildingFinish();

	void UpdateWarehouse(ETypeResourse & resType, int & resCount);
	/// Проверка пустого места в здании
	bool GetFreeSpace() const {return FreeSpace;};
protected:
	virtual void BeginPlay() override;
	
	/*
	 *	Добавление объектов для Blueprint классов
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Mesh Build object")
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Mesh Build object")
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Material Build object")
	TArray<UMaterial*> MaterialBuilding;

	/*
	 *Тип здания
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Type Build")
	TEnumAsByte<ETypeBuild> TypeBuild;
	
	/*
	 * Ресурсы для строительства
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Resource from building")
	TMap<ETypeResourse, int> ResourseForBuilding;

	/*
	 * Ресурсы внутри здания
	 */
	TMap<ETypeResourse, int> Warehouse;
	/// Максимальное число ресурсов в здании
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Resources")
	int maxCountResource = 150;
	/// Количество ресурсов внутри здания
	int countResources;
	
	/* 
	 * Юниты внутри здания
	 */
	TMap<int, ABaseUnitCharacter*> UnitsInBuiding;

	/// Максимально число юнитов в здании
	int MaxCountUnitInBuilding = 2;
	/// Кол-во юнитов в здании
	int CountUnitInBuilding;
	/// Количество объектов мешающих постройке здания
	int CountObjectOverlap = 0;
	/// Здание построено?
	bool isBuildingBuild = false;

	///Ресурс для добычи
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Resources")
	ETypeResourse ExtractionResource;
	///Количество добываемого ресурса
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Resources")
	int countExtractionResource = 0;
	/// Таймер добычи ресурсов
	FTimerHandle ExtractionResourceTimer;
	/// Здание может добывать ресурсы?
	bool CanExtractResource = false;
	/// В здании есть место?
	bool FreeSpace = true;

	void StartAddResource();

	///Debug
	void printNameUnitsInBuild();
};

