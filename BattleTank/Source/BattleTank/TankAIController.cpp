// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay() {

	Super::BeginPlay();
	TankPawn = GetControlledTank();
	if (TankPawn) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found Pawn: %s"), *(TankPawn->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No Pawn found for TankAIController"));
	}

}

ATank * ATankAIController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
}
