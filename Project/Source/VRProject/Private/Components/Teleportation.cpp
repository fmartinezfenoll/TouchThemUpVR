#include "Components/Teleportation.h"
#include "VRCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "TimerManager.h"

UTeleportation::UTeleportation()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTeleportation::BeginPlay()
{
	Super::BeginPlay();
	VRCharacter = Cast<AVRCharacterBase>(GetOwner());
}

void UTeleportation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsTracingForTeleportLocation)
	{
		TraceForTeleportLocation();
	}
}

void UTeleportation::BeginTeleport(float ratio)
{
	bIsTracingForTeleportLocation = true;
	if (VRCharacter) VRCharacter->UpdateRightHandPose(ratio);
}

void UTeleportation::EndTeleport()
{
	bIsTracingForTeleportLocation = false;
	if (VRCharacter) VRCharacter->UpdateRightHandPose(0.0f);

	if (bFoundTeleportLocation)
	{
		TeleportAction();
	}
}

void UTeleportation::TraceForTeleportLocation()
{
	if (!VRCharacter) return;

	FPredictProjectilePathParams PredictParams;
	PredictParams.bTraceComplex = false;
	PredictParams.bTraceWithCollision = true;
	PredictParams.bTraceWithChannel = true;
	PredictParams.TraceChannel = ECC_Visibility;

	const FVector StartLocation = VRCharacter->RightMotionController->GetComponentLocation();
	const FVector ForwardVector = VRCharacter->RightMotionController->GetForwardVector();

	PredictParams.StartLocation = StartLocation;
	PredictParams.LaunchVelocity = ForwardVector * TeleportTraceProjectileVelocity;

	FPredictProjectilePathResult PredictResult;
	if (UGameplayStatics::PredictProjectilePath(this, PredictParams, PredictResult))
	{
		TeleportLocation = PredictResult.HitResult.Location;
		bFoundTeleportLocation = true;
	}
	else
	{
		bFoundTeleportLocation = false;
	}
}

void UTeleportation::TeleportAction()
{
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->
		StartCameraFade(0.f, 1.f, TeleportDelay, FLinearColor::Black);

	FTimerHandle FadeTimer;
	GetWorld()->GetTimerManager().SetTimer(FadeTimer, this, &UTeleportation::TeleportCharacter, TeleportDelay);
}

void UTeleportation::TeleportCharacter()
{
	if (VRCharacter)
	{
		VRCharacter->SetActorLocation(TeleportLocation);
	}

	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->
		StartCameraFade(1.f, 0.f, TeleportDelay, FLinearColor::Black);
}
