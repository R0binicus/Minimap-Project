#include "MinimapIcon.h"
#include "IconDisplayData.h"

void UMinimapIcon::SetCanvasSlot(UCanvasPanelSlot* NewCanvasSlot)
{
	CanvasSlot = NewCanvasSlot;
}

void UMinimapIcon::SetIconDisabled(bool bDisabled)
{
	bIconDisabled = bDisabled;
	if (bIconDisabled)
	{
		SetVisibility(ESlateVisibility::Collapsed);
		IconImage = nullptr;
		CurrentIconMaterial = nullptr;
	}
	else
	{
		SetVisibility(ESlateVisibility::Visible);
	}
}

void UMinimapIcon::UpdateIcon(const FVector& MainPlayerPosition, const FIconDisplayData& DisplayData, const float& CameraYaw)
{
	UpdateIconTransform(MainPlayerPosition, DisplayData.IconPosition, CameraYaw);
	UpdateIconImage(DisplayData.IconMaterial);
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

bool UMinimapIcon::UpdateIconImage(UMaterialInstanceDynamic* IconMaterial)
{
	if (!IconMaterial)
	{
		return false;
	}

	if (!IconImage)
	{
		return false;
	}

	if (IconMaterial != CurrentIconMaterial)
	{
		IconImage->SetBrushFromMaterial(IconMaterial);
		CurrentIconMaterial = IconMaterial;
	}

	return true;
}
