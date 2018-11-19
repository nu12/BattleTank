// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
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
	
private:
	ATank* TankPawn = nullptr;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 1.0/2.0;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 1.0/3.0;

	ATank * GetControlledTank();
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;
};
