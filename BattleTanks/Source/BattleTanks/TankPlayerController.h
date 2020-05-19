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
	ATank* GetPlayerControlledTank() const;
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	// start moving the barrel of the tank, so that a shot
	// would hit where the crosshair intersects the world
	void AimTowardsCrosshair();
	
private:
	ATank* PlayerControlledTank = nullptr;
};
