// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	float Speed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float Rotation = Speed * DegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float ActualYaw = RelativeRotation.Yaw;

	SetRelativeRotation(FRotator(0.f, ActualYaw + Rotation, 0.f));
}
