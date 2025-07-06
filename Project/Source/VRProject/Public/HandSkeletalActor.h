#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandSkeletalActor.generated.h"

class UVRHandAnimationInstance;
class UMotionControllerComponent;
class UPrimitiveComponent;
class USphereComponent;

UCLASS()
class VRPROJECT_API AHandSkeletalActor : public AActor
{
	GENERATED_BODY()

public:
	AHandSkeletalActor();
	virtual void Tick(float DeltaTime) override;

	// === Control de poses ===
	UFUNCTION(BlueprintCallable)
	void UpdateTeleportPose(float Alpha);

	UFUNCTION(BlueprintCallable)
	void UpdateGrabPose(float Alpha);

	UFUNCTION(BlueprintCallable)
	void ResetPoseToDefault();

	// === Interacción ===
	UFUNCTION(BlueprintCallable)
	void GrabPressed(UMotionControllerComponent* MotionController);

	UFUNCTION(BlueprintCallable)
	void GrabReleased(UMotionControllerComponent* MotionController);

protected:
	virtual void BeginPlay() override;

	// === Detección de objetos cercanos ===
	UFUNCTION()
	void OnGrabSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnGrabSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	// === Componentes ===
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Base;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* HandMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* GrabSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
	UVRHandAnimationInstance* HandAnimationInstance;

protected:
	// === Referencias de interacción ===
	UPROPERTY()
	AActor* ReadyToGrabActor = nullptr;

	UPROPERTY()
	AActor* AttachedActor = nullptr;

	UPROPERTY()
	UPrimitiveComponent* ReadyToGrabComponent = nullptr;
};
