// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATank* GetAIControlledTank() const;
	ATank* GetPlayerTank() const;
	void BeginPlay() override;

private:
	ATank* AIControlledTank = nullptr;
	ATank* PlayerTank = nullptr;
};
