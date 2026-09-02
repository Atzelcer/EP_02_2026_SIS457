#include "CuboEstatico.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ACuboEstatico::ACuboEstatico()
{
	PrimaryActorTick.bCanEverTick = false;
	bYaExploto = false;
	bEsPar = false;
	TexturaCubo = nullptr;
	MaterialCubo = nullptr;
	FXExplosion = nullptr;
	CueExplosion = nullptr;

	MeshCubo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCubo"));
	RootComponent = MeshCubo;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CuboAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CuboAsset.Succeeded())
	{
		MeshCubo->SetStaticMesh(CuboAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> TexturaAsset(TEXT("/Game/StarterContent/Textures/T_Brick_Clay_New_D.T_Brick_Clay_New_D"));
	if (TexturaAsset.Succeeded())
	{
		TexturaCubo = TexturaAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	if (MaterialAsset.Succeeded())
	{
		MaterialCubo = MaterialAsset.Object;
		MeshCubo->SetMaterial(0, MaterialCubo);
	}

	MeshCubo->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshCubo->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	SonidoExplosion = CreateDefaultSubobject<UAudioComponent>(TEXT("SonidoExplosion"));
	SonidoExplosion->SetupAttachment(RootComponent);
	SonidoExplosion->bAutoActivate = false;

	static ConstructorHelpers::FObjectFinder<USoundBase> SonidoAsset(TEXT("/Game/StarterContent/Audio/Explosion_Cue.Explosion_Cue"));
	if (SonidoAsset.Succeeded())
	{
		CueExplosion = SonidoAsset.Object;
		SonidoExplosion->SetSound(CueExplosion);
	}

	ParticulaExplosion = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticulaExplosion"));
	ParticulaExplosion->SetupAttachment(RootComponent);
	ParticulaExplosion->bAutoActivate = false;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticulaAsset(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (ParticulaAsset.Succeeded())
	{
		FXExplosion = ParticulaAsset.Object;
		ParticulaExplosion->SetTemplate(FXExplosion);
	}
}

void ACuboEstatico::AplicarColor(const FLinearColor& Color)
{
	if (MeshCubo == nullptr)
	{
		return;
	}

	UMaterialInterface* Base = MeshCubo->GetMaterial(0);
	if (Base == nullptr)
	{
		Base = MaterialCubo;
	}
	if (Base == nullptr)
	{
		return;
	}

	UMaterialInstanceDynamic* MID = MeshCubo->CreateDynamicMaterialInstance(0, Base);
	if (MID != nullptr)
	{
		MID->SetVectorParameterValue(TEXT("Color"), Color);
	}
}

void ACuboEstatico::Explotar()
{
	if (bYaExploto)
	{
		return;
	}
	bYaExploto = true;

	if (MeshCubo != nullptr)
	{
		MeshCubo->SetVisibility(false);
		MeshCubo->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (FXExplosion != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FXExplosion, GetActorLocation(), GetActorRotation());
	}

	if (ParticulaExplosion != nullptr)
	{
		ParticulaExplosion->Activate(true);
	}

	if (CueExplosion != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CueExplosion, GetActorLocation());
	}

	if (SonidoExplosion != nullptr)
	{
		SonidoExplosion->Play();
	}

	SetLifeSpan(2.0f);
}
