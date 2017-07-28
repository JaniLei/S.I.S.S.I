// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUp.h"
#include "ArmorPickUp.generated.h"

/**
 * 
 */
UCLASS()
class UUS_API AArmorPickUp : public APickUp
{
	GENERATED_BODY()
	
public:

	AArmorPickUp();


protected:

	UFUNCTION()
	void OnPlayerEnterPickUpBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	
};
