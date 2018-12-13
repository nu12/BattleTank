// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	TankPawn = GetControlledTank();

	if (TankPawn) {
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController found Pawn: %s"), *(TankPawn->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No Pawn found for TankPlayerController"));
	}
}

void ATankPlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!ensure(TankPawn)) { return; }

	FVector HitLocation;
	
	if (GetSightRayHitLocation(HitLocation)) {
		TankPawn->AimAt(HitLocation);
	}
	

}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	int32 SizeX, SizeY;
	GetViewportSize(SizeX, SizeY);
	FVector2D ScreenLocation = FVector2D(SizeX * CrossHairXLocation, SizeY * CrossHairYLocation);
	FVector WorldDirection;
	/// De-project the screen position of the crosshair to a world location
	if (GetLookDirection(ScreenLocation, WorldDirection)) {
		// Line-trace along that look direction
		return GetLookVectorDirection(WorldDirection, OutHitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookVectorDirection(FVector LookDirection, FVector &OutHitLocation) const {
	FHitResult HitResult;
	FVector StartLine = PlayerCameraManager->GetCameraLocation();
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		StartLine,
		StartLine + LookDirection * LineTraceRange,
		ECC_Visibility)
		) {
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const {
	FVector WorldLocation; // To be discarted
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		WorldLocation,
		LookDirection);
}