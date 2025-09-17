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

	SetMinimapInitialValues();
}

// Called every frame
void AMinimapDataCollector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Currently in tick because I'm not sure the best place top put it
	// Would a function on a 0.1 second timer be better?
	// Is there an event better place?
	UpdateMinimapParamValues();
}

void AMinimapDataCollector::SetMinimapInitialValues()
{
	if (GetWorld() == nullptr) return;
	if (MaterialParams == nullptr) return;
	MaterialParamInstance = GetWorld()->GetParameterCollectionInstance(MaterialParams);
	if (MaterialParamInstance == nullptr) return;

	// Set material parameter for the Minimap Distance Width
	MaterialParamInstance->SetScalarParameterValue(FName("MinimapDistanceWidth"), MinimapDistanceWidth);

	// Set material parameter for minimap multiplier and scale
	MaterialParamInstance->SetScalarParameterValue(FName("MinimapScaleMultiplier"), ScaleMultiplier);
	MaterialParamInstance->SetScalarParameterValue(FName("MinimapScaleOffset"), ScaleOffset);
}

void AMinimapDataCollector::UpdateMinimapParamValues()
{
	if (MaterialParamInstance == nullptr) return;
	if (GetWorld() == nullptr) return;
	
	SetMinimapCentre();
	SetMinimapRotation();

	// Set material parameter for player character rotation amount
	// May be used later for player character icon
	/*const FRotator PlayerRotation = PlayerCharacter->GetActorRotation();
	if (!MaterialParamInstance->SetScalarParameterValue(FName("RotationAmount"), PlayerRotation.Yaw))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Set minimap RotationAmount!")));
	}*/
}

void AMinimapDataCollector::SetMinimapCentre()
{
	const ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter == nullptr) return;

	const FVector PlayerLocation = PlayerCharacter->GetActorLocation();

	// Set scaled X and Y axis coordinates
	float ScaledXAxisCoordinate = PlayerLocation.X / MinimapDistanceWidth + XPosOffset;
	ScaledXAxisCoordinate = 1 - ScaledXAxisCoordinate;

	const float ScaledYAxisCoordinate = PlayerLocation.Y / MinimapDistanceWidth + YPosOffset;

	// Set material parameter for the player positions
	MaterialParamInstance->SetScalarParameterValue(FName("PlayerXPos"), ScaledXAxisCoordinate);
	MaterialParamInstance->SetScalarParameterValue(FName("PlayerYPos"), ScaledYAxisCoordinate);
}

void AMinimapDataCollector::SetMinimapRotation()
{
	const APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (CameraManager == nullptr) return;

	// Rotation value needs to be a fraction of 360 degrees
	const float RotationValue = CameraManager->GetCameraRotation().Yaw / 360;

	MaterialParamInstance->SetScalarParameterValue(FName("RotationAmount"), RotationValue);
}
