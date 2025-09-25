// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerSubsystem.h"
#include "UObject/WeakInterfacePtr.h"

void UPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	
}

void UPlayerSubsystem::Deinitialize()
{

}

void UPlayerSubsystem::AddPlayer(const TScriptInterface<IMinimapIconable> PlayerInterface)
{
	if (PlayerRefArray == nullptr)
	{
		return;
	}

	UObject* PlayerObj = PlayerInterface.GetObject();

	if (!PlayerObj)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("PlayerObj is null")));
		return;
	}

	if (!PlayerObj->Implements<UMinimapIconable>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("PlayerObj is not implemented")));
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("oLAYERoBJ VALID")));

	//PlayerInterface.GetObject()

	//FVector Vector = IMinimapIconable::Execute_GetObjectPostion();

	//FVector Vector = IMinimapIconable::Execute_GetObjectPostion(PlayerInterface.GetObject());

	// Why doesn't think work???
	//if (MapIconActor->GetClass()->ImplementsInterface(UMinimapIconable::StaticClass()))//Implements<IMinimapIconable>())
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("does not implement iconable")));
	//	//return;
	//}

	//UMinimapIconable* MinimapIconable = Cast<UMinimapIconable>(MapIconActor);

	//if (PlayerInterface->Implements<UMinimapIconable>())//Implements<IMinimapIconable>())
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("does not implement iconable")));
	//	return;
	//}


	//TScriptInterface<UMinimapIconable> IconableInterface = Cast<UMinimapIconable>(MapIconActor);

	//TScriptInterface<UMinimapIconable> Player = MapIconActor;

	//if (IconableInterface == nullptr)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("IconableInterface is nullptr")));
	//	return;
	//}

	/*if (TargetActor->GetClass()->ImplementsInterface(UInterfaceCoversArea::StaticClass()))
	{
		CurrentRange -= IInterfaceCoversArea::Execute_GetAreaCoverageRadius(TargetActor);
	}*/

	//IMinimapIconable* Interface = Player.GetInterface();
	//TScriptInterface<IMinimapIconable>::UObjectType* Interface2 = Player.GetObject();

	//if (Interface2 == nullptr)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Interface is nullptr")));
	//	return;
	//}

	//IMinimapIconable* TheInterface = Cast<IMinimapIconable>(Interface2);
	//if (TheInterface)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Interface is good!")));
	//	PlayerRefArray->Add(TheInterface);
	//	return;
	//}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Interface is NOT CASTING!")));

	PlayerRefArray->Add(PlayerObj);
	//PlayerRefArray->Add(MinimapIconable);
}

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

//FVector UPlayerSubsystem::GetMainPlayerLocation()
//{
//	return FVector();
//}

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
