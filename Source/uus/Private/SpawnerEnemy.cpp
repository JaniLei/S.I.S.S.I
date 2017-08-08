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
}

void ASpawnerEnemy::BeginPlay()
{
	Super::BeginPlay();

	//PlayerCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	//GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnerEnemy::SpawnEnemy, SpawnInterval, true);
}

void ASpawnerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector DistanceVector = PlayerLocation - EnemyLocation;

	// if player is within "sight" range(400)
	if (DistanceVector.X < 800 && DistanceVector.X > -800 &&
		DistanceVector.Z < 800 && DistanceVector.Z > -800 && !PlayerFound)
	{
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnerEnemy::SpawnEnemy, SpawnInterval, true);
		PlayerFound = true;
	}
}

void ASpawnerEnemy::SpawnEnemy()
{
	FTransform SpawnTransform;
	FVector ActorLocation = GetActorLocation();
	SpawnTransform.SetLocation(FVector(FMath::FRandRange(ActorLocation.X - 20, ActorLocation.X + 20), 0, FMath::FRandRange(ActorLocation.Z - 20, ActorLocation.Z + 20)));

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

