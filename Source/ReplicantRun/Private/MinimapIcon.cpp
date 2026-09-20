#include "MinimapIcon.h"
#include "MinimapIconable.h"
#include "IconDisplayData.h"
#include "Kismet/KismetRenderingLibrary.h"

void UMinimapIcon::InitIcon(UCanvasPanelSlot* NewCanvasSlot, UMaterialInterface* IconMaterialBase, UTextureRenderTarget2D* NewIconRenderTarget)
{
	if (!IsValid(NewCanvasSlot) || !IsValid(IconImage) || !IsValid(IconMaterialBase))
	{
		return;
	}

	SetCanvasSlot(NewCanvasSlot);
	IconMaterial = UMaterialInstanceDynamic::Create(IconMaterialBase, this);
	CanvasSlot->SetAlignment(FVector2D(AnchorValue, AnchorValue));
	CanvasSlot->SetAnchors(FAnchors(AnchorValue));
	IconImage->SetBrushFromMaterial(IconMaterial);
	IconRenderTarget = NewIconRenderTarget;
	SetVisibility(ESlateVisibility::Collapsed);

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
		//SetVisibility(ESlateVisibility::Visible);

	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed);
		DisplayData = FIconDisplayData(); //Clear stored icon data
	}
}

void UMinimapIcon::UpdateIcon(const FVector& MainPlayerPosition, const float CameraYaw)
{
	if (!IsValid(IconRenderTarget) || !IsValid(IconMaterial))
	{
		return;
	}

	if (const TStrongObjectPtr<UObject> LockedObserver = IconInterfacePtr.Pin())
	{
		const FIconDisplayData& NewDisplayData = IMinimapIconable::Execute_GetIconDisplayData(LockedObserver.Get());

		if (UpdateIconTransform(MainPlayerPosition, NewDisplayData, CameraYaw)
			&& UpdateIconImage(NewDisplayData))
		{
			//SetVisibility(ESlateVisibility::Visible);
		}

		UKismetRenderingLibrary::DrawMaterialToRenderTarget(GetWorld(), IconRenderTarget, IconMaterial);
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

bool UMinimapIcon::UpdateIconTransform(const FVector& MainPlayerPosition, const FIconDisplayData& NewDisplayData, const float CameraYaw)
{
	if (!IsValid(IconMaterial) || !IsValid(CanvasSlot))
	{
		return false;
	}

	const FVector& NewIconPosition = NewDisplayData.IconPosition;
	//CanvasSlot->SetPosition(FVector2D((MainPlayerPosition - NewIconPosition) * IconLocationMultiplier));
	FVector IconLocation = FVector((MainPlayerPosition - NewIconPosition) * IconLocationMultiplier);
	IconLocation = FVector(-IconLocation.Y, IconLocation.X, 0);
	IconMaterial->SetVectorParameterValue("Location", IconLocation);
	IconMaterial->SetScalarParameterValue("Rotation", CameraYaw);

	return true;
}

bool UMinimapIcon::UpdateIconImage(const FIconDisplayData& NewDisplayData)
{
	if (!IsValid(IconMaterial))
	{
		return false;
	}

	const TObjectPtr<UTexture2D> NewIconTexture = NewDisplayData.IconTexture;
	const float NewHueShift = NewDisplayData.IconHueShift;

	if (NewIconTexture != DisplayData.IconTexture)
	{
		IconMaterial->SetTextureParameterValue("BotIcon", NewIconTexture);
	}

	if (NewHueShift != DisplayData.IconHueShift)
	{
		IconMaterial->SetScalarParameterValue("HueShift", NewHueShift);
	}

	return true;
}