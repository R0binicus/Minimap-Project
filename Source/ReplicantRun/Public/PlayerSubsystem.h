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

protected:
	UPROPERTY()
	TArray<TWeakObjectPtr<UObject>> PlayerRefArray;

	UPROPERTY()
	TArray<TWeakObjectPtr<UObject>> MapDisplayArray;

	UPROPERTY()
	bool bDisplayArrayChanged;

	const int MaxBotCount = 8;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player Subsystem",
		meta = (ToolTip = "Returns the maximum number of robots that can be present in the level"))
	int GetMaxBots() const { return MaxBotCount; }

	UFUNCTION()
	const TArray<TWeakObjectPtr<UObject>>& GetMapDisplayArray() const { return MapDisplayArray; }

	UFUNCTION()
	bool HasDisplayArrayChanged() const { return bDisplayArrayChanged; }

	UFUNCTION()
	void SetDisplayArrayUnchanged();

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem",
		meta = (ToolTip = "Registers player for use in the subsystem"))
	void AddPlayer(const TScriptInterface<IMinimapIconable>& Player);

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem",
		meta = (ToolTip = "Registers player to be displayed as an icon in the minimap"))
	void EnableMapDisplay(const TScriptInterface<IMinimapIconable>& Player);

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem",
		meta = (ToolTip = "Unregisters player for use in the subsystem and minimap"))
	void RemovePlayer(const TScriptInterface<IMinimapIconable>& Player);

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem",
		meta = (ToolTip = "Modifies FVector with out reference parameter, returns false and ZeroVector if fails"))
	bool TryGetMainPlayerLocation(FVector& Location);

private:
	void RemoveInterfaceFromArray(TArray<TWeakObjectPtr<UObject>>& Array, const TScriptInterface<IMinimapIconable>& PlayerInterface);
};
