// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PlayerSybsystem.generated.h"

/**
 * Used to keep track of player bots
 * both the one controlled by the player and the ones not
 */
UCLASS()
class REPLICANTRUN_API UPlayerSybsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	// End USubsystem
	void IncrementResourceStat();
private:
	// All my variables
};
