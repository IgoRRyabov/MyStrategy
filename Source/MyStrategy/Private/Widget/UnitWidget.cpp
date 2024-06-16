// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/UnitWidget.h"
#include "BaseUnitCharacter.h"


#include "BasePlayerController.h"

void UUnitWidget::HealingUnitButton(float healthValue)
{
	if(ActiveHealing) return;
	
	if(OwnerUnit)
	{
		ActiveHealing = true;
		OwnerUnit->HealingUnit();
		UE_LOG(LogTemp, Log, TEXT("Healing Button Start"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Healing Button Error"));
	}
}

void UUnitWidget::SetOwnerUnit(ABaseUnitCharacter* OwnerUnitValue)
{
	OwnerUnit = OwnerUnitValue;
}
