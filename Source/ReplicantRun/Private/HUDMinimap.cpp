#include "HUDMinimap.h"
#include "Kismet/GameplayStatics.h" 
#include "Components/CanvasPanelSlot.h" 
#include "MinimapIcon.h"
#include "PlayerSubsystem.h"

void UHUDMinimap::NativeOnInitialized()
{

}

void UHUDMinimap::NativePreConstruct()
{
	const TObjectPtr<UWorld> CurrentWorld = GetWorld();
	if (CurrentWorld)
	{
		PlayerSubsystem = CurrentWorld->GetSubsystem<UPlayerSubsystem>();

		CameraManager = UGameplayStatics::GetPlayerCameraManager(CurrentWorld, 0);
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

	IconCanvasPanel->ClearChildren();
	TArray<FVector> IconLocations = PlayerSubsystem->GetMapIconLocations();

	for (size_t i = 0; i < IconLocations.Num(); i++)
	{
		CreateIcon(IconLocations[i]);
	}
	IconCanvasPanel->SetRenderTransformAngle(-(CameraYaw-90));
}

void UHUDMinimap::CreateIcon(const FVector Location)
{
	if (!MinimapIconClass)
	{
		return;
	}

	if (!IconCanvasPanel)
	{
		return;
	}

	if (!MinimapImage)
	{
		return;
	}

	const TObjectPtr<UMinimapIcon> NewIconWidget = CreateWidget<UMinimapIcon>(GetWorld(), MinimapIconClass);

	if (!NewIconWidget)
	{
		return;
	}

	const TObjectPtr<UCanvasPanelSlot> CanvasSlot = IconCanvasPanel->AddChildToCanvas(NewIconWidget);

	if (!CanvasSlot)
	{
		return;
	}

	CanvasSlot->SetAlignment(FVector2D(AnchorValue, AnchorValue));
	CanvasSlot->SetAnchors(FAnchors(AnchorValue));
	CanvasSlot->SetPosition(FVector2D((MainPlayerLocation - Location) * IconLocationMultiplier));
	NewIconWidget->SetRenderTransformAngle(-((1-CameraYaw)+90));
}
