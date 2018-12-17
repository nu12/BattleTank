// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn * InPawn){
	Super::SetPawn(InPawn);
	if (InPawn) {
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (PossessedTank) {
			PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
		}
	}
}
void ATankAIController::OnPossessedTankDeath(){
	APawn * Pawn = GetPawn();
	if (!ensure(Pawn)) { return; }
	Pawn->DetachFromControllerPendingDestroy();
}
void ATankAIController::Tick(float Delta){
	Super::Tick(Delta);	
	APawn * PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank) { return; }
	FVector HitLocation = PlayerTank->GetActorLocation();
	UTankAimingComponent * AimingComponent = GetPawn()->FindComponentByClass< UTankAimingComponent>();
	AimingComponent->AimAt(HitLocation);
	if (AimingComponent->GetFiringState() == EFiringState::Locked) {
		AimingComponent->Fire();
	}

	UTankMovementComponent * MovementComponent = GetPawn()->FindComponentByClass< UTankMovementComponent>();
	if (MovementComponent) {
		MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(), GetPawn()->FindComponentByClass< UTankMovementComponent>()->AcceptanceRadius);
	}
	
}