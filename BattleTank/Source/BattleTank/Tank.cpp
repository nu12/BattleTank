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