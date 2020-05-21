// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	
private:
	ATank* PlayerControlledTank = nullptr;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.333333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 100000.f; // 1 kilometre

	ATank* GetPlayerControlledTank() const;

	// start moving the barrel of the tank, so that a shot
	// would hit where the crosshair intersects the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& WorldLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector& Out_HitLocation, FVector LookDirection) const;
};
