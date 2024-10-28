#include "UI/BaseHUD.h"

#include "Blueprint/UserWidget.h"

ABaseHUD::ABaseHUD()
{
	MainDisplayWidget = CreateDefaultSubobject<UUserWidget>("Main Display Widget");
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();
	check(MainDisplayWidget);
	
	CreateWidget(MainDisplayWidget);
	MainDisplayWidget->AddToViewport();
}
