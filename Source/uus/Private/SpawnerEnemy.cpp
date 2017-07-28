// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnerEnemy.h"
#include "Kismet/GameplayStatics.h"


ASpawnerEnemy::ASpawnerEnemy()
{
	SpawnInterval = 2;
	EnemiesToSpawn = 0;
	SpawnedEnemies = 0;

	PlayerFound = false;

	//Health = ?;
	//CanDropItems = ?;
}

void ASpawnerEnemy::BeginPlay()
{
	Super::BeginPlay();

	//PlayerCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnerEnemy::SpawnEnemy, SpawnInterval, true);
}

void ASpawnerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (GetHorizontalDistanceTo(PlayerCharacter) < 500 && !PlayerFound)
	//{
	//	// start spawning enemies at set intervals(in seconds)
	//	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnerEnemy::SpawnEnemy, SpawnInterval, true);
	//	PlayerFound = true;
	//}
}

void ASpawnerEnemy::SpawnEnemy()
{
	if (EnemiesToSpawn == 0)
	{
		// infinite spawning
		FActorSpawnParameters SpawnParams;
		AEnemy* EnemyActor = GetWorld()->SpawnActor<AEnemy>(EnemyBP, GetActorTransform(), SpawnParams);
	}
	else
	{
		// spawn set amount of enemies
		if (SpawnedEnemies < EnemiesToSpawn)
		{
			// spawn enemy
			FActorSpawnParameters SpawnParams;
			AEnemy* EnemyActor = GetWorld()->SpawnActor<AEnemy>(EnemyBP, GetActorTransform(), SpawnParams);

			SpawnedEnemies++;
		}
		else
		{
			// clear spawning timer when all enemies have been spawned
			GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		}
	}
}

