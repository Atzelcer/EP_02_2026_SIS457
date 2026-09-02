#include "EjercicioFilaCubos.h"
#include "CuboEstatico.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

AEjercicioFilaCubos::AEjercicioFilaCubos()
{
	PrimaryActorTick.bCanEverTick = true;

	CantidadCubos = 40;
	Separacion = 120.f;
	AlturaSubida = 200.f;
	SegundosPares = 5.f;
	SegundosImparesDespuesDePares = 8.f;
	ColorPares = FLinearColor(0.15f, 0.45f, 1.0f, 1.0f);
	ColorImpares = FLinearColor(1.0f, 0.15f, 0.1f, 1.0f);
	OrigenFila = FVector(400.f, 0.f, 50.f);
	TiempoRestante = 0.f;
	Fase = 0;
}

void AEjercicioFilaCubos::BeginPlay()
{
	Super::BeginPlay();

	SpawnearFila();
	PrepararCubos();

	TiempoRestante = SegundosPares;
	Fase = 0;
}

void AEjercicioFilaCubos::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Fase > 1)
	{
		return;
	}

	TiempoRestante -= DeltaTime;
	PintarContador();

	if (TiempoRestante > 0.f)
	{
		return;
	}

	if (Fase == 0)
	{
		ExplotarPares();
		TiempoRestante = SegundosImparesDespuesDePares;
		Fase = 1;
		return;
	}

	ExplotarImpares();
	Fase = 2;
}

void AEjercicioFilaCubos::SpawnearFila()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		return;
	}

	Cubos.Empty();
	Cubos.Reserve(CantidadCubos);

	FVector Inicio = OrigenFila;
	FVector DireccionFila = FVector::RightVector;

	if (APawn* Player = UGameplayStatics::GetPlayerPawn(this, 0))
	{
		DireccionFila = Player->GetActorRightVector();
		const float AnchoTotal = (CantidadCubos - 1) * Separacion;
		Inicio = Player->GetActorLocation()
			+ Player->GetActorForwardVector() * 400.f
			- DireccionFila * (AnchoTotal * 0.5f);
		Inicio.Z = Player->GetActorLocation().Z;
	}

	for (int32 i = 0; i < CantidadCubos; ++i)
	{
		const FVector SpawnLocation = Inicio + DireccionFila * (i * Separacion);
		ACuboEstatico* NuevoCubo = World->SpawnActor<ACuboEstatico>(SpawnLocation, FRotator::ZeroRotator);

		if (NuevoCubo != nullptr)
		{
			Cubos.Add(NuevoCubo);
		}
	}
}

void AEjercicioFilaCubos::PrepararCubos()
{
	for (int32 i = 0; i < Cubos.Num(); ++i)
	{
		ACuboEstatico* Cubo = Cubos[i];
		if (Cubo == nullptr)
		{
			continue;
		}

		const bool bPar = (i % 2 == 0);
		Cubo->SetEsPar(bPar);
		Cubo->AplicarColor(bPar ? ColorPares : ColorImpares);

		if (!bPar)
		{
			Cubo->AddActorWorldOffset(FVector(0.f, 0.f, AlturaSubida));
		}
	}
}

void AEjercicioFilaCubos::ExplotarPares()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Cyan, TEXT("Pares explotaron"));
	}

	for (ACuboEstatico* Cubo : Cubos)
	{
		if (IsValid(Cubo) && Cubo->EsPar() && !Cubo->YaExploto())
		{
			Cubo->Explotar();
		}
	}
}

void AEjercicioFilaCubos::ExplotarImpares()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, TEXT("Impares explotaron"));
	}

	for (ACuboEstatico* Cubo : Cubos)
	{
		if (IsValid(Cubo) && !Cubo->EsPar() && !Cubo->YaExploto())
		{
			Cubo->Explotar();
		}
	}

	Cubos.Empty();
}

void AEjercicioFilaCubos::PintarContador() const
{
	if (GEngine == nullptr)
	{
		return;
	}

	const int32 Segundos = FMath::Max(0, FMath::CeilToInt(TiempoRestante));
	FString Texto;

	if (Fase == 0)
	{
		Texto = FString::Printf(TEXT("Pares explotan en: %d"), Segundos);
		GEngine->AddOnScreenDebugMessage(1, 0.2f, FColor::Cyan, Texto);
	}
	else
	{
		Texto = FString::Printf(TEXT("Impares explotan en: %d"), Segundos);
		GEngine->AddOnScreenDebugMessage(1, 0.2f, FColor::Orange, Texto);
	}
}
