#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MinimapDataCollector.generated.h"

class UMaterialParameterCollection;

/**
 * Object placed in the level, which collects data for the minimap
 * then does as much math as possible before passing that info
 * off to the material for final rendering
 */
UCLASS()
class REPLICANTRUN_API AMinimapDataCollector : public AActor
{
	GENERATED_BODY()
	
public:	
	AMinimapDataCollector();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Minimap material references
	UPROPERTY(EditAnywhere, Category = "Minimap")
	TObjectPtr<UMaterialParameterCollection> MaterialParams;

	UPROPERTY()
	TObjectPtr<UMaterialParameterCollectionInstance> MaterialParamInstance;

	UPROPERTY()
	TObjectPtr<UWorld> WorldPtr;

	const int32 DegreesInCircle = 360;

	UPROPERTY()
	float MinimapRotation;

	// Minimap Values
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Minimap")
	float MinimapDistanceWidth = 50000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
	float ScaleMultiplier = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
	float ScaleOffset = 0.475f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
	float XPosOffset = 1.f;

	// Set Minimap Material Parameter Functions
	void SetMinimapInitialValues();

	void UpdateMinimapParamValues();

	void SetPlayerBasedValues();

	void SetMinimapCentre(const TObjectPtr<ACharacter>& PlayerCharacter);

	void SetPlayerIndicatorRotation(const TObjectPtr<ACharacter>& PlayerCharacter);

	void SetMinimapRotation();
};
