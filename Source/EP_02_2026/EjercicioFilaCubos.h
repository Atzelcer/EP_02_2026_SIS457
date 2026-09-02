#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EjercicioFilaCubos.generated.h"

class ACuboEstatico;

UCLASS()
class EP_02_2026_API AEjercicioFilaCubos : public AActor
{
	GENERATED_BODY()

public:
	AEjercicioFilaCubos();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SpawnearFila();
	void PrepararCubos();
	void ExplotarPares();
	void ExplotarImpares();
	void PintarContador() const;

	UPROPERTY(EditAnywhere, Category = "Ejercicio")
	int32 CantidadCubos;

	UPROPERTY(EditAnywhere, Category = "Ejercicio")
	float Separacion;

	UPROPERTY(EditAnywhere, Category = "Ejercicio")
	float AlturaSubida;

	UPROPERTY(EditAnywhere, Category = "Ejercicio")
	float SegundosPares;

	UPROPERTY(EditAnywhere, Category = "Ejercicio")
	float SegundosImparesDespuesDePares;

	UPROPERTY(EditAnywhere, Category = "Ejercicio")
	FLinearColor ColorPares;

	UPROPERTY(EditAnywhere, Category = "Ejercicio")
	FLinearColor ColorImpares;

	UPROPERTY(EditAnywhere, Category = "Ejercicio")
	FVector OrigenFila;

	UPROPERTY()
	TArray<ACuboEstatico*> Cubos;

	float TiempoRestante;
	int32 Fase;
};
