// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnerEnemy.h"
#include "Kismet/GameplayStatics.h"


ASpawnerEnemy::ASpawnerEnemy()
{
	SpawnInterval = 2;
	EnemiesToSpawn = 0;
	SpawnedEnemies = 0;

	PlayerFound = false;

	Health = 100;
	//CanDropItems = ?;
	LoSDistance = 800;
}

void ASpawnerEnemy::BeginPlay()
{
	Super::BeginPlay();

	//GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnerEnemy::SpawnEnemy, SpawnInterval, true);
}

void ASpawnerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector DistanceVector = PlayerLocation - EnemyLocation;

	// if player is within line of sight range
	if (DistanceVector.X < LoSDistance && DistanceVector.X > -LoSDistance &&
		DistanceVector.Z < LoSDistance && DistanceVector.Z > -LoSDistance && !PlayerFound)
	{
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnerEnemy::SpawnEnemy, SpawnInterval, true, SpawnInterval);
		PlayerFound = true;
	}
}

void ASpawnerEnemy::SpawnEnemy()
{
	FTransform SpawnTransform;
	FVector ActorLocation = GetActorLocation();
	SpawnTransform.SetLocation(FVector(FMath::FRandRange(ActorLocation.X - 40, ActorLocation.X + 40), 0, FMath::FRandRange(ActorLocation.Z - 40, ActorLocation.Z + 40)));

	if (EnemiesToSpawn == 0)
	{
		// infinite spawning
		FActorSpawnParameters SpawnParams;
		AEnemy* EnemyActor = GetWorld()->SpawnActor<AEnemy>(EnemyBP, SpawnTransform, SpawnParams);
	}
	else
	{
		// spawn set amount of enemies
		if (SpawnedEnemies < EnemiesToSpawn)
		{
			// spawn enemy
			FActorSpawnParameters SpawnParams;
			AEnemy* EnemyActor = GetWorld()->SpawnActor<AEnemy>(EnemyBP, SpawnTransform, SpawnParams);

			SpawnedEnemies++;
		}
		else
		{
			// clear spawning timer when all enemies have been spawned
			GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		}
	}
}

