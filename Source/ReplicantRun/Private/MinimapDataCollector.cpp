#include "MinimapDataCollector.h"
#include "Kismet/GameplayStatics.h" 
#include "Materials/MaterialParameterCollectionInstance.h"
#include "GameFramework/Character.h"

AMinimapDataCollector::AMinimapDataCollector()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMinimapDataCollector::BeginPlay()
{
	Super::BeginPlay();

	SetMinimapInitialValues();
}

void AMinimapDataCollector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMinimapParamValues();
}

void AMinimapDataCollector::SetMinimapInitialValues()
{
	WorldPtr = GetWorld();
	
	if (WorldPtr == nullptr)
	{
		return;
	}
	
	if (MaterialParams == nullptr)
	{
		return;
	}
	
	MaterialParamInstance = WorldPtr->GetParameterCollectionInstance(MaterialParams);
	
	if (MaterialParamInstance == nullptr) 
	{
		return;
	}

	MaterialParamInstance->SetScalarParameterValue(FName("MinimapDistanceWidth"), MinimapDistanceWidth);
	MaterialParamInstance->SetScalarParameterValue(FName("MinimapScaleMultiplier"), ScaleMultiplier);
	MaterialParamInstance->SetScalarParameterValue(FName("MinimapScaleOffset"), ScaleOffset);
}

void AMinimapDataCollector::UpdateMinimapParamValues()
{
	SetMinimapRotation();
	SetPlayerBasedValues();
}

void AMinimapDataCollector::SetMinimapRotation()
{
	if (WorldPtr == nullptr)
	{
		return;
	}

	if (MaterialParamInstance == nullptr)
	{
		return;
	}
	
	const TObjectPtr<APlayerCameraManager> CameraManager = UGameplayStatics::GetPlayerCameraManager(WorldPtr, 0);
	
	if (CameraManager == nullptr)
	{
		return;
	}

	// Rotation value needs to be a fraction of 360 degrees
	MinimapRotation = CameraManager->GetCameraRotation().Yaw / DegreesInCircle;

	MaterialParamInstance->SetScalarParameterValue(FName("RotationAmount"), MinimapRotation);
}

void AMinimapDataCollector::SetPlayerBasedValues()
{
	if (WorldPtr == nullptr)
	{
		return;
	}
	
	const TObjectPtr<ACharacter> PlayerCharacter = UGameplayStatics::GetPlayerCharacter(WorldPtr, 0);
	
	if (PlayerCharacter == nullptr)
	{
		return;
	}

	SetMinimapCentre(PlayerCharacter);
	SetPlayerIndicatorRotation(PlayerCharacter);
}

void AMinimapDataCollector::SetMinimapCentre(const TObjectPtr<ACharacter>& PlayerCharacter)
{
	const FVector PlayerLocation = PlayerCharacter->GetActorLocation();

	// Set scaled X and Y axis coordinates
	float ScaledXAxisCoordinate = PlayerLocation.X / MinimapDistanceWidth + XPosOffset;
	ScaledXAxisCoordinate = 1 - ScaledXAxisCoordinate;

	const float ScaledYAxisCoordinate = PlayerLocation.Y / MinimapDistanceWidth;

	// Set material parameter for the player positions
	MaterialParamInstance->SetScalarParameterValue(FName("PlayerXPos"), ScaledXAxisCoordinate);
	MaterialParamInstance->SetScalarParameterValue(FName("PlayerYPos"), ScaledYAxisCoordinate);
}

void AMinimapDataCollector::SetPlayerIndicatorRotation(const TObjectPtr<ACharacter>& PlayerCharacter)
{
	// Calculate rotation fraction needed for the minimap's player indicator
	// Based on the minimap's rotation and the player character rotation
	float PlayerRotation = PlayerCharacter->GetActorRotation().Yaw / -DegreesInCircle;
	PlayerRotation = MinimapRotation + PlayerRotation;

	MaterialParamInstance->SetScalarParameterValue(FName("PlayerRotation"), PlayerRotation);
}
