#include "HUDMinimap.h"
#include "Kismet/GameplayStatics.h" 
#include "Components/CanvasPanelSlot.h" 
#include "MinimapIcon.h"
#include "PlayerSubsystem.h"

void UHUDMinimap::NativePreConstruct()
{
	const TObjectPtr<UWorld> CurrentWorld = GetWorld();
	if (CurrentWorld)
	{
		PlayerSubsystem = CurrentWorld->GetSubsystem<UPlayerSubsystem>();

		CameraManager = UGameplayStatics::GetPlayerCameraManager(CurrentWorld, 0);
	}

	if (MainCanvasPanel)
	{
		MainCanvasPanel->SetClipping(EWidgetClipping::ClipToBounds);
	}
}

void UHUDMinimap::NativeTick_Implementation(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SetCameraYaw();
	SetPlayerLocation();
	DisplayIcons();
}

void UHUDMinimap::SetCameraYaw()
{
	if (!CameraManager)
	{
		return;
	}

	CameraYaw = CameraManager->GetCameraRotation().Yaw;
}

void UHUDMinimap::SetPlayerLocation()
{
	if (!PlayerSubsystem)
	{
		return;
	}

	MainPlayerLocation = PlayerSubsystem->GetMainPlayerLocation();
}

void UHUDMinimap::DisplayIcons()
{
	if (!PlayerSubsystem)
	{
		return;
	}

	if (!IconCanvasPanel)
	{
		return;
	}

	IconCanvasPanel->ClearChildren();
	TArray<FVector> IconLocations = PlayerSubsystem->GetMapIconLocations();

	for (size_t i = 0; i < IconLocations.Num(); i++)
	{
		CreateIcon(IconLocations[i]);
	}

	IconCanvasPanel->SetRenderTransformAngle(-(CameraYaw-90));

	/*for (size_t i = 0; i < IconCanvasPanel->GetChildrenCount(); i++)
	{
		HideInvalidIcon(IconCanvasPanel->GetChildAt(i));
	}*/
}

const UCanvasPanelSlot* UHUDMinimap::CreateIcon(const FVector Location)
{
	if (!MinimapIconClass)
	{
		return nullptr;
	}

	if (!IconCanvasPanel)
	{
		return nullptr;
	}

	if (!MinimapImage)
	{
		return nullptr;
	}

	const TObjectPtr<UMinimapIcon> NewIconWidget = CreateWidget<UMinimapIcon>(GetWorld(), MinimapIconClass);

	if (!NewIconWidget)
	{
		return nullptr;
	}

	const TObjectPtr<UCanvasPanelSlot> CanvasSlot = IconCanvasPanel->AddChildToCanvas(NewIconWidget);

	if (!CanvasSlot)
	{
		return nullptr;
	}

	CanvasSlot->SetAlignment(FVector2D(AnchorValue, AnchorValue));
	CanvasSlot->SetAnchors(FAnchors(AnchorValue));
	CanvasSlot->SetPosition(FVector2D((MainPlayerLocation - Location) * IconLocationMultiplier));
	NewIconWidget->SetRenderTransformAngle(-((1-CameraYaw)+90));

	return CanvasSlot;
}

//void UHUDMinimap::HideInvalidIcon(UWidget* Icon)
//{
//	if (!Icon)
//	{
//		return;
//	}
//
//	const UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Icon->Slot);
//
//	if (!CanvasSlot)
//	{
//		return;
//	}
//
//	const FVector2D IconPosition = CanvasSlot->GetPosition();
//
//	const float X = IconPosition.X;
//	const float Y = IconPosition.Y;
//
//	if (X >= MinimapIconCutoffWidth || X <= -MinimapIconCutoffWidth || Y >= MinimapIconCutoffWidth || Y <= -MinimapIconCutoffWidth)
//	{
//		Icon->SetVisibility(ESlateVisibility::Collapsed);
//	}
//}
