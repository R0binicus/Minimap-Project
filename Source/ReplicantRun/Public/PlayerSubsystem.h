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
	TArray<TWeakInterfacePtr<IMinimapIconable>> PlayerList[6];
	
public:
	 // Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	 // End USubsystem
	virtual void Deinitialize() override;
	
	// When player is created/destroyed add/remove from list
	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	void AddPlayer();

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	void RemovePlayer();

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	void EnableMapDisplay();

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	TArray<FIconDisplayData> GetMapIconData();
};
