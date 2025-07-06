#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_TouchThemUP.generated.h"

class ASimplePickup;
class AStatsColumn3D;

UCLASS()
class VRPROJECT_API AGM_TouchThemUP : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGM_TouchThemUP();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void NotifyPickupCollected(ASimplePickup* Pickup);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	float GameDuration = 120.0f;

private:
	TSet<ASimplePickup*> AllPickups;
	TSet<ASimplePickup*> CollectedPickups;

	float TimeRemaining;
	bool bGameEnded = false;

	UPROPERTY()
	AStatsColumn3D* StatsColumn;

	void EndGame(bool bVictory);
	void RestartLevelAfterDelay();
	void UpdateHUD();
};
