#include "VRCharacterBase.h"
#include "HandSkeletalActor.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "CineCameraComponent.h"

AVRCharacterBase::AVRCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	VROffset = CreateDefaultSubobject<USceneComponent>(TEXT("VROffset"));
	VROffset->SetupAttachment(RootComponent);

	VRCamera = CreateDefaultSubobject<UCineCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(VROffset);

	ControllerBase = CreateDefaultSubobject<USceneComponent>(TEXT("ControllerBase"));
	ControllerBase->SetupAttachment(VROffset);

	RightMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
	RightMotionController->SetupAttachment(ControllerBase);
	RightMotionController->SetTrackingSource(EControllerHand::Right);

	LeftMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionController"));
	LeftMotionController->SetupAttachment(ControllerBase);
	LeftMotionController->SetTrackingSource(EControllerHand::Left);

	TeleportLocationIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TeleportLocationIndicator"));
	TeleportLocationIndicator->SetupAttachment(RootComponent);
	TeleportLocationIndicator->SetVisibility(false);
}

void AVRCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	SpawnHandSkeletalMeshActors();
}

void AVRCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FindFocusDistance();
}

void AVRCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AVRCharacterBase::CharacterMoveForward(float ratio)
{
	AddMovementInput(VRCamera->GetForwardVector(), ratio * MaximumSpeed);
}

void AVRCharacterBase::FindFocusDistance()
{
	FVector Start = VRCamera->GetComponentLocation();
	FVector End = Start + VRCamera->GetForwardVector() * MaximumFocusTrackingDistance;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		// Usar Hit.Distance si se desea enfoque dinámico
	}
}

void AVRCharacterBase::UpdateRightHandPose(float teleportRatio, float grabRatio)
{
	if (!RightHand) return;

	if (teleportRatio < 0.01f && grabRatio < 0.01f)
	{
		RightHand->ResetPoseToDefault();
	}
	else
	{
		RightHand->UpdateTeleportPose(teleportRatio);
		RightHand->UpdateGrabPose(grabRatio);
	}
}

void AVRCharacterBase::UpdateLeftHandPose(float teleportRatio, float grabRatio)
{
	if (!LeftHand) return;

	if (teleportRatio < 0.01f && grabRatio < 0.01f)
	{
		LeftHand->ResetPoseToDefault();
	}
	else
	{
		LeftHand->UpdateTeleportPose(teleportRatio);
		LeftHand->UpdateGrabPose(grabRatio);
	}
}

void AVRCharacterBase::RightGrabPressed()
{
	if (RightHand)
	{
		RightHand->GrabPressed(RightMotionController);
	}
}

void AVRCharacterBase::LeftGrabPressed()
{
	if (LeftHand)
	{
		LeftHand->GrabPressed(LeftMotionController);
	}
}

void AVRCharacterBase::RightGrabReleased()
{
	if (RightHand)
	{
		RightHand->GrabReleased(RightMotionController);
	}
}

void AVRCharacterBase::LeftGrabReleased()
{
	if (LeftHand)
	{
		LeftHand->GrabReleased(LeftMotionController);
	}
}

void AVRCharacterBase::SpawnHandSkeletalMeshActors()
{
	if (RightHandActorTemplate)
	{
		RightHand = GetWorld()->SpawnActor<AHandSkeletalActor>(RightHandActorTemplate);
		if (RightHand)
		{
			RightHand->AttachToComponent(RightMotionController, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
	}
	if (LeftHandActorTemplate)
	{
		LeftHand = GetWorld()->SpawnActor<AHandSkeletalActor>(LeftHandActorTemplate);
		if (LeftHand)
		{
			LeftHand->AttachToComponent(LeftMotionController, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
	}
}
