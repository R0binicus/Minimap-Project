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
	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	void SetCanvasSlot(UCanvasPanelSlot* NewCanvasSlot);

	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	bool IsIconDisabled() const { return bIconDisabled; }

	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	void SetIconDisabled(bool bDisabled);

	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	void UpdateIcon(const FVector& MainPlayerPosition, const FIconDisplayData& DisplayData, const float& CameraYaw);

protected:
	UPROPERTY()
	TWeakObjectPtr<UObject> IconInterfacePtr = nullptr;

	// Bind Widget
	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icon", meta = (BindWidget))
	TObjectPtr<UImage> IconImage;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icon")
	bool bIconDisabled = true;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icon")
	TObjectPtr<UCanvasPanelSlot> CanvasSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Minimap Icon")
	float IconLocationMultiplier = 0.1f;

	const int32 RightAngleDegrees = 90;

	// Update
	TObjectPtr<UMaterialInstanceDynamic> CurrentIconMaterial = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	bool UpdateIconTransform(const FVector& MainPlayerPosition, const FVector& IconPosition, const float& CameraYaw);

	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	bool UpdateIconImage(UMaterialInstanceDynamic* IconMaterial);
};
