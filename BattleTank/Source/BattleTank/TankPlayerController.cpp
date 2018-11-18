// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

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
	//AimTowardsCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!TankPawn) { return; }
}