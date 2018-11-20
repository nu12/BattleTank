// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
	TankPawn = GetControlledTank();
	PlayerTank = GetPlayerTank();
	if (TankPawn) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found Pawn: %s"), *(TankPawn->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No Pawn found for TankAIController"));
	}

	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found PlayerTank: %s"), *(PlayerTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("PlayerTank not found"));
	}

}

void ATankAIController::Tick(float Delta){
	Super::Tick(Delta);
	if (!TankPawn || !PlayerTank) { return; }

	FVector HitLocation = PlayerTank->GetActorLocation();
	TankPawn->AimAt(HitLocation);
}

ATank * ATankAIController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank()
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
