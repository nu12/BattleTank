// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/StaticMesh.h"

void UTankTrack::SetThrottle(float Throttle){
	FVector ForceApplied = GetForwardVector() * Throttle * MaxTrackDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent * TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


