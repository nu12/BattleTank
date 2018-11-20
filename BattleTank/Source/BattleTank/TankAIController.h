// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;
	void Tick(float Delta) override;

private:
	ATank * TankPawn = nullptr;
	ATank * PlayerTank = nullptr; // This will be the target

	ATank * GetControlledTank();
	ATank * GetPlayerTank();
	
};
