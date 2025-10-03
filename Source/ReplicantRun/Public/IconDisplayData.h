#pragma once

#include "CoreMinimal.h"
#include "IconDisplayData.generated.h"

USTRUCT(BlueprintType)
struct FIconDisplayData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IconDisplayData")
	TObjectPtr<UMaterialInstanceDynamic> IconMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IconDisplayData")
	FVector IconPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IconDisplayData")
	float IconScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IconDisplayData")
	FColor IconColour;

	FIconDisplayData() : IconMaterial(nullptr), IconPosition(FVector::ZeroVector), IconScale(1.f), IconColour(FColor(FColor::White))
	{

	}

	FIconDisplayData(UMaterialInstanceDynamic* InIconMaterial, FVector InIconPosition, float InIconScale, FColor InIconColour) :
		IconMaterial(InIconMaterial), IconPosition(InIconPosition), IconScale(InIconScale), IconColour(InIconColour)
	{

	}
};
