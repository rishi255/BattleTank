#include "TankPlayerController.h"
#include "DrawDebugHelpers.h"

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

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		PlayerControlledTank->AimAt(HitLocation);
	}
}

// Get world location of line trace through crosshair, retunr true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& Out_HitLocation) const
{
	/// find crosshair position in pixel coordinates (where the dot is aiming right now)
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	FVector LookDirection, WorldLocation;
	if (GetLookDirection(ScreenLocation, WorldLocation, LookDirection))
	{
		/// Line-trace along the look direction we just got, see what we hit (max distance = LineTraceRange)
		GetLookVectorHitLocation(Out_HitLocation, LookDirection);
	}

	return true;
}

/// De-project screen position of crosshair to a world direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& Out_WorldLocation, FVector& Out_LookDirection) const
{
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		Out_WorldLocation,
		Out_LookDirection
	);
	//UE_LOG(LogTemp, Warning, TEXT("WorldDirection: %s"), *Out_LookDirection.ToString());
}

// this does the actual line-trace, sets Out_HitLocation.
bool ATankPlayerController::GetLookVectorHitLocation(FVector& Out_HitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	auto Params = FCollisionQueryParams(TEXT(""), false, PlayerControlledTank);

	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	/// if line trace by visibility channel succeeds, set Out_HitLocation.
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility,
		Params)
	)
	{
		DrawDebugLine(
			GetWorld(),
			StartLocation,
			EndLocation,
			FColor(255, 0, 0),
			false,
			0.f,
			0.f,
			10.f);

		//UE_LOG(LogTemp, Warning, TEXT("HitResult: %s, HitLocation: %s"), 
			//*(HitResult.GetActor()->GetName()), *(HitResult.Location.ToString()));
		Out_HitLocation = HitResult.Location;
		return true;
	}
	// setting to (0,0,0) where the line-trace doesn't hit anything
	Out_HitLocation = FVector(0.f);
	return false;
}
