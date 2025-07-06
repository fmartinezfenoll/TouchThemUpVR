// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class AHandSkeletalActor;

// Esta clase no necesita ser modificada
UINTERFACE()
class VRPROJECT_API UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interfaz para objetos interactuables (como pickups).
 */
class VRPROJECT_API IInteractable
{
	GENERATED_BODY()

public:
	virtual void GrabPressed(AHandSkeletalActor* Hand) {}
	virtual void GrabReleased(AHandSkeletalActor* Hand) {}
};
