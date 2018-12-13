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
	PrimaryComponentTick.bCanEverTick = false;
}
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (!ensure(Barrel && Turret)) { return; }

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
	}

	//TODO remove debug line
	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), HitLocation, FColor(255,0,0), false, 0.f, 0, 10.f); // DebugLine
}

void UTankAimingComponent::Fire() {
	bool isReloaded = GetWorld()->TimeSeconds - LastFireTime > ReloadTimeInSeconds;
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }
	if (isReloaded) {
		AProjectile * Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->TimeSeconds;
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

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

