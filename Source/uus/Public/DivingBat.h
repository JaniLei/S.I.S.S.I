// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlyingEnemy.h"
#include "DivingBat.generated.h"

/**
 * 
 */
UCLASS()
class UUS_API ADivingBat : public AFlyingEnemy
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ADivingBat();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

protected:

	FVector EndPosition;
	FVector AttackTarget;
	FVector StartPos;
	FVector NewDirection;

	float EndX, EndZ, StartX, StartZ, MiddleZ, TestX;

	float InterpSpeed;

	float ChangePositionInterval;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsTurning;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsDiving;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsBiting;
	bool BiteCooldown;

	// to the left of player when starting to dive;
	bool ToLeft;

	void DiveAtPlayer(float DeltaTime);

	FTimerHandle BehaviourTimerHandle;
	FTimerHandle BitingTimerHandle;
	FTimerHandle BiteCooldownTimerHandle;

	void ChooseNewRandomPos();

	void EndBiting();
	void RefreshBiteCooldown();

	UFUNCTION()
	void OnPlayerEnterBitingBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void CheckDirection() override;

	virtual void Movement(float DeltaTime) override;

	virtual void Attack() override;
	
	
};
