// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerSubsystem.h"
#include "UObject/WeakInterfacePtr.h"

void UPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	
}

void UPlayerSubsystem::Deinitialize()
{

}

void UPlayerSubsystem::AddPlayer(TScriptInterface<IMinimapIconable> Player)
{
	if (PlayerRefArray == nullptr)
	{
		return;
	}
	PlayerRefArray->Add(Player.GetInterface());
}


void UPlayerSubsystem::EnableMapDisplay(TScriptInterface<IMinimapIconable> Player)
{
	if (MapDisplayArray == nullptr)
	{
		return;
	}
	MapDisplayArray->Add(Player.GetInterface());
}

void UPlayerSubsystem::RemovePlayer(TScriptInterface<IMinimapIconable> Player)
{
	RemoveInterfaceFromArray(PlayerRefArray, Player);
	RemoveInterfaceFromArray(MapDisplayArray, Player);
}

TArray<FIconDisplayData> UPlayerSubsystem::GetMapIconData()
{
	if (MapDisplayArray == nullptr)
	{
		return TArray<FIconDisplayData>();
	}

	TArray<FIconDisplayData> IconDataArray;

	for (size_t i = 0; i < MapDisplayArray->Num(); i++)
	{
		if (!MapDisplayArray->IsValidIndex(i))
		{
			continue;
		}

		if ((*MapDisplayArray)[i] == nullptr)
		{
			continue;
		}

		IconDataArray.Add((*MapDisplayArray)[i]->GetIconDisplayData());
	}
	return IconDataArray;
}

TArray<FVector> UPlayerSubsystem::GetMapIconLocations()
{
	if (MapDisplayArray == nullptr)
	{
		return TArray<FVector>();
	}

	TArray<FVector> IconPostionArray;

	for (size_t i = 0; i < MapDisplayArray->Num(); i++)
	{
		if (!MapDisplayArray->IsValidIndex(i))
		{
			continue;
		}

		if ((*MapDisplayArray)[i] == nullptr)
		{
			continue;
		}

		IconPostionArray.Add((*MapDisplayArray)[i]->GetObjectPostion());
	}
	return IconPostionArray;
}

//FVector UPlayerSubsystem::GetMainPlayerLocation()
//{
//	return FVector();
//}

void UPlayerSubsystem::RemoveInterfaceFromArray(TArray<TWeakInterfacePtr<IMinimapIconable>>* Array, TScriptInterface<IMinimapIconable> Player)
{
	if (Array == nullptr)
	{
		return;
	}

	// Why does this not work??
	/*if (!Array->Contains(Player))
	{
		return;
	}*/

	// Don't remove if it's not in the array
	TArray<TWeakInterfacePtr<IMinimapIconable>> Array2 = *Array;
	IMinimapIconable* Interface = Player.GetInterface();
	if (Array2.Contains(Interface))
	{
		return;
	}

	Array->Remove(Player.GetInterface());
}
