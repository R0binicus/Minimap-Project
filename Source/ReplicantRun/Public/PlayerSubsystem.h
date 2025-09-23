// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MinimapIconable.h"
#include "UObject/WeakInterfacePtr.h"
#include "PlayerSubsystem.generated.h"

/**
 * Used to keep track of player bots
 * both the one controlled by the player and the ones not
 */
UCLASS()
class REPLICANTRUN_API UPlayerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	TArray<TWeakInterfacePtr<IMinimapIconable>>* PlayerRefArray = new TArray<TWeakInterfacePtr<IMinimapIconable>>;
	TArray<TWeakInterfacePtr<IMinimapIconable>>* MapDisplayArray = new TArray<TWeakInterfacePtr<IMinimapIconable>>;;
	
public:
	 // Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	 // End USubsystem
	virtual void Deinitialize() override;
	
	// When player is created/destroyed add/remove from list
	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	void AddPlayer(TScriptInterface<IMinimapIconable> Player);

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	void EnableMapDisplay(TScriptInterface<IMinimapIconable> Player);

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	void RemovePlayer(TScriptInterface<IMinimapIconable> Player);

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	TArray<FIconDisplayData> GetMapIconData();

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	TArray<FVector> GetMapIconLocations();

	/*UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	FVector GetMainPlayerLocation();*/

private:
	void RemoveInterfaceFromArray(TArray<TWeakInterfacePtr<IMinimapIconable>>* Array, TScriptInterface<IMinimapIconable> Player);
};
