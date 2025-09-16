// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimapDataCollector.h"
#include "Kismet/GameplayStatics.h" 
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "GameFramework/Character.h"

// Sets default values
AMinimapDataCollector::AMinimapDataCollector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMinimapDataCollector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMinimapDataCollector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Currently in tick because I'm not sure the best place top put it
	// Would a function on a 0.1 second timer be better?
	// Is there an event better place?
	SetMinimapMaterialParams();

}

void AMinimapDataCollector::SetMinimapMaterialParams()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter == nullptr) return;
	if (MaterialParams == nullptr) return;

	UMaterialParameterCollectionInstance* Instance = GetWorld()->GetParameterCollectionInstance(MaterialParams);

	if (!Instance->SetVectorParameterValue(FName("PlayerPosition"), PlayerCharacter->GetActorLocation()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Set minimap player position failed!")));
	}

	FRotator PlayerRotation = PlayerCharacter->GetActorRotation();

	if (!Instance->SetScalarParameterValue(FName("RotationAmount"), PlayerRotation.Yaw))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Set minimap player rotation failed!")));
	}
}
