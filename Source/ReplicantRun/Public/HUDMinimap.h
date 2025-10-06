#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "HUDMinimap.generated.h"

class UPlayerSubsystem;
class UMinimapIcon;
struct FIconDisplayData;

/**
 * Used to create and update the icons on the minimap
 */
UCLASS()
class REPLICANTRUN_API UHUDMinimap : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativePreConstruct() override;

	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Minimap Icons")
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	void NativeTick_Implementation(const FGeometry& MyGeometry, float InDeltaTime);

	// Set in constructor
	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icons")
	TObjectPtr<UPlayerSubsystem> PlayerSubsystem;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icons")
	TObjectPtr<APlayerCameraManager> CameraManager;

	// Tick Update
	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icons")
	float CameraYaw;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icons")
	FVector MainPlayerPosition;

	UFUNCTION(BlueprintCallable, Category = "Minimap Icons",
		meta = (ToolTip = "Updates the minimap's variable of the current camera rotation"))
	void UpdateCameraYaw();

	UFUNCTION(BlueprintCallable, Category = "Minimap Icons",
		meta = (ToolTip = "Updates the minimap's variable the player's current location"))
	void UpdatePlayerLocation();

	// Constant
	const int32 RightAngleDegrees = 90;

	// Modifiable in editor
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Minimap Icons")
	TSubclassOf<UMinimapIcon> MinimapIconClass = nullptr;

	// Bind Widget
	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icons", meta = (BindWidget))
	TObjectPtr<UCanvasPanel> MainCanvasPanel;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icons", meta = (BindWidget))
	TObjectPtr<UCanvasPanel> IconCanvasPanel;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icons", meta = (BindWidget))
	TObjectPtr<UImage> MinimapImage;

	UPROPERTY()
	TArray<TObjectPtr<UMinimapIcon>> IconPool;

	// Create Icons
	UFUNCTION(BlueprintCallable, Category = "Minimap Icons",
		meta = (ToolTip = "Makes the specified number of icon widgets"))
	void MakeIcons(const int NewIconAmount);

	UFUNCTION(BlueprintCallable, Category = "Minimap Icons",
		meta = (ToolTip = "Creates and initialises an icon"))
	UMinimapIcon* CreateIcon();

	// Update Icons
	UFUNCTION(BlueprintCallable, Category = "Minimap Icons",
		meta = (ToolTip = "Updates all icons' location and image"))
	void UpdateIcons();
};
