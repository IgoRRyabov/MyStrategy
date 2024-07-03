#include "Widget/BuildingIconWidget.h"

#include "BasePlayerController.h"
#include "BuildComponent.h"

void UBuildingIconWidget::Start()
{
	const auto a = GetOwningPlayer();
	auto b = Cast<ABasePlayerController>(a);
	const auto c = b->GetBuildComponent();
	c->StartBuilding(NameBuilding);
}
