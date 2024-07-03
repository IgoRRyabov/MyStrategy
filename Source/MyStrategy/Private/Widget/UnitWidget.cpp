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
	}
}