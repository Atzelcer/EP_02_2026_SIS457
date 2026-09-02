#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CuboEstatico.generated.h"

class UStaticMeshComponent;
class UAudioComponent;
class UParticleSystemComponent;
class UParticleSystem;
class USoundBase;
class UTexture2D;
class UMaterialInterface;
class UMaterialInstanceDynamic;

UCLASS()
class EP_02_2026_API ACuboEstatico : public AActor
{
	GENERATED_BODY()

public:


	ACuboEstatico();

	void Explotar();
	void AplicarColor(const FLinearColor& Color);
	void SetEsPar(bool bNuevoEsPar) { bEsPar = bNuevoEsPar; }
	bool EsPar() const { return bEsPar; }
	bool YaExploto() const { return bYaExploto; }

	UStaticMeshComponent* GetMesh() const { return MeshCubo; }

private:
	UPROPERTY(VisibleAnywhere, Category = "Cubo")
	UStaticMeshComponent* MeshCubo;

	UPROPERTY(VisibleAnywhere, Category = "Cubo")
	UAudioComponent* SonidoExplosion;

	UPROPERTY(VisibleAnywhere, Category = "Cubo")
	UParticleSystemComponent* ParticulaExplosion;

	UPROPERTY()
	UTexture2D* TexturaCubo;

	UPROPERTY()
	UMaterialInterface* MaterialCubo;

	UPROPERTY()
	UParticleSystem* FXExplosion;

	UPROPERTY()
	USoundBase* CueExplosion;

	bool bYaExploto;
	bool bEsPar;
};
