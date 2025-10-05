#include "MinimapIcon.h"
#include "MinimapIconable.h"
#include "IconDisplayData.h"

void UMinimapIcon::InitIcon(UCanvasPanelSlot* NewCanvasSlot)
{
	if (!NewCanvasSlot)
	{
		return;
	}
	
	SetCanvasSlot(NewCanvasSlot);
	CanvasSlot->SetAlignment(FVector2D(AnchorValue, AnchorValue));
	CanvasSlot->SetAnchors(FAnchors(AnchorValue));
	SetIconEnabled(false);
}

void UMinimapIcon::SetCanvasSlot(UCanvasPanelSlot* NewCanvasSlot)
{
	CanvasSlot = NewCanvasSlot;
}

void UMinimapIcon::SetIconEnabled(const bool bEnabled)
{
	bIconEnabled = bEnabled;
	if (bIconEnabled)
	{
		SetVisibility(ESlateVisibility::Visible);
		
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed);
		CurrentIconMaterial = nullptr;
	}
}

void UMinimapIcon::UpdateIcon(const FVector& MainPlayerPosition, const float& CameraYaw)
{
	if (const TStrongObjectPtr<UObject> LockedObserver = IconInterfacePtr.Pin())
	{
		const FIconDisplayData& DisplayData = IMinimapIconable::Execute_GetIconDisplayData(LockedObserver.Get());

		if (UpdateIconTransform(MainPlayerPosition, DisplayData.IconPosition, CameraYaw)
			&& UpdateIconImage(DisplayData.IconMaterial))
		{
			SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		SetIconEnabled(false);
	}
}

void UMinimapIcon::SetInterfacePtr(const TWeakObjectPtr<UObject> InterfacePtr)
{
	IconInterfacePtr = InterfacePtr;
	SetIconEnabled(true);
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
