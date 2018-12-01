// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h" // Debug
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	if (!Barrel || !Turret) { return; }

	FColor color = FColor(255, 0, 0);
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
		color = FColor(0, 255, 0);
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), GetWorld()->GetTimeSeconds())
	}
	else {
		AimDirection = GetOwner()->GetActorForwardVector();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution not found"), GetWorld()->GetTimeSeconds())
	}

	MoveBarrelTowards(AimDirection);
	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), HitLocation, color, false, 0.f, 0, 10.f);
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection){
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaBarrelRotator = AimRotator - BarrelRotator;
	FRotator DeltaTurretRotator = AimRotator - TurretRotator;
	float DeltaTurretRotatorYaw = DeltaTurretRotator.Yaw;

	//TODO: Delete log
	if (GetOwner()->GetName() == GetWorld()->GetFirstPlayerController()->GetPawn()->GetName()) {
		UE_LOG(LogTemp, Warning, TEXT("%f"), DeltaTurretRotator.Yaw)
	}

	// Prevent Turret Rotation going to the longest path
	if (FMath::Abs(DeltaTurretRotatorYaw) > 180) {
		DeltaTurretRotatorYaw *= -1;
	}
	
	Barrel->Elevate(DeltaBarrelRotator.Pitch);
	Turret->Rotate(DeltaTurretRotatorYaw);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
}

