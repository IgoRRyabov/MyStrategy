#include "Widget/MainDisplayWidget.h"
#include "GameData.h"

void UMainDisplayWidget::UpdateRes(ETypeResourse TRes, int value)
{
	if (TRes == ETypeResourse::Gold) SetGoldCount(value);

	UE_LOG(LogTemp, Log, TEXT("___________Resource: %d  ===  %d"), TRes, value);
}

void UMainDisplayWidget::SetGoldCount(int value)
{
	GoldCount = value;
	UpdateEvent();
}

void UMainDisplayWidget::CreateButtonBuildWidget()
{
	
}
