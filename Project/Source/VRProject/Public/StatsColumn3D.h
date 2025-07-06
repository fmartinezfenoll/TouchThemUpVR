#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StatsColumn3D.generated.h"

class UTextRenderComponent;

UCLASS()
class VRPROJECT_API AStatsColumn3D : public AActor
{
	GENERATED_BODY()
	
public:	
	AStatsColumn3D();

	void UpdateTimeText(const FString& Text);
	void UpdatePickupText(const FString& Text);
	void ShowStatusText(const FString& Text);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	// 4 Caras × 3 Textos
	UPROPERTY(VisibleAnywhere) UTextRenderComponent* TimeText_N;
	UPROPERTY(VisibleAnywhere) UTextRenderComponent* PickupText_N;
	UPROPERTY(VisibleAnywhere) UTextRenderComponent* StatusText_N;

	UPROPERTY(VisibleAnywhere) UTextRenderComponent* TimeText_E;
	UPROPERTY(VisibleAnywhere) UTextRenderComponent* PickupText_E;
	UPROPERTY(VisibleAnywhere) UTextRenderComponent* StatusText_E;

	UPROPERTY(VisibleAnywhere) UTextRenderComponent* TimeText_S;
	UPROPERTY(VisibleAnywhere) UTextRenderComponent* PickupText_S;
	UPROPERTY(VisibleAnywhere) UTextRenderComponent* StatusText_S;

	UPROPERTY(VisibleAnywhere) UTextRenderComponent* TimeText_W;
	UPROPERTY(VisibleAnywhere) UTextRenderComponent* PickupText_W;
	UPROPERTY(VisibleAnywhere) UTextRenderComponent* StatusText_W;
};
