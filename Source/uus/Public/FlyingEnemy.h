// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy.h"
#include "FlyingEnemy.generated.h"

/**
*
*/

UCLASS()
class UUS_API AFlyingEnemy : public AEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFlyingEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

protected:

	//enum EnemyStates { Idle, Moving, Attacking };
	//EnemyStates EnemyState;
	

	UPROPERTY(EditAnywhere)
	UBoxComponent* AttackBox;

	/** Blueprint of enemy to spawn*/
	UPROPERTY(EditAnywhere, Category = "Shooting")
	TSubclassOf<AActor> ProjectileBP;

	FVector MovementVector;
	FVector LastLocation;
	FVector FloatingLocation;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsShooting;
	bool IsHit;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool PlayerFound;

	float AttackInterval;

	float RunningTime;

	/** Movement speed*/
	UPROPERTY(EditAnywhere, Category = "EnemyVariables")
	float Speed;

	virtual void Movement(float DeltaTime);

	virtual void CheckDirection();

	bool LookForPlayer();

	UFUNCTION()
	virtual void OnPlayerEnterAttackBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnPlayerExitAttackBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void Attack();

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	virtual void DamageEnemy(int32 Amount) override;

	FTimerHandle AttackTimerHandle;

};
