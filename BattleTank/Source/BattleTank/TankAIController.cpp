// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
	ControlledTank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::Tick(float Delta){
	Super::Tick(Delta);
	if (!ensure(ControlledTank && PlayerTank)) { return; }

	FVector HitLocation = PlayerTank->GetActorLocation();
	ControlledTank->GetTankAimingComponent()->AimAt(HitLocation);
	ControlledTank->GetTankAimingComponent()->Fire();

	MoveToActor(PlayerTank, ControlledTank->AcceptanceRadius);
}