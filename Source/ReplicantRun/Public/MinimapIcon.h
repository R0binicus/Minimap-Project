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
	UFUNCTION(BlueprintCallable, Category = "Minimap Icons")
	void SetIconImage(UMaterialInstanceDynamic* NewImageMat);

	UFUNCTION(BlueprintCallable, Category = "Minimap Icons")
	bool GetIconDisabled();

	UFUNCTION(BlueprintCallable, Category = "Minimap Icons")
	void SetIconDisabled(bool bDisabled);

	UFUNCTION(BlueprintCallable, Category = "Minimap Icons")
	void SetCanvasSlot(UCanvasPanelSlot* NewCanvasSlot);

	UFUNCTION(BlueprintCallable, Category = "Minimap Icons")
	UCanvasPanelSlot* GetCanvasSlot();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icon", meta = (BindWidget))
	TObjectPtr<UImage> IconImage;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icon")
	bool bIconDisabled = true;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icon")
	TObjectPtr<UCanvasPanelSlot> CanvasSlot;
};
