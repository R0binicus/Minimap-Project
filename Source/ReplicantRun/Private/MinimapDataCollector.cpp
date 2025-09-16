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

	SetMinimapDistanceWidth();
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

void AMinimapDataCollector::SetMinimapDistanceWidth()
{
	if (GetWorld() == nullptr) return;
	MaterialParamInstance = GetWorld()->GetParameterCollectionInstance(MaterialParams);
	if (MaterialParamInstance == nullptr) return;

	// Set material parameter for the Minimap Distance Width
	if (!MaterialParamInstance->SetScalarParameterValue(FName("MinimapDistanceWidth"), MinimapDistanceWidth))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Set minimap MinimapDistanceWidth!")));
	}
}

void AMinimapDataCollector::SetMinimapCentre()
{
	const ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter == nullptr) return;

	const FVector PlayerLocation = PlayerCharacter->GetActorLocation();

	float ScaledAxisCoordinate = PlayerLocation.X / MinimapDistanceWidth;

	// Set material parameter for the Player X Position
	if (!MaterialParamInstance->SetScalarParameterValue(FName("PlayerXPos"), ScaledAxisCoordinate))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Failed to set minimap PlayerXPos!")));
	}

	ScaledAxisCoordinate = PlayerLocation.Y / MinimapDistanceWidth;

	// Set material parameter for the Player Y Position
	if (!MaterialParamInstance->SetScalarParameterValue(FName("PlayerYPos"), ScaledAxisCoordinate))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Failed to set minimap PlayerYPos!")));
	}
}

void AMinimapDataCollector::SetMinimapRotation()
{
	const APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (CameraManager == nullptr) return;

	// Rotation value needs to be a fraction of 360 degrees
	const float RotationValue = CameraManager->GetCameraRotation().Yaw / 360;

	// Set material parameter for camera rotation
	if (!MaterialParamInstance->SetScalarParameterValue(FName("RotationAmount"), RotationValue))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Failed to set minimap RotationAmount!")));
	}
}
