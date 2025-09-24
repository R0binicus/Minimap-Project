// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerSubsystem.h"
#include "UObject/WeakInterfacePtr.h"

void UPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	
}

void UPlayerSubsystem::Deinitialize()
{

}

void UPlayerSubsystem::AddPlayer(UObject* PlayerInterface)
{
	if (PlayerRefArray == nullptr)
	{
		return;
	}

	if (!PlayerInterface)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("PlayerInterface is null")));
		return;
	}

	if (!PlayerInterface->Implements<UMinimapIconable>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("PlayerInterface is not implemented")));
		return;
	}

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

	PlayerRefArray->Add(PlayerInterface);
	//PlayerRefArray->Add(MinimapIconable);
}

void UPlayerSubsystem::EnableMapDisplay(UObject* PlayerInterface)
{
	if (MapDisplayArray == nullptr)
	{
		return;
	}
	if (!PlayerInterface)
	{
		return;
	}
	MapDisplayArray->Add(PlayerInterface);
}

void UPlayerSubsystem::RemovePlayer(UObject* PlayerInterface)
{
	RemoveInterfaceFromArray(PlayerRefArray, PlayerInterface);
	RemoveInterfaceFromArray(MapDisplayArray, PlayerInterface);
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

		//IconPositionArray.Add(IMinimapIconable::Execute_GetObjectPostion((*MapDisplayArray)[i].Get()));
	}
	return IconDataArray;
}

TArray<FVector> UPlayerSubsystem::GetMapIconLocations()
{
	TArray<FVector> IconPositionArray;

	if (MapDisplayArray == nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("MapDisplayArray == nullptr")));
		return IconPositionArray;
	}

	for (size_t i = 0; i < MapDisplayArray->Num(); i++)
	{
		if (!MapDisplayArray->IsValidIndex(i))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("iNVALID INDEX")));
			continue;
		}

		if ((*MapDisplayArray)[i] == nullptr)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("(*MapDisplayArray)[i] == nullptr")));
			continue;
		}

		// IconPostionArray.Add((*MapDisplayArray)[i]->GetObjectPostion());
		//IconPositionArray.Add((*MapDisplayArray)[i]->GetObjectPostion());
		//TArray<TWeakObjectPtr<UObject>> Array2 = *MapDisplayArray;
		//TWeakObjectPtr<UObject> obj = Array2[i];

		//IconPositionArray.Add(IMinimapIconable::Execute_GetObjectPostion(obj.Get()));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Adding to array")));
		IconPositionArray.Add(IMinimapIconable::Execute_GetObjectPostion((*MapDisplayArray)[i].Get()));
	}
	return IconPositionArray;
}

//FVector UPlayerSubsystem::GetMainPlayerLocation()
//{
//	return FVector();
//}

void UPlayerSubsystem::RemoveInterfaceFromArray(TArray<TWeakObjectPtr<UObject>>* Array, UObject* PlayerInterface)
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

	if (!PlayerInterface)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("PlayerInterface is null")));
		return;
	}

	if (!PlayerInterface->Implements<UMinimapIconable>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("PlayerInterface is not implemented")));
		return;
	}

	// Don't remove if it's not in the array
	TArray<TWeakObjectPtr<UObject>> Array2 = *Array;
	if (!Array2.Contains(PlayerInterface))
	{
		return;
	}
	Array->Remove(PlayerInterface);
}
