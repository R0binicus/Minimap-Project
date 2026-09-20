#pragma once

#include "CoreMinimal.h"
#include "IconDisplayData.h"
#include "MinimapIcon.generated.h"

/**
 * Widget class, which gets displayed on the minimap as an icon
 */
UCLASS()
class REPLICANTRUN_API UMinimapIcon : public UObject
{
	GENERATED_BODY()

public:
	// Initialisation
	UFUNCTION(BlueprintCallable, Category = "Minimap Icon",
		meta = (ToolTip = "Initialises and sets up the icon for use"))
	void InitIcon(UMaterialInterface* IconMaterialBase, UTextureRenderTarget2D* NewIconRenderTarget);
	
	// Enable/disable functions
	UFUNCTION(BlueprintCallable, Category = "Minimap Icon",
		meta = (ToolTip = "Checks if the icon is enabled or disabled"))
	bool IsIconEnabled() const { return bIconEnabled; }

	UFUNCTION(BlueprintCallable, Category = "Minimap Icon",
		meta = (ToolTip = "Shows or hides Icon"))
	void SetIconEnabled(const bool bEnabled);

	// Update functions
	UFUNCTION(BlueprintCallable, Category = "Minimap Icon",
		meta = (ToolTip = "Draws to render target, after updating values"))
	void UpdateIcon(const FVector& MainPlayerPosition, const float CameraYaw);

	void SetInterfacePtr(const TWeakObjectPtr<UObject> InterfacePtr);

protected:
	UPROPERTY()
	TWeakObjectPtr<UObject> IconInterfacePtr = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icon")
	TObjectPtr<UTextureRenderTarget2D> IconRenderTarget;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icon")
	TObjectPtr<UMaterialInstanceDynamic> IconMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap Icon")
	FIconDisplayData DisplayData;

	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icon")
	bool bIconEnabled = true;

	// Update
	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	bool UpdateIconTransform(const FVector& MainPlayerPosition, const FIconDisplayData& NewDisplayData, const float CameraYaw) const;

	UFUNCTION(BlueprintCallable, Category = "Minimap Icon")
	bool UpdateIconImage(const FIconDisplayData& NewDisplayData) const;
};
