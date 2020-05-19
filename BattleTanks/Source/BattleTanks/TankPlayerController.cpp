#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Inside TankPlayerController BeginPlay() !!!"));
	
	PlayerControlledTank = GetPlayerControlledTank();

	if (!PlayerControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank not found!!!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank = %s"), *PlayerControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetPlayerControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!PlayerControlledTank) { return; }
}