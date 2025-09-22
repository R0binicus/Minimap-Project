// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IconDisplayData.generated.h"

USTRUCT(BlueprintType)
struct FIconDisplayData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IconDisplayData")
	UTexture2D* IconImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IconDisplayData")
	float IconScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IconDisplayData")
	FColor IconColour;

	FIconDisplayData() : IconImage(nullptr), IconScale(1.f), IconColour(FColor(FColor::White))
	{

	}

	FIconDisplayData(UTexture2D* InIconImage, float InIconScale, FColor InIconColour) :
		IconImage(InIconImage), IconScale(InIconScale), IconColour(InIconColour)
	{

	}
};
