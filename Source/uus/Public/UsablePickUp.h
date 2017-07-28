// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUp.h"
#include "UsablePickUp.generated.h"

/**
 * 
 */
UCLASS()
class UUS_API AUsablePickUp : public APickUp
{
	GENERATED_BODY()

public:

	virtual void UseItem();

	bool IsUsed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString PickUpName;
	
protected:

	UFUNCTION()
	virtual void OnPlayerEnterPickUpBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	
};
