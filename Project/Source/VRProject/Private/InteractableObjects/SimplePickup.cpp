#include "InteractableObjects/SimplePickup.h"
#include "HandSkeletalActor.h" 
#include "GM_TouchThemUP.h"

ASimplePickup::ASimplePickup()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComponent->SetCollisionObjectType(ECC_PhysicsBody);
}

void ASimplePickup::BeginPlay()
{
	Super::BeginPlay();
}

void ASimplePickup::GrabReleased(AHandSkeletalActor* Hand)
{
	if (!Hand) return;

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	StaticMeshComponent->SetSimulatePhysics(true);
}

void ASimplePickup::GrabPressed(AHandSkeletalActor* Hand)
{
	if (!Hand) return;

	AttachToActor(Hand, FAttachmentTransformRules::KeepWorldTransform);
	StaticMeshComponent->SetSimulatePhysics(false);

	// Notificar al GameMode
	if (AGM_TouchThemUP* GM = Cast<AGM_TouchThemUP>(GetWorld()->GetAuthGameMode()))
	{
		GM->NotifyPickupCollected(this);
	}
}

