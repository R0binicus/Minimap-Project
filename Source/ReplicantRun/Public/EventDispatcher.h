#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MinimapIconable.h"
#include "EventDispatcher.generated.h"

// Delegates that can bind to multiple UFUNCTIONs simultaniously
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEvent_ExampleNoParams);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEvent_ExampleOneParams, bool, MyBool);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEvent_ExampleTwoParams, bool, MyBool, float, MyFloat);

UCLASS()
class UEventDispatcher : public UBlueprintFunctionLibrary
{
	#pragma region Event Manager
	// Core event manager code
	GENERATED_BODY()

private:
	// For delegates to be blueprint assignable, they can not be static
	// So a singleton is used
	static UEventDispatcher* EventManagerSingleton;

	// Set singleton in constructor and destructor
	UEventDispatcher();
	~UEventDispatcher();

public: // These are the event multi dispatchers
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Create Event Dispatcher")
	FEvent_ExampleNoParams Event_ExampleNoParams;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Create Event Dispatcher")
	FEvent_ExampleOneParams Event_ExampleOneParams;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Create Event Dispatcher")
	FEvent_ExampleTwoParams Event_ExampleTwoParams;

public: 
	UFUNCTION(BlueprintPure, Category = "Create Event Dispatcher")
	static UEventDispatcher* GetEventManagerSingleton();
#pragma endregion Event Manager

#pragma region Example
// These are examples of how another script would use the event dispatcher
// Essentially imagine that they are in a script other than the EventManager
private: // Example functions that will be called when the event is triggered
	UFUNCTION()
		void ExampleNoParamsHandler();
	UFUNCTION()
		void ExampleOneParamsHandler(bool MyBool);
	UFUNCTION()
		void ExampleTwoParamsHandler(bool MyBool, float MyFloat);

public:
	// Bind all example event dispatchers
	UFUNCTION(BlueprintCallable, Category = "Create Event Dispatcher")
		static void ExampleBindDispatchersCpp();
	
	// Unbind all example event dispatchers
	UFUNCTION(BlueprintCallable, Category = "Create Event Dispatcher")
		static void ExampleUnbindDispatchersCpp();

	// Call all example event dispatchers
	UFUNCTION(BlueprintCallable, Category = "Create Event Dispatcher")
		static void ExampleCallDispatchersCpp();
#pragma endregion Example
};
