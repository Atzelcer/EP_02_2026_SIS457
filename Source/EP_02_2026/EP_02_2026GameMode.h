// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EP_02_2026GameMode.generated.h"

UCLASS(minimalapi)
class AEP_02_2026GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEP_02_2026GameMode();

protected:
	virtual void BeginPlay() override;
};



