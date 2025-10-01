#pragma once

#include "CoreMinimal.h"
#include "IconDisplayData.generated.h"

USTRUCT(BlueprintType)
struct FIconDisplayData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IconDisplayData")
	TObjectPtr<UMaterialInstanceDynamic > IconMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IconDisplayData")
	float IconScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IconDisplayData")
	FColor IconColour;

	FIconDisplayData() : IconMaterial(nullptr), IconScale(1.f), IconColour(FColor(FColor::White))
	{

	}

	FIconDisplayData(UMaterialInstanceDynamic* InIconMaterial, float InIconScale, FColor InIconColour) :
		IconMaterial(InIconMaterial), IconScale(InIconScale), IconColour(InIconColour)
	{

	}
};
