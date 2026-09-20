#include "HUDMinimap.h"
#include "Kismet/GameplayStatics.h" 
#include "MinimapIcon.h"
#include "PlayerSubsystem.h"
#include "Kismet/KismetRenderingLibrary.h"

void UHUDMinimap::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (const TObjectPtr<UWorld> CurrentWorld = GetWorld())
	{
		PlayerSubsystem = CurrentWorld->GetSubsystem<UPlayerSubsystem>();
		
		CameraManager = UGameplayStatics::GetPlayerCameraManager(CurrentWorld, 0);
	}

	if (IsValid(MainCanvasPanel))
	{
		MainCanvasPanel->SetClipping(EWidgetClipping::ClipToBounds);
	}
}

void UHUDMinimap::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(PlayerSubsystem))
	{
		MakeIcons(PlayerSubsystem->GetMaxBots());
	}
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
	if (IsValid(CameraManager))
	{
		CameraYaw = CameraManager->GetCameraRotation().Yaw;
	}
}

void UHUDMinimap::UpdatePlayerLocation()
{
	if (IsValid(PlayerSubsystem))
	{
		PlayerSubsystem->TryGetMainPlayerLocation(MainPlayerPosition);
	}
}

void UHUDMinimap::MakeIcons(const int NewIconAmount)
{
	IconPool.Reserve(IconPool.Num() + NewIconAmount);
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
	if (!IsValid(MinimapIconClass))
	{
		return nullptr;
	}

	const TObjectPtr<UMinimapIcon> NewIconObject = NewObject<UMinimapIcon>(this, MinimapIconClass);
	if (!IsValid(NewIconObject))
	{
		return nullptr;
	}

	NewIconObject->InitIcon(IconMaterialBase, MinimapIconsRenderTarget);

	return NewIconObject;
}

void UHUDMinimap::UpdateIcons()
{
	if (!IsValid(PlayerSubsystem))
	{
		return;
	}

	const TArray<TWeakObjectPtr<UObject>>& PlayerIconInterfaces = PlayerSubsystem->GetMapDisplayArray();

	// Check if extra minimap icons are needed
	if (IconPool.Num() < PlayerIconInterfaces.Num())
	{
		const int32 NewIconsNeeded = PlayerIconInterfaces.Num() - IconPool.Num();
		MakeIcons(NewIconsNeeded);
	}

	if (!IsValid(MinimapIconsRenderTarget))
	{
		return;
	}

	UKismetRenderingLibrary::ClearRenderTarget2D(GetWorld(), MinimapIconsRenderTarget, FLinearColor::Black);

	for (size_t i = 0; i < IconPool.Num(); i++)
	{
		TObjectPtr<UMinimapIcon> MinimapIcon = IconPool[i];
		if (!MinimapIcon)
		{
			continue;
		}

		// If the player icons have changed, update the icon's 
		// MinimapIconable weak pointers
		if (PlayerSubsystem->HasDisplayArrayChanged())
		{
			if (PlayerIconInterfaces.IsValidIndex(i))
			{
				IconPool[i]->SetInterfacePtr(PlayerIconInterfaces[i]);
			}
			else
			{
				IconPool[i]->SetIconEnabled(false);
			}
		}

		if (MinimapIcon->IsIconEnabled())
		{
			MinimapIcon->UpdateIcon(MainPlayerPosition, CameraYaw);
		}
	}

	PlayerSubsystem->SetDisplayArrayUnchanged();
}
