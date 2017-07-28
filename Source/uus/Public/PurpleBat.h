// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GreenBug.h"
#include "PurpleBat.generated.h"

/**
 * 
 */
UCLASS()
class UUS_API APurpleBat : public AGreenBug
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APurpleBat();

	
protected:

	FVector NewDirection;

	float ChangePositionInterval;

	FTimerHandle BehaviourTimerHandle;

	void ChooseNewRandomPos();

	virtual void Movement(float DeltaTime) override;
	
};
