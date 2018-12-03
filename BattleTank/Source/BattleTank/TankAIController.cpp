// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
	ControlledTank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::Tick(float Delta){
	Super::Tick(Delta);
	if (!ControlledTank || !PlayerTank) { return; }

	FVector HitLocation = PlayerTank->GetActorLocation();
	ControlledTank->AimAt(HitLocation);
	ControlledTank->Fire();
}