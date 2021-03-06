// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent * AimingComponent);
	
private:

	virtual void SetPawn(APawn * InPawn) override;
	UFUNCTION()
	void OnPossessedTankDeath();
	
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 1.0/2.0;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 1.0/3.0;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;

	bool GetLookVectorDirection(FVector LookDirection, FVector &OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;
};
