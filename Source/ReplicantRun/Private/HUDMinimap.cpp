#include "HUDMinimap.h"
#include "Kismet/GameplayStatics.h" 
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
