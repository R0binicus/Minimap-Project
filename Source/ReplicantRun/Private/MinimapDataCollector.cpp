#include "MinimapDataCollector.h"
#include "Kismet/GameplayStatics.h" 
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "GameFramework/Character.h"

AMinimapDataCollector::AMinimapDataCollector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
	
	SetMinimapRotation();
	SetPlayerBasedValues();
}

void AMinimapDataCollector::SetMinimapRotation()
{
	const APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (CameraManager == nullptr) return;

	// Rotation value needs to be a fraction of 360 degrees
	MinimapRotation = CameraManager->GetCameraRotation().Yaw / DegreesInCircle;

	MaterialParamInstance->SetScalarParameterValue(FName("RotationAmount"), MinimapRotation);
}

void AMinimapDataCollector::SetPlayerBasedValues()
{
	const ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter == nullptr) return;

	SetMinimapCentre(PlayerCharacter);
	SetPlayerIndicatorRotation(PlayerCharacter);
}

void AMinimapDataCollector::SetMinimapCentre(const ACharacter* PlayerCharacter)
{
	const FVector PlayerLocation = PlayerCharacter->GetActorLocation();

	// Set scaled X and Y axis coordinates
	float ScaledXAxisCoordinate = PlayerLocation.X / MinimapDistanceWidth + XPosOffset;
	ScaledXAxisCoordinate = 1 - ScaledXAxisCoordinate;

	const float ScaledYAxisCoordinate = PlayerLocation.Y / MinimapDistanceWidth + YPosOffset;

	// Set material parameter for the player positions
	MaterialParamInstance->SetScalarParameterValue(FName("PlayerXPos"), ScaledXAxisCoordinate);
	MaterialParamInstance->SetScalarParameterValue(FName("PlayerYPos"), ScaledYAxisCoordinate);
}

void AMinimapDataCollector::SetPlayerIndicatorRotation(const ACharacter* PlayerCharacter)
{
	// Calculate rotation fraction needed for the minimap's player indicator
	// Based on the minimap's rotation and the player character rotation
	float PlayerRotation = PlayerCharacter->GetActorRotation().Yaw / -DegreesInCircle;
	PlayerRotation = MinimapRotation + PlayerRotation;

	MaterialParamInstance->SetScalarParameterValue(FName("PlayerRotation"), PlayerRotation);
}
