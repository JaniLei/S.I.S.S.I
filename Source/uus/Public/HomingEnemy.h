// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "HomingEnemy.generated.h"

/**
 * 
 */
UCLASS()
class UUS_API AHomingEnemy : public AEnemy
{
	GENERATED_BODY()

	AHomingEnemy();

public:

	virtual void Tick(float DeltaSeconds) override;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsExploding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	void Movement();
	
};
