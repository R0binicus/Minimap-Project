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

	UPROPERTY()
	TArray<FIconDisplayData> IconDataArray;

	UPROPERTY()
	bool bDisplayArrayChanged;
	
public:
	UFUNCTION()
	const TArray<TWeakObjectPtr<UObject>>& GetMapDisplayArray() const { return MapDisplayArray; }

	UFUNCTION()
	const bool HasDisplayArrayChanged() const { return bDisplayArrayChanged; }

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	void AddPlayer(const TScriptInterface<IMinimapIconable>& Player);

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	void EnableMapDisplay(const TScriptInterface<IMinimapIconable>& Player);

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	void RemovePlayer(const TScriptInterface<IMinimapIconable>& Player);

	UFUNCTION(BlueprintCallable, Category = "Player Subsystem")
	const TArray<FIconDisplayData>& GetMapIconData();

	UFUNCTION(BlueprintCallable, meta = (ShortToolTip = "Modifies FVector with out reference, returns false and ZeroVector if fails"), Category = "Player Subsystem")
	bool TryGetMainPlayerLocation(FVector& Location);

private:
	void RemoveInterfaceFromArray(TArray<TWeakObjectPtr<UObject>>& Array, const TScriptInterface<IMinimapIconable>& PlayerInterface);
};
