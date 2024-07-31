#pragma once

#include "Widget/BuildingWidget.h"

#include "BuildingIconWidget.h"
#include "ObjectForBuilding.h"

UBuildingWidget::UBuildingWidget()
{
	//UBuild = CreateDefaultSubobject<UBuildingIconWidget>("");
}

void UBuildingWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	
	//AddVertexIconBuild(UBuild);
}

void UBuildingWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	
}

void UBuildingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(!ObjectDataHandle.IsNull())
	{
		ObjectDataHandle.DataTable->GetAllRows("", BuildingObjectData);
		int count = 0;
		for (auto Ref : BuildingObjectData)
		{
			//RefBuildingIconWidget->SetIcon(Ref->IconBuild);
			
			
			if(count == BuildingIconWidgets.Max()) return;
			
			if(BuildingIconWidgets[count])
			{
				BuildingIconWidgets[count]->SetIcon(Ref->IconBuild);
				BuildingIconWidgets[count]->SetName(Ref->NameBuilding);
				AddVertexIconBuild(BuildingIconWidgets[count]);
			}
			
			count++;
		}
	}
}

