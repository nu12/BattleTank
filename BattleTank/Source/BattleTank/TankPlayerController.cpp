// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	TankPawn = Cast<ATank>(GetPawn());

	if (TankPawn) {
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController found Pawn: %s"), *(TankPawn->GetName()));
	}
}

ATank * ATankPlayerController::GetControlledTank() const {
	return TankPawn;
}



