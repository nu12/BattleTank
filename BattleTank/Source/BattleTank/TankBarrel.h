// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))//, hidecategories=("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	void Elevate(float RelativeSpeed);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float DegreesPerSecond = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegrees = 40.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinDegrees = 0.f;
	
};
