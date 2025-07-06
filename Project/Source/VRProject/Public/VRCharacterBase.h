#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MotionControllerComponent.h"
#include "VRCharacterBase.generated.h"

class AHandSkeletalActor;
class UCineCameraComponent;

UCLASS()
class VRPROJECT_API AVRCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AVRCharacterBase();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void UpdateRightHandPose(float teleportRatio = 0, float grabRatio = 0);

	UFUNCTION(BlueprintCallable)
	void UpdateLeftHandPose(float teleportRatio = 0, float grabRatio = 0);

	UFUNCTION(BlueprintCallable)
	void RightGrabPressed();

	UFUNCTION(BlueprintCallable)
	void LeftGrabPressed();

	UFUNCTION(BlueprintCallable)
	void RightGrabReleased();

	UFUNCTION(BlueprintCallable)
	void LeftGrabReleased();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void CharacterMoveForward(float ratio);

	UFUNCTION(BlueprintCallable)
	void FindFocusDistance();

	void SpawnHandSkeletalMeshActors();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* VROffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCineCameraComponent* VRCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* ControllerBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMotionControllerComponent* RightMotionController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMotionControllerComponent* LeftMotionController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Teleportation")
	UStaticMeshComponent* TeleportLocationIndicator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TSubclassOf<AHandSkeletalActor> RightHandActorTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TSubclassOf<AHandSkeletalActor> LeftHandActorTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion|Movement")
	float MaximumSpeed = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion|Movement")
	float MaximumFocusTrackingDistance = 10000.0f;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Hands")
	AHandSkeletalActor* RightHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Hands")
	AHandSkeletalActor* LeftHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* RightHandPlaceHolder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* LeftHandPlaceHolder;
};
