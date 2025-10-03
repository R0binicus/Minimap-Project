#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "HUDMinimap.generated.h"

class UPlayerSubsystem;
class UMinimapIcon;
struct FIconDisplayData;
;

/**
 * Used to create and update the icons on the minimap
 */
UCLASS()
class REPLICANTRUN_API UHUDMinimap : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Minimap Icons")
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	void NativeTick_Implementation(const FGeometry& MyGeometry, float InDeltaTime);

protected:
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

	UFUNCTION(BlueprintCallable, Category = "Minimap Icons")
	void UpdateCameraYaw();

	UFUNCTION(BlueprintCallable, Category = "Minimap Icons")
	void UpdatePlayerLocation();

	// Constant
	const int32 RightAngleDegrees = 90;

	const float AnchorValue = 0.5f;

	// Modifiable in editor
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Minimap Icons")
	float MinimapIconCutoffWidth = 115.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Minimap Icons")
	TSubclassOf<UMinimapIcon> MinimapIconClass = nullptr;

	// Bind Widget
	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icons", meta = (BindWidget))
	TObjectPtr<UCanvasPanel> MainCanvasPanel;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icons", meta = (BindWidget))
	TObjectPtr<UCanvasPanel> IconCanvasPanel;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icons", meta = (BindWidget))
	TObjectPtr<UImage> MinimapImage;

	// Icon Object Pooling
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Minimap Icons")
	int DefaultIconNum = 7;

	UPROPERTY()
	TArray<TObjectPtr<UMinimapIcon>> IconPool;

	// Create Icons
	UFUNCTION(BlueprintCallable, Category = "Minimap Icons")
	void MakeIcons(int NewIconAmount);

	UFUNCTION(BlueprintCallable, Category = "Minimap Icons")
	UMinimapIcon* CreateIcon();

	// Update Icons
	UFUNCTION(BlueprintCallable, Category = "Minimap Icons")
	void UpdateIcons();

	// Disable and reenable icons
	UFUNCTION(BlueprintCallable, Category = "Minimap Icons")
	UMinimapIcon* GetDisabledIcon();

	UFUNCTION(BlueprintCallable, Category = "Minimap Icons")
	bool HasDisabledIcon();
};
