#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "SimplePickup.generated.h"

UCLASS()
class VRPROJECT_API ASimplePickup : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	ASimplePickup();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	virtual void GrabPressed(class AHandSkeletalActor* Hand) override;
	virtual void GrabReleased(class AHandSkeletalActor* Hand) override;
};
