#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MinimapIconable.h"
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
	UPROPERTY()
	TArray<TWeakObjectPtr<UObject>> PlayerRefArray;

	UPROPERTY()
	TArray<TWeakObjectPtr<UObject>> MapDisplayArray;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	void AddPlayer(const TScriptInterface<IMinimapIconable>& Player);

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	void EnableMapDisplay(const TScriptInterface<IMinimapIconable>& Player);

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	void RemovePlayer(const TScriptInterface<IMinimapIconable>& Player);

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	TArray<FIconDisplayData> GetMapIconData();

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	TArray<FVector> GetMapIconLocations();

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	FVector GetMainPlayerLocation();

private:
	void RemoveInterfaceFromArray(TArray<TWeakObjectPtr<UObject>>& Array, const TScriptInterface<IMinimapIconable>& PlayerInterface);
};
