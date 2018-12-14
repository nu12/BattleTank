// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/StaticMesh.h"

void UTankTrack::SetThrottle(float Throttle){
	FVector ForceApplied = GetForwardVector() * Throttle * MaxTrackDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent * TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	
	// -SlippageSpeed because we need to pull the tank in the opposite direction
	FVector CorrectionAcceleration = - SlippageSpeed / DeltaTime * GetRightVector(); 

	UStaticMeshComponent * TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2; // Two Tracks

	TankRoot->AddForce(CorrectionForce);
}
