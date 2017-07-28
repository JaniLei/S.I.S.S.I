// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlyingEnemy.h"
#include "GreenBug.generated.h"

/**
 * 
 */
UCLASS()
class UUS_API AGreenBug : public AFlyingEnemy
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AGreenBug();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
protected:

	float MovementInterval;

	UPROPERTY(EditAnywhere)
	bool IsBat;

	FTimerHandle MovementBehaviourTimerHandle;

	void ChangeMovementBehaviour();

	virtual void Attack() override;
	
};
