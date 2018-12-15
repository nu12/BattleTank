// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h" // Debug
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AvailableAmmo <= 0) {
		FiringState = EFiringState::OutOfAmmo;
	}
	else if (GetWorld()->TimeSeconds - LastFireTime < ReloadTimeInSeconds) {
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringState = EFiringState::Aiming;
	}
	else {
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }

	FVector OutLaunchVelocity = FVector(0.f);
	FVector AimDirection = FVector(0.f);
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		Barrel->GetSocketLocation(FName("Projectile")),
		HitLocation,
		LaunchSpeed, 
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	)) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		LastAimDirection = AimDirection;
	}

	//TODO remove debug line
	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), HitLocation, FColor(255,0,0), false, 0.f, 0, 10.f); // DebugLine
}

void UTankAimingComponent::Fire() {
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }	
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming) {

		AProjectile * Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->TimeSeconds;		
		AvailableAmmo -= 1;
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection){
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaBarrelRotator = AimRotator - BarrelRotator;
	FRotator DeltaTurretRotator = AimRotator - TurretRotator;
	float DeltaTurretRotatorYaw = DeltaTurretRotator.Yaw;

	// Prevent Turret Rotation going to the longest path
	if (FMath::Abs(DeltaTurretRotatorYaw) > 180) {
		DeltaTurretRotatorYaw *= -1;
	}
	
	Barrel->Elevate(DeltaBarrelRotator.Pitch);
	Turret->Rotate(DeltaTurretRotatorYaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	return !LastAimDirection.Equals(Barrel->GetForwardVector(), 0.01);
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetAvailableAmmo() const
{
	return AvailableAmmo;
}
