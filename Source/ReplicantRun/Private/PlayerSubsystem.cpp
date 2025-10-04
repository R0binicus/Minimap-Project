
#include "PlayerSubsystem.h"

void UPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	PlayerRefArray.Reserve(GetMaxBots());
	MapDisplayArray.Reserve(GetMaxBots());
}

void UPlayerSubsystem::SetDisplayArrayUnchanged()
{
	bDisplayArrayChanged = false;
}

void UPlayerSubsystem::AddPlayer(const TScriptInterface<IMinimapIconable>& PlayerInterface)
{
	PlayerRefArray.Add(PlayerInterface.GetObject());
}

void UPlayerSubsystem::EnableMapDisplay(const TScriptInterface<IMinimapIconable>& PlayerInterface)
{
	MapDisplayArray.Add(PlayerInterface.GetObject());
	bDisplayArrayChanged = true;
}

void UPlayerSubsystem::RemovePlayer(const TScriptInterface<IMinimapIconable>& PlayerInterface)
{
	RemoveInterfaceFromArray(PlayerRefArray, PlayerInterface);
	RemoveInterfaceFromArray(MapDisplayArray, PlayerInterface);
	bDisplayArrayChanged = true;
}

bool UPlayerSubsystem::TryGetMainPlayerLocation(FVector& Location)
{
	TWeakObjectPtr<UObject> PlayerPtr;

	for (size_t i = 0; i < PlayerRefArray.Num(); i++)
	{
		PlayerPtr = PlayerRefArray[i];

		// Get player NOT contained in MapDisplayArray, which is the main player
		if (MapDisplayArray.Contains(PlayerPtr))
		{
			continue;
		}

		if (!(PlayerPtr->Implements<UMinimapIconable>()))
		{
			continue;
		}

		if (TStrongObjectPtr<UObject> LockedObserver = PlayerPtr.Pin())
		{
			Location = IMinimapIconable::Execute_GetObjectPosition(LockedObserver.Get());
			return true;
		}
	}
	Location = FVector::ZeroVector;
	return false;
}

void UPlayerSubsystem::RemoveInterfaceFromArray(TArray<TWeakObjectPtr<UObject>>& Array, const TScriptInterface<IMinimapIconable>& PlayerInterface)
{
	TObjectPtr<UObject> PlayerObj = PlayerInterface.GetObject();

	if (!PlayerObj)
	{
		return;
	}

	if (!Array.Contains(PlayerObj))
	{
		return;
	}

	Array.Remove(PlayerObj);
}
