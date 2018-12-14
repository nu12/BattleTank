// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float Delta){
	Super::Tick(Delta);

	FVector HitLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	GetPawn()->FindComponentByClass< UTankAimingComponent>()->AimAt(HitLocation);
	GetPawn()->FindComponentByClass< UTankAimingComponent>()->Fire();
	
	// TODO include AcceptanceRadius variable in MovementComponent
	MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(), 3000.f);
}