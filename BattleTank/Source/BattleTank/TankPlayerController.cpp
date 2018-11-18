// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"

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
	if (!TankPawn) { return; }

	FVector HitLocation;
	
	if (GetSightRayHitLocation(HitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("Ye Hit"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Hit"));
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	FHitResult HitResult;
	bool Hit = GetWorld()->LineTraceSingleByChannel(HitResult,
		TankPawn->GetActorLocation(),
		TankPawn->GetActorLocation() + TankPawn->GetViewRotation().Vector() * 10000.f,
		ECollisionChannel::ECC_WorldStatic
	);
	if (Hit) {
		OutHitLocation = HitResult.GetActor()->GetActorLocation();
	}
	return Hit;
}
