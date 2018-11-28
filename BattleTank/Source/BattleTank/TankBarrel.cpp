// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float ElevationChange = RelativeSpeed * DegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewElevation = RelativeRotation.Pitch + ElevationChange;
	float Elevation = FMath::Clamp<float>(NewElevation, MinDegrees, MaxDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}


