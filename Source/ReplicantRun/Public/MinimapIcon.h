#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "MinimapIcon.generated.h"

/**
 * Widget class, which gets displayed on the minimap as an icon
 */
UCLASS()
class REPLICANTRUN_API UMinimapIcon : public UUserWidget
{
	GENERATED_BODY()

public:
	// Initialisation
	UFUNCTION(BlueprintCallable, Category = "Minimap Icon",
		meta = (ToolTip = "Initialises and sets up the icon for use"))
	void InitIcon(UCanvasPanelSlot* NewCanvasSlot);
	
	UFUNCTION(BlueprintCallable, Category = "Minimap Icon",
		meta = (ToolTip = "Sets the icons's canvas slot variable"))
	void SetCanvasSlot(UCanvasPanelSlot* NewCanvasSlot);

	// Enable/disable functions
	UFUNCTION(BlueprintCallable, Category = "Minimap Icon",
		meta = (ToolTip = "Checks if the icon is enabled or disabled"))
	bool IsIconEnabled() const { return bIconEnabled; }

	UFUNCTION(BlueprintCallable, Category = "Minimap Icon",
		meta = (ToolTip = "Disabled and hides "))
	void SetIconEnabled(const bool bEnabled);

	// Update functions
	UFUNCTION(BlueprintCallable, Category = "Minimap Icon",
		meta = (ToolTip = "Updates the icon's location, image and "))
	void UpdateIcon(const FVector& MainPlayerPosition, const float& CameraYaw);

	void SetInterfacePtr(const TWeakObjectPtr<UObject> InterfacePtr);

protected:
	UPROPERTY()
	TWeakObjectPtr<UObject> IconInterfacePtr = nullptr;

	// Bind Widget
	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icon", meta = (BindWidget))
	TObjectPtr<UImage> IconImage;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icon")
	bool bIconEnabled = true;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icon")
	TObjectPtr<UCanvasPanelSlot> CanvasSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Minimap Icon")
	float IconLocationMultiplier = 0.1f;

	// Constants
	const int32 RightAngleDegrees = 90;
	
	const float AnchorValue = 0.5f;

	// Update
	TObjectPtr<UMaterialInstanceDynamic> CurrentIconMaterial = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	bool UpdateIconTransform(const FVector& MainPlayerPosition, const FVector& IconPosition, const float& CameraYaw);

	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	bool UpdateIconImage(UMaterialInstanceDynamic* IconMaterial);
};
