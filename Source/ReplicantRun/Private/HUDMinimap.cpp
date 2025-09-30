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

	for (size_t i = 0; i < DefaultIconNum; i++)
	{
		TObjectPtr<UWidget> Icon = CreateIcon();
		if (!Icon)
		{
			continue;
		}
		IconPool.Add(Icon);
	}
}

void UHUDMinimap::NativeTick_Implementation(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateCameraYaw();
	UpdatePlayerLocation();
	DisplayIcons();
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

	PlayerSubsystem->TryGetMainPlayerLocation(MainPlayerLocation);
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

	TArray<FVector> IconLocations = PlayerSubsystem->GetMapIconLocations();
	TArray<FIconDisplayData> IconData = PlayerSubsystem->GetMapIconData();

	for (size_t i = 0; i < IconPool.Num(); i++)
	{
		if (IconLocations.IsValidIndex(i) && IconLocations.Num() == IconData.Num())
		{
			UpdateIcon(IconPool[i].Get(), IconLocations[i], IconData[i]);
		}
		else
		{
			IconPool[i]->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	IconCanvasPanel->SetRenderTransformAngle(-(CameraYaw - RightAngleDegrees));
}

UWidget* UHUDMinimap::CreateIcon()
{
	if (!ensure(MinimapIconClass))
	{
		return nullptr;
	}

	if (!IconCanvasPanel)
	{
		return nullptr;
	}

	const TObjectPtr<UWidget> NewIconWidget = CreateWidget<UMinimapIcon>(GetWorld(), MinimapIconClass);

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
	NewIconWidget->SetVisibility(ESlateVisibility::Collapsed);

	return NewIconWidget;
}

void UHUDMinimap::UpdateIcon(UWidget* IconWidget, const FVector& Location, const FIconDisplayData& DisplayData)
{
	if (!MinimapIconClass)
	{
		return;
	}

	if (!IconCanvasPanel)
	{
		return;
	}

	if (!IconWidget)
	{
		return;
	}

	const TObjectPtr<UCanvasPanelSlot> CanvasSlot = Cast<UCanvasPanelSlot>(IconWidget->Slot);

	if (CanvasSlot)
	{
		CanvasSlot->SetPosition(FVector2D((MainPlayerLocation - Location) * IconLocationMultiplier));
		IconWidget->SetRenderTransformAngle(-((1 - CameraYaw) + RightAngleDegrees));
		IconWidget->SetVisibility(ESlateVisibility::Visible);
	}

	const TObjectPtr<UMinimapIcon> MinimapIcon = Cast<UMinimapIcon>(IconWidget);

	if (!MinimapIcon)
	{
		return;
	}

	const TObjectPtr<UMaterialInstanceDynamic> IconImage = DisplayData.IconMaterial;

	if (IconImage)
	{
		MinimapIcon->SetIconImage(IconImage);
		MinimapIcon->SetRenderOpacity(1.f);
	}
	else
	{
		MinimapIcon->SetRenderOpacity(0.f);
	}
}