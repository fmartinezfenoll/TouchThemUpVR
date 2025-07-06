#include "GM_TouchThemUP.h"
#include "InteractableObjects/SimplePickup.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "StatsColumn3D.h"
#include "EngineUtils.h"

AGM_TouchThemUP::AGM_TouchThemUP()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGM_TouchThemUP::BeginPlay()
{
	Super::BeginPlay();

	TimeRemaining = GameDuration;

	// Buscar todos los pickups
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASimplePickup::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors)
	{
		if (ASimplePickup* Pickup = Cast<ASimplePickup>(Actor))
		{
			AllPickups.Add(Pickup);
		}
	}

	// Buscar la columna de stats en el mapa
	for (TActorIterator<AStatsColumn3D> It(GetWorld()); It; ++It)
	{
		StatsColumn = *It;
		break;
	}

	UpdateHUD();
}

void AGM_TouchThemUP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bGameEnded) return;

	TimeRemaining -= DeltaTime;
	if (TimeRemaining <= 0.f)
	{
		EndGame(false); // derrota
		return;
	}

	UpdateHUD();
}

void AGM_TouchThemUP::NotifyPickupCollected(ASimplePickup* Pickup)
{
	if (!Pickup || bGameEnded || CollectedPickups.Contains(Pickup)) return;

	CollectedPickups.Add(Pickup);
	UpdateHUD();

	if (CollectedPickups.Num() >= AllPickups.Num())
	{
		EndGame(true); // victoria
	}
}

void AGM_TouchThemUP::UpdateHUD()
{
	if (StatsColumn)
	{
		int32 Min = FMath::FloorToInt(TimeRemaining / 60);
		int32 Sec = FMath::RoundToInt(FMath::Fmod(TimeRemaining, 60));
		StatsColumn->UpdateTimeText(FString::Printf(TEXT("%02d:%02d"), Min, Sec));
		StatsColumn->UpdatePickupText(FString::Printf(TEXT("%d / %d"), CollectedPickups.Num(), AllPickups.Num()));
	}
}

void AGM_TouchThemUP::EndGame(bool bVictory)
{
	bGameEnded = true;

	if (StatsColumn)
	{
		StatsColumn->ShowStatusText(bVictory ? TEXT("¡VICTORIA!") : TEXT("DERROTA"));
	}

	RestartLevelAfterDelay();
}

void AGM_TouchThemUP::RestartLevelAfterDelay()
{
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, []()
		{
			UGameplayStatics::OpenLevel(GWorld, FName(*UGameplayStatics::GetCurrentLevelName(GWorld)));
		}, 10.0f, false);
}
