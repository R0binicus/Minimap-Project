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

	MakeIcons(DefaultIconNum);
}

void UHUDMinimap::NativeTick_Implementation(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateCameraYaw();
	UpdatePlayerLocation();
	UpdateIcons();
}

void UHUDMinimap::UpdateCameraYaw()
{
	if (!CameraManager)
	{
		return;
	}

	CameraYaw = CameraManager->GetCameraRotation().Yaw;
}

void UHUDMinimap::UpdatePlayerLocation()
{
	if (!PlayerSubsystem)
	{
		return;
	}

	PlayerSubsystem->TryGetMainPlayerLocation(MainPlayerPosition);
}

void UHUDMinimap::MakeIcons(int NewIconAmount)
{
	for (size_t i = 0; i < NewIconAmount; i++)
	{
		const TObjectPtr<UMinimapIcon> Icon = CreateIcon();
		if (!Icon)
		{
			return;
		}
		IconPool.Add(Icon);
	}
}

UMinimapIcon* UHUDMinimap::CreateIcon()
{
	if (!ensure(MinimapIconClass))
	{
		return nullptr;
	}

	if (!IconCanvasPanel)
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

	NewIconWidget->SetCanvasSlot(CanvasSlot);
	CanvasSlot->SetAlignment(FVector2D(AnchorValue, AnchorValue));
	CanvasSlot->SetAnchors(FAnchors(AnchorValue));
	NewIconWidget->SetVisibility(ESlateVisibility::Collapsed);

	return NewIconWidget;
}

void UHUDMinimap::UpdateIcons()
{
	if (!PlayerSubsystem)
	{
		return;
	}

	if (!IconCanvasPanel)
	{
		return;
	}

	const TArray<FIconDisplayData> IconData = PlayerSubsystem->GetMapIconData();

	// Check if extra minimap icons are needed
	if (IconPool.Num() < IconData.Num())
	{
		const int32 NewIconsNeeded = IconData.Num() - IconPool.Num();

		MakeIcons(NewIconsNeeded);
	}

	for (size_t i = 0; i < IconPool.Num(); i++)
	{
		if (!IconData.IsValidIndex(i) || !IconPool.IsValidIndex(i))
		{
			break;
		}

		TObjectPtr<UMinimapIcon> MinimapIcon = IconPool[i];
		if (!MinimapIcon)
		{
			continue;
		}

		MinimapIcon->UpdateIcon(MainPlayerPosition, IconData[i], CameraYaw);
	}

	IconCanvasPanel->SetRenderTransformAngle(RightAngleDegrees - CameraYaw);
}

UMinimapIcon* UHUDMinimap::GetDisabledIcon()
{
	for (size_t i = 0; i < IconPool.Num(); i++)
	{
		if (!IconPool[i])
		{
			continue;
		}

		if (IconPool[i]->IsIconDisabled())
		{
			return IconPool[i];
		}
	}
	return nullptr;
}

bool UHUDMinimap::HasDisabledIcon()
{
	for (size_t i = 0; i < IconPool.Num(); i++)
	{
		if (!IconPool[i])
		{
			continue;
		}

		if (IconPool[i]->IsIconDisabled())
		{
			return true;
		}
	}
	return false;
}
