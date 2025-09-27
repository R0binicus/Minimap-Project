#include "PlayerSubsystem.h"
#include "UObject/WeakInterfacePtr.h"

// Add player to PlayerRefArray
void UPlayerSubsystem::AddPlayer(const TScriptInterface<IMinimapIconable> PlayerInterface)
{
	if (PlayerRefArray == nullptr)
	{
		return;
	}

	UObject* PlayerObj = PlayerInterface.GetObject();

	if (!PlayerObj)
	{
		return;
	}

	if (!PlayerObj->Implements<UMinimapIconable>())
	{
		return;
	}

	PlayerRefArray->Add(PlayerObj);
}

// Add player to MapDisplayArray
void UPlayerSubsystem::EnableMapDisplay(const TScriptInterface<IMinimapIconable> PlayerInterface)
{
	if (MapDisplayArray == nullptr)
	{
		return;
	}

	UObject* PlayerObj = PlayerInterface.GetObject();

	if (!PlayerObj)
	{
		return;
	}

	if (!PlayerObj->Implements<UMinimapIconable>())
	{
		return;
	}

	MapDisplayArray->Add(PlayerObj);
}

void UPlayerSubsystem::RemovePlayer(const TScriptInterface<IMinimapIconable> PlayerInterface)
{
	RemoveInterfaceFromArray(PlayerRefArray, PlayerInterface);
	RemoveInterfaceFromArray(MapDisplayArray, PlayerInterface);
}

// Access gets relevant interface's GetMapIconData and returns them as an array
TArray<FIconDisplayData> UPlayerSubsystem::GetMapIconData()
{
	TArray<FIconDisplayData> IconDataArray;

	if (MapDisplayArray == nullptr)
	{
		return IconDataArray;
	}

	TWeakObjectPtr<UObject> PlayerPtr;

	for (size_t i = 0; i < MapDisplayArray->Num(); i++)
	{
		// Too many validation checks???
		if (!MapDisplayArray->IsValidIndex(i))
		{
			continue;
		}

		PlayerPtr = (*MapDisplayArray)[i];

		if (PlayerPtr == nullptr)
		{
			continue;
		}

		if (!PlayerPtr->Implements<UMinimapIconable>())
		{
			continue;
		}

		IconDataArray.Add(IMinimapIconable::Execute_GetIconDisplayData(PlayerPtr.Get()));
	}
	return IconDataArray;
}

// Access gets relevant interface's GetObjectPosition and returns them as an array
TArray<FVector> UPlayerSubsystem::GetMapIconLocations()
{
	TArray<FVector> IconPositionArray;

	if (MapDisplayArray == nullptr)
	{
		return IconPositionArray;
	}

	TWeakObjectPtr<UObject> PlayerPtr;

	for (size_t i = 0; i < MapDisplayArray->Num(); i++)
	{
		// Too many validation checks???
		if (!MapDisplayArray->IsValidIndex(i))
		{
			continue;
		}

		PlayerPtr = (*MapDisplayArray)[i];

		if (PlayerPtr == nullptr)
		{
			continue;
		}

		if (!PlayerPtr->Implements<UMinimapIconable>())
		{
			continue;
		}

		// IconPostionArray.Add((*MapDisplayArray)[i]->GetObjectPostion());
		//TArray<TWeakObjectPtr<UObject>> Array2 = *MapDisplayArray;
		//TWeakObjectPtr<UObject> obj = Array2[i];

		//IconPositionArray.Add(IMinimapIconable::Execute_GetObjectPostion(obj.Get()));
		IconPositionArray.Add(IMinimapIconable::Execute_GetObjectPosition(PlayerPtr.Get()));
	}
	return IconPositionArray;
}

FVector UPlayerSubsystem::GetMainPlayerLocation()
{
	if (PlayerRefArray == nullptr)
	{
		return FVector();
	}
	if (MapDisplayArray == nullptr)
	{
		return FVector();
	}

	TArray<TWeakObjectPtr<UObject>> RefArray2 = *PlayerRefArray;
	TArray<TWeakObjectPtr<UObject>> DisplayArray2 = *MapDisplayArray;

	TWeakObjectPtr<UObject> PlayerPtr;

	for (size_t i = 0; i < PlayerRefArray->Num(); i++)
	{
		PlayerPtr = (*PlayerRefArray)[i];
		if (!DisplayArray2.Contains(PlayerPtr))
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

void UPlayerSubsystem::RemoveInterfaceFromArray(TArray<TWeakObjectPtr<UObject>>* Array, const TScriptInterface<IMinimapIconable> PlayerInterface)
{
	if (Array == nullptr)
	{
		return;
	}

	// Why does this not work??
	/*if (!Array->Contains(PlayerInterface))
	{
		return;
	}*/

	UObject* PlayerObj = PlayerInterface.GetObject();

	if (!PlayerObj)
	{
		return;
	}

	if (!PlayerObj->Implements<UMinimapIconable>())
	{
		return;
	}

	// Don't remove if it's not in the array
	TArray<TWeakObjectPtr<UObject>> Array2 = *Array;
	if (!Array2.Contains(PlayerObj))
	{
		return;
	}
	Array->Remove(PlayerObj);
}
