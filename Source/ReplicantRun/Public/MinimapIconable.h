#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IconDisplayData.h"
#include "MinimapIconable.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UMinimapIconable : public UInterface
{
	GENERATED_BODY()
};

class REPLICANTRUN_API IMinimapIconable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = MyInterface)
	FIconDisplayData GetIconDisplayData();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = MyInterface)
	FVector GetObjectPosition();
};
