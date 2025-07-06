#include "HandSkeletalActor.h"
#include "VRHandAnimationInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Interfaces/Interactable.h"
#include "MotionControllerComponent.h"

// Constructor
AHandSkeletalActor::AHandSkeletalActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Base = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Base);

	HandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandMesh"));
	HandMesh->SetupAttachment(Base);

	GrabSphere = CreateDefaultSubobject<USphereComponent>(TEXT("GrabSphere"));
	GrabSphere->SetupAttachment(HandMesh);
	GrabSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GrabSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	GrabSphere->OnComponentBeginOverlap.AddDynamic(this, &AHandSkeletalActor::OnGrabSphereBeginOverlap);
	GrabSphere->OnComponentEndOverlap.AddDynamic(this, &AHandSkeletalActor::OnGrabSphereEndOverlap);
}

// BeginPlay
void AHandSkeletalActor::BeginPlay()
{
	Super::BeginPlay();

	HandAnimationInstance = Cast<UVRHandAnimationInstance>(HandMesh->GetAnimInstance());
	if (HandAnimationInstance)
	{
		HandAnimationInstance->IsInDefaultPose = 0;
	}
}

// Tick
void AHandSkeletalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Reset a la pose neutra
void AHandSkeletalActor::ResetPoseToDefault()
{
	if (HandAnimationInstance)
	{
		HandAnimationInstance->IsInDefaultPose = 1;
	}
}

// Blend de teletransporte
void AHandSkeletalActor::UpdateTeleportPose(float Alpha)
{
	if (HandAnimationInstance)
	{
		HandAnimationInstance->PoseAlphaTeleport = Alpha;
		HandAnimationInstance->IsInDefaultPose = 0;
	}
}

// Blend de agarre
void AHandSkeletalActor::UpdateGrabPose(float Alpha)
{
	if (HandAnimationInstance)
	{
		HandAnimationInstance->PoseAlphaGrab = Alpha;
		HandAnimationInstance->IsInDefaultPose = 0;
	}
}

// Agarre
void AHandSkeletalActor::GrabPressed(UMotionControllerComponent* MotionController)
{
	if (const auto Interactable = Cast<IInteractable>(ReadyToGrabActor))
	{
		Interactable->GrabPressed(this);
		AttachedActor = ReadyToGrabActor;
	}
}

// Soltar
void AHandSkeletalActor::GrabReleased(UMotionControllerComponent* MotionController)
{
	if (const auto Interactable = Cast<IInteractable>(AttachedActor))
	{
		Interactable->GrabReleased(this);
		AttachedActor = nullptr;
		ReadyToGrabActor = nullptr;
		ReadyToGrabComponent = nullptr;
	}
}

// Inicio de colisión con objeto interactuable
void AHandSkeletalActor::OnGrabSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		ReadyToGrabActor = OtherActor;
		ReadyToGrabComponent = OtherComp;
	}
}

// Fin de colisión con objeto interactuable
void AHandSkeletalActor::OnGrabSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && ReadyToGrabActor == OtherActor)
	{
		ReadyToGrabActor = nullptr;
		ReadyToGrabComponent = nullptr;
	}
}
