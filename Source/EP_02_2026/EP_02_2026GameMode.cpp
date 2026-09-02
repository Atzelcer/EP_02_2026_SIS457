// Copyright Epic Games, Inc. All Rights Reserved.

#include "EP_02_2026GameMode.h"
#include "EP_02_2026HUD.h"
#include "EP_02_2026Character.h"
#include "EjercicioFilaCubos.h"
#include "UObject/ConstructorHelpers.h"

AEP_02_2026GameMode::AEP_02_2026GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AEP_02_2026HUD::StaticClass();
}

void AEP_02_2026GameMode::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		World->SpawnActor<AEjercicioFilaCubos>(FVector::ZeroVector, FRotator::ZeroRotator);
	}
}
