#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "HUDMinimap.generated.h"

class UPlayerSubsystem;
class UMinimapIcon;

/**
 * 
 */
UCLASS()
class REPLICANTRUN_API UHUDMinimap : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeOnInitialized() override;

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
	FVector MainPlayerLocation;

	// Constant
	const int32 RightAngleDegrees = 90;

	const float AnchorValue = 0.5f;

	// Modifiable in editor
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Minimap Icons")
	float MinimapIconCutoffWidth = 115.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Minimap Icons")
	float IconLocationMultiplier = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Minimap Icons")
	TSubclassOf<UMinimapIcon> MinimapIconClass = nullptr;

	// Bind Widget
	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icons", meta = (BindWidget))
	TObjectPtr<UCanvasPanel> IconCanvasPanel;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icons", meta = (BindWidget))
	TObjectPtr<UImage> MinimapImage;

	UFUNCTION(BlueprintCallable, Category = "Minimap Icons")
	void SetCameraYaw();

	UFUNCTION(BlueprintCallable, Category = "Minimap Icons")
	void SetPlayerLocation();
};
