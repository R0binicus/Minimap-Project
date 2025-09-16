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

	MaterialParamInstance = GetWorld()->GetParameterCollectionInstance(MaterialParams);
	if (MaterialParamInstance == nullptr) return;

	// Set material parameter for the Minimap Distance Width
	if (!MaterialParamInstance->SetScalarParameterValue(FName("MinimapDistanceWidth"), MinimapDistanceWidth))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Set minimap MinimapDistanceWidth!")));
	}
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
	if (MaterialParams == nullptr) return;
	if (MaterialParamInstance == nullptr) return;
	const ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter == nullptr) return;

	// Set material parameter for the Player Position
	if (!MaterialParamInstance->SetVectorParameterValue(FName("PlayerPosition"), PlayerCharacter->GetActorLocation()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Set minimap PlayerPosition!")));
	}

	// Set material parameter for Rotation Amount
	const FRotator PlayerRotation = PlayerCharacter->GetActorRotation();
	if (!MaterialParamInstance->SetScalarParameterValue(FName("RotationAmount"), PlayerRotation.Yaw))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Set minimap RotationAmount!")));
	}
}
