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

	UPROPERTY(EditAnywhere, Category = "Minimap")
	UMaterialParameterCollection* MaterialParams;

	UPROPERTY()
	UMaterialParameterCollectionInstance* MaterialParamInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Minimap")
	float MinimapDistanceWidth = 50000.f;

	void SetMinimapMaterialParams();
};
