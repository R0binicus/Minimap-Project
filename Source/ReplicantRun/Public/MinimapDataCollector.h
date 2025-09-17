// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MinimapDataCollector.generated.h"

class UMaterialParameterCollection;

UCLASS()
class REPLICANTRUN_API AMinimapDataCollector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMinimapDataCollector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Minimap material references
	UPROPERTY(EditAnywhere, Category = "Minimap")
	UMaterialParameterCollection* MaterialParams;

	UPROPERTY()
	UMaterialParameterCollectionInstance* MaterialParamInstance;

	// Minimap Values
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Minimap")
	float MinimapDistanceWidth = 50000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
	float ScaleMultiplier = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
	float ScaleOffset = 0.475f;

	// Values for material scale and offset:
	// 3.0 -1.0,    2.5 -0.75,     2.0 -0.5,     0.4 0.3,    0.35   0.325,    0.3 0.35,    0.25 0.375,    0.2 0.4,    0.15 0.425,    0.1 0.45,    0.05 0.475

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
	float XPosOffset = 0.9405f; // Originally 1 - 0.0595

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
	float YPosOffset = 0.f; // Now unused

	// Set Minimap Material Parameter Functions
	void SetMinimapInitialValues();

	void UpdateMinimapParamValues();

	void SetMinimapCentre();

	void SetMinimapRotation();
};
