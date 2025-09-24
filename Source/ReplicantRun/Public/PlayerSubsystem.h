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
	//TArray<TWeakInterfacePtr<IMinimapIconable>>* PlayerRefArray = new TArray<TWeakInterfacePtr<IMinimapIconable>>;
	//TArray<TWeakInterfacePtr<IMinimapIconable>>* MapDisplayArray = new TArray<TWeakInterfacePtr<IMinimapIconable>>;
	TArray<TWeakObjectPtr<UObject>>* PlayerRefArray = new TArray<TWeakObjectPtr<UObject>>;
	TArray<TWeakObjectPtr<UObject>>* MapDisplayArray = new TArray<TWeakObjectPtr<UObject>>;
	
	
public:
	 // Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	 // End USubsystem
	virtual void Deinitialize() override;
	
	// When player is created/destroyed add/remove from list
	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	void AddPlayer(UObject* PlayerInterface);

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	void EnableMapDisplay(UObject* PlayerInterface);

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	void RemovePlayer(UObject* PlayerInterface);

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	TArray<FIconDisplayData> GetMapIconData();

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	TArray<FVector> GetMapIconLocations();

	/*UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	FVector GetMainPlayerLocation();*/

private:
	void RemoveInterfaceFromArray(TArray<TWeakObjectPtr<UObject>>* Array, UObject* PlayerInterface);
};
