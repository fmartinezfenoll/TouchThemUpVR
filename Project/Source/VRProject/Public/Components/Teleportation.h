#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Teleportation.generated.h"

class AVRCharacterBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRPROJECT_API UTeleportation : public UActorComponent
{
	GENERATED_BODY()

public:
	UTeleportation();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void BeginTeleport(float ratio);

	UFUNCTION(BlueprintCallable)
	void EndTeleport();

protected:
	virtual void BeginPlay() override;

	void TraceForTeleportLocation();
	void TeleportAction();
	void TeleportCharacter();

protected:
	UPROPERTY(EditAnywhere, Category = "Teleportation")
	float TeleportTraceProjectileVelocity = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Teleportation")
	float TeleportDelay = 0.5f;

	AVRCharacterBase* VRCharacter = nullptr;
	bool bIsTracingForTeleportLocation = false;
	bool bFoundTeleportLocation = false;
	FVector TeleportLocation;
};
