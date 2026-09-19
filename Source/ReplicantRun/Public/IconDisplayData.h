#pragma once

#include "CoreMinimal.h"
#include "IconDisplayData.generated.h"

USTRUCT(BlueprintType)
struct FIconDisplayData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IconDisplayData")
	TObjectPtr<UTexture2D> IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IconDisplayData")
	FVector IconPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IconDisplayData")
	float IconScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IconDisplayData")
	float IconHueShift;

	FIconDisplayData() : IconTexture(nullptr), IconPosition(FVector::ZeroVector), IconScale(1.f), IconHueShift(1.f)
	{
	}

	FIconDisplayData(UTexture2D* InIconTexture, const FVector& InIconPosition, const float InIconScale, const float InIconHue) :
		IconTexture(InIconTexture), IconPosition(InIconPosition), IconScale(InIconScale), IconHueShift(InIconHue)
	{
	}
};
