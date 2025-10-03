#include "MinimapIcon.h"
#include "IconDisplayData.h"

void UMinimapIcon::SetIconImage(UMaterialInstanceDynamic* NewImageMat)
{
	if (!NewImageMat)
	{
		return;
	}

	if (!IconImage)
	{
		return;
	}
	
	IconImage->SetBrushFromMaterial(NewImageMat);
}

bool UMinimapIcon::GetIconDisabled()
{
	return bIconDisabled;
}

void UMinimapIcon::SetIconDisabled(bool bDisabled)
{
	bIconDisabled = bDisabled;
	if (bIconDisabled)
	{

	}
	else
	{

	}
}

void UMinimapIcon::SetCanvasSlot(UCanvasPanelSlot* NewCanvasSlot)
{
	CanvasSlot = NewCanvasSlot;
}

void UMinimapIcon::UpdateIcon(const FVector& MainPlayerPosition, const FIconDisplayData& DisplayData, const float& CameraYaw)
{
	// Try to update icon, if it fails hide the icon
	if (UpdateIconTransform(MainPlayerPosition, DisplayData.IconPosition, CameraYaw) 
		&& UpdateDisplayImage(DisplayData.IconMaterial))
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}
}

UCanvasPanelSlot* UMinimapIcon::GetCanvasSlot()
{
	return CanvasSlot;
}

bool UMinimapIcon::UpdateIconTransform(const FVector& MainPlayerPosition, const FVector& IconPosition, const float& CameraYaw)
{
	if (!CanvasSlot)
	{
		return false;
	}

	CanvasSlot->SetPosition(FVector2D((MainPlayerPosition - IconPosition) * IconLocationMultiplier));
	SetRenderTransformAngle(CameraYaw - RightAngleDegrees);

	return true;
}

bool UMinimapIcon::UpdateDisplayImage(UMaterialInstanceDynamic* IconMaterial)
{
	if (!IconMaterial)
	{
		return false;
	}

	SetIconImage(IconMaterial);

	return true;
}
