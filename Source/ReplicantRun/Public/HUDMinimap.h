#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDMinimap.generated.h"

class UPlayerSubsystem;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap Icons")
	TObjectPtr<UPlayerSubsystem> PlayerSubsystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap Icons")
	TObjectPtr<APlayerCameraManager> CameraManager;

	UFUNCTION(BlueprintCallable, Category = "Minimap Icons")
	void SetCameraYaw();

	UFUNCTION(BlueprintCallable, Category = "Minimap Icons")
	void SetPlayerLocation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap Icons")
	float CameraYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap Icons")
	float MinimapIconCutoffWidth = 115.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap Icons")
	FVector MainPlayerLocation;
};
