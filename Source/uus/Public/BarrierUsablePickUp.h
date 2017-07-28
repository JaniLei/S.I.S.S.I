// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsablePickUp.h"
#include "Barrier.h"
#include "BarrierUsablePickUp.generated.h"

/**
 * 
 */
UCLASS()
class UUS_API ABarrierUsablePickUp : public AUsablePickUp
{
	GENERATED_BODY()

	ABarrierUsablePickUp();
	
public:

	virtual void UseItem() override;

protected:

	float OffsetX;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "BarrierSpawn")
	TSubclassOf<ABarrier> BarrierBP;

	
};
