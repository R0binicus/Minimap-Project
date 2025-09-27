#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDMinimap.generated.h"

/**
 * 
 */
UCLASS()
class REPLICANTRUN_API UHUDMinimap : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap Icons")
	float CameraYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap Icons")
	float MinimapIconCutoffWidth = 115.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap Icons")
	FVector MainPlayerLocation;
};
