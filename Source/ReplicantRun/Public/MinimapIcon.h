#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "MinimapIcon.generated.h"

/**
 * 
 */
UCLASS()
class REPLICANTRUN_API UMinimapIcon : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	void SetIconImage(UMaterialInstanceDynamic* NewImageMat);

	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	bool GetIconDisabled();

	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	void SetIconDisabled(bool bDisabled);

	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	void SetCanvasSlot(UCanvasPanelSlot* NewCanvasSlot);

	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	void UpdateIcon(const FVector& MainPlayerPosition, const FIconDisplayData& DisplayData, const float& CameraYaw);

	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	UCanvasPanelSlot* GetCanvasSlot();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icon", meta = (BindWidget))
	TObjectPtr<UImage> IconImage;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icon")
	bool bIconDisabled = true;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icon")
	TObjectPtr<UCanvasPanelSlot> CanvasSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Minimap Icon")
	float IconLocationMultiplier = 0.1f;

	const int32 RightAngleDegrees = 90;

	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	bool UpdateIconTransform(const FVector& MainPlayerPosition, const FVector& IconPosition, const float& CameraYaw);

	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	bool UpdateDisplayImage(UMaterialInstanceDynamic* IconMaterial);
};
