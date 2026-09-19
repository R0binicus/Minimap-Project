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
		const FIconDisplayData& NewDisplayData = IMinimapIconable::Execute_GetIconDisplayData(LockedObserver.Get());

		if (UpdateIconTransform(MainPlayerPosition, NewDisplayData, CameraYaw)
			&& UpdateIconImage(NewDisplayData))
		{
			SetVisibility(ESlateVisibility::Visible);
		}

		DisplayData = NewDisplayData;
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

bool UMinimapIcon::UpdateIconTransform(const FVector& MainPlayerPosition, const FIconDisplayData& NewDisplayData, const float& CameraYaw)
{
	const FVector& IconPosition = NewDisplayData.IconPosition;
	if (!CanvasSlot)
	{
		return false;
	}

	CanvasSlot->SetPosition(FVector2D((MainPlayerPosition - IconPosition) * IconLocationMultiplier));
	SetRenderTransformAngle(CameraYaw - RightAngleDegrees);

	return true;
}

bool UMinimapIcon::UpdateIconImage(const FIconDisplayData& NewDisplayData)
{
	UTexture2D* IconTexture = NewDisplayData.IconTexture;
	if (!IconTexture || !IconImage)
	{
		return false;
	}

	IconMaterial = UMaterialInstanceDynamic::Create(IconMaterialBase, this);
	if (!IconMaterial)
	{
		return false;
	}

	if (IconMaterial != CurrentIconMaterial)
	{
		IconMaterial->SetScalarParameterValue("HueShift", NewDisplayData.IconHueShift);
		IconMaterial->SetTextureParameterValue("BotIcon", IconTexture);
		IconImage->SetBrushFromMaterial(IconMaterial);
		CurrentIconMaterial = IconMaterial;
	}

	return true;
}
