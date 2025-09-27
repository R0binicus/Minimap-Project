
#include "PlayerSubsystem.h"

void UPlayerSubsystem::AddPlayer(const TScriptInterface<IMinimapIconable>& PlayerInterface)
{
	PlayerRefArray.Add(PlayerInterface.GetObject());
}

void UPlayerSubsystem::EnableMapDisplay(const TScriptInterface<IMinimapIconable>& PlayerInterface)
{
	MapDisplayArray.Add(PlayerInterface.GetObject());
}

void UPlayerSubsystem::RemovePlayer(const TScriptInterface<IMinimapIconable>& PlayerInterface)
{
	RemoveInterfaceFromArray(PlayerRefArray, PlayerInterface);
	RemoveInterfaceFromArray(MapDisplayArray, PlayerInterface);
}

TArray<FIconDisplayData> UPlayerSubsystem::GetMapIconData()
{
	TArray<FIconDisplayData> IconDataArray;
	TWeakObjectPtr<UObject> PlayerPtr;

	for (size_t i = 0; i < MapDisplayArray.Num(); i++)
	{
		if (!MapDisplayArray.IsValidIndex(i))
		{
			continue;
		}

		PlayerPtr = MapDisplayArray[i];

		if (PlayerPtr == nullptr)
		{
			continue;
		}

		IconDataArray.Add(IMinimapIconable::Execute_GetIconDisplayData(PlayerPtr.Get()));
	}
	return IconDataArray;
}

TArray<FVector> UPlayerSubsystem::GetMapIconLocations()
{
	TArray<FVector> IconPositionArray;

	TWeakObjectPtr<UObject> PlayerPtr;

	for (size_t i = 0; i < MapDisplayArray.Num(); i++)
	{
		if (!MapDisplayArray.IsValidIndex(i))
		{
			continue;
		}

		PlayerPtr = MapDisplayArray[i];

		if (PlayerPtr == nullptr)
		{
			continue;
		}

		IconPositionArray.Add(IMinimapIconable::Execute_GetObjectPosition(PlayerPtr.Get()));
	}
	return IconPositionArray;
}

FVector UPlayerSubsystem::GetMainPlayerLocation()
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
			return (IMinimapIconable::Execute_GetObjectPosition(PlayerPtr.Get()));
		}
	}

	return FVector();
}

void UPlayerSubsystem::RemoveInterfaceFromArray(TArray<TWeakObjectPtr<UObject>>& Array, const TScriptInterface<IMinimapIconable> PlayerInterface)
{
	UObject* PlayerObj = PlayerInterface.GetObject();

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
