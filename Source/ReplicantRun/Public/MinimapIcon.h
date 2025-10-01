#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
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

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Minimap Icon", meta = (BindWidget))
	TObjectPtr<UImage> IconImage;
	
};
