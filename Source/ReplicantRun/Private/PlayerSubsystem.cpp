
#include "PlayerSubsystem.h"

void UPlayerSubsystem::AddPlayer(const TScriptInterface<IMinimapIconable>& PlayerInterface)
{
	PlayerRefArray.Add(PlayerInterface.GetObject());
}

void UPlayerSubsystem::EnableMapDisplay(const TScriptInterface<IMinimapIconable>& PlayerInterface)
{
	MapDisplayArray.Add(PlayerInterface.GetObject());

	IconDataArray.AddUninitialized();
}

void UPlayerSubsystem::RemovePlayer(const TScriptInterface<IMinimapIconable>& PlayerInterface)
{
	RemoveInterfaceFromArray(PlayerRefArray, PlayerInterface);
	RemoveInterfaceFromArray(MapDisplayArray, PlayerInterface);

	if (IconDataArray.IsValidIndex(0))
	{
		IconDataArray.RemoveAt(0);
	}
}

const TArray<FIconDisplayData>& UPlayerSubsystem::GetMapIconData()
{
	TWeakObjectPtr<UObject> PlayerPtr;

	for (size_t i = 0; i < MapDisplayArray.Num(); i++)
	{
		PlayerPtr = MapDisplayArray[i];

		if (TStrongObjectPtr<UObject> LockedObserver = PlayerPtr.Pin())
		{
			IconDataArray[i] = IMinimapIconable::Execute_GetIconDisplayData(LockedObserver.Get());
		}
	}
	return IconDataArray;
}

bool UPlayerSubsystem::TryGetMainPlayerLocation(FVector& Location)
{
	TWeakObjectPtr<UObject> PlayerPtr;

	for (size_t i = 0; i < PlayerRefArray.Num(); i++)
	{
		PlayerPtr = PlayerRefArray[i];

		// Get player NOT contained in MapDisplayArray, which is the main player
		if (!MapDisplayArray.Contains(PlayerPtr))
		{
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
