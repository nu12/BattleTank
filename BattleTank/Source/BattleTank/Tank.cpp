// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"


ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
float ATank::GetHealth()
{
	return (float)CurrentHealth / (float)StartingHealth;
}
float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser){
	float Damage = FMath::Clamp<float>(DamageAmount, 0, CurrentHealth);
	CurrentHealth -= Damage;
	return Damage;
}
