// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
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
	if (!Barrel) { return; }

	FColor color = FColor(255, 0, 0);
	FVector OutLaunchVelocity = FVector(0.f);
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
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		color = FColor(0, 255, 0);
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), GetWorld()->GetTimeSeconds())
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution not found"), GetWorld()->GetTimeSeconds())
	}


	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), HitLocation, color, false, 0.f, 0, 10.f);
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection){
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaAimRotator = AimRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("%f | %f | %f"), BarrelRotator.Pitch, AimRotator.Pitch, DeltaAimRotator.Pitch)

	Barrel->Elevate(DeltaAimRotator.Pitch);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

