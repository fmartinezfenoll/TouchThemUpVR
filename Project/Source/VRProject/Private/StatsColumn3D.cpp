#include "StatsColumn3D.h"
#include "Components/TextRenderComponent.h"

#define ADD_TEXT(Name, Loc, Rot, Color, Text) \
	Name = CreateDefaultSubobject<UTextRenderComponent>(TEXT(#Name)); \
	Name->SetupAttachment(Root); \
	Name->SetRelativeLocation(Loc); \
	Name->SetRelativeRotation(Rot); \
	Name->SetHorizontalAlignment(EHTA_Center); \
	Name->SetTextRenderColor(Color); \
	Name->SetText(FText::FromString(Text));

AStatsColumn3D::AStatsColumn3D()
{
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// Cara Norte (frontal)
	ADD_TEXT(TimeText_N, FVector(0, 0, 180), FRotator(0, 0, 0), FColor::Cyan, "Tiempo: 00:00");
	ADD_TEXT(PickupText_N, FVector(0, 0, 140), FRotator(0, 0, 0), FColor::Green, "Pickups: 0 / 0");
	ADD_TEXT(StatusText_N, FVector(0, 0, 100), FRotator(0, 0, 0), FColor::White, "Estado");

	// Cara Este
	ADD_TEXT(TimeText_E, FVector(0, 0, 180), FRotator(0, 90, 0), FColor::Cyan, "Tiempo: 00:00");
	ADD_TEXT(PickupText_E, FVector(0, 0, 140), FRotator(0, 90, 0), FColor::Green, "Pickups: 0 / 0");
	ADD_TEXT(StatusText_E, FVector(0, 0, 100), FRotator(0, 90, 0), FColor::White, "Estado");

	// Cara Sur
	ADD_TEXT(TimeText_S, FVector(0, 0, 180), FRotator(0, 180, 0), FColor::Cyan, "Tiempo: 00:00");
	ADD_TEXT(PickupText_S, FVector(0, 0, 140), FRotator(0, 180, 0), FColor::Green, "Pickups: 0 / 0");
	ADD_TEXT(StatusText_S, FVector(0, 0, 100), FRotator(0, 180, 0), FColor::White, "Estado");

	// Cara Oeste
	ADD_TEXT(TimeText_W, FVector(0, 0, 180), FRotator(0, 270, 0), FColor::Cyan, "Tiempo: 00:00");
	ADD_TEXT(PickupText_W, FVector(0, 0, 140), FRotator(0, 270, 0), FColor::Green, "Pickups: 0 / 0");
	ADD_TEXT(StatusText_W, FVector(0, 0, 100), FRotator(0, 270, 0), FColor::White, "Estado");
}

void AStatsColumn3D::BeginPlay()
{
	Super::BeginPlay();
}

void AStatsColumn3D::UpdateTimeText(const FString& Text)
{
	FText F = FText::FromString("Tiempo: " + Text);
	TimeText_N->SetText(F); TimeText_E->SetText(F);
	TimeText_S->SetText(F); TimeText_W->SetText(F);
}

void AStatsColumn3D::UpdatePickupText(const FString& Text)
{
	FText F = FText::FromString("Pickups: " + Text);
	PickupText_N->SetText(F); PickupText_E->SetText(F);
	PickupText_S->SetText(F); PickupText_W->SetText(F);
}

void AStatsColumn3D::ShowStatusText(const FString& Text)
{
	FText F = FText::FromString(Text);
	StatusText_N->SetText(F); StatusText_E->SetText(F);
	StatusText_S->SetText(F); StatusText_W->SetText(F);
}
