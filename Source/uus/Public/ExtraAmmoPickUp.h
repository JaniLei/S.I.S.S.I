// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUp.h"
#include "ExtraAmmoPickUp.generated.h"

/**
 * 
 */
UCLASS()
class UUS_API AExtraAmmoPickUp : public APickUp
{
	GENERATED_BODY()
	
protected:

	UFUNCTION()
	virtual void OnPlayerEnterPickUpBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	
};
