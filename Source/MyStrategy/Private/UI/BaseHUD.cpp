#include "UI/BaseHUD.h"

#include "Blueprint/UserWidget.h"

ABaseHUD::ABaseHUD()
{
	MainDisplayWidget = CreateDefaultSubobject<UMainDisplayWidget>("Main Display Widget");
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();
	check(MainDisplayWidget);
	
	// CreateWidget(MainDisplayWidget);
	// MainDisplayWidget->AddToViewport();
}

void ABaseHUD::SetResourseComponent(UManagerResoursesComponent* MComponent)
{
	ManagerResoursesComponent = MComponent;
	ManagerResoursesComponent->DelegateUpdateResourse.AddDynamic(MainDisplayWidget, &UMainDisplayWidget::UpdateRes);
}
