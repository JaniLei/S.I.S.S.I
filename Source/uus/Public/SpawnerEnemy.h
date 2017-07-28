// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "MainCharacter.h"
#include "SpawnerEnemy.generated.h"

/**
 * 
 */
UCLASS()
class UUS_API ASpawnerEnemy : public AEnemy
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASpawnerEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	/** The number of enemies to spawn (infinite spawning if set to 0)*/
	UPROPERTY(EditAnyWhere, Category = "Spawning")
	int32 EnemiesToSpawn;

	/** Seconds between enemy spawns*/
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float SpawnInterval;

	/** Blueprint of enemy to spawn*/
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AEnemy> EnemyBP;

protected:

	int32 SpawnedEnemies;

	void SpawnEnemy();

	AMainCharacter* PlayerCharacter;
	bool PlayerFound;

private:

	FTimerHandle SpawnTimerHandle;
	
	
};
