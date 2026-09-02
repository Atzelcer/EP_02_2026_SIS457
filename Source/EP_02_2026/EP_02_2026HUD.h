// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EP_02_2026HUD.generated.h"

UCLASS()
class AEP_02_2026HUD : public AHUD
{
	GENERATED_BODY()

public:
	AEP_02_2026HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

