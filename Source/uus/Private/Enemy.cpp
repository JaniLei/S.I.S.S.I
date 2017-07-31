// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "uus.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("EnemyRoot"));
	RootComponent = EnemyRoot;

	EnemyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemyBox"));
	EnemyBox->SetBoxExtent(FVector(40, 0, 40));
	EnemyBox->bGenerateOverlapEvents = true;
	EnemyBox->SetupAttachment(RootComponent);

	Health = 1;
	CanDropItems = true;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::DamageEnemy(int32 Amount)
{
	Health -= Amount;
	if (Health <= 0 && !IsPendingKill())
	{
		EnemyDeath();
	}
}

void AEnemy::EnemyDeath()
{
	EnemyState = EEnemyState::Dead;
	// item drops / score
	if (CanDropItems)
	{
		SpawnDrop();
	}
	// destroy enemy
	/*if (!IsPendingKill())
	{
		Destroy();
	}*/
}

void AEnemy::SpawnDrop()
{
	if (DropTable.Num() > 0)
	{
		UClass* Drop = DropTable[0];

		if (DropTable.Num() > 1)
		{
			// randomly choosing index from droptable if more than 1 possible drop
			UClass* Drop = DropTable[FMath::RandRange(0, DropTable.Num() - 1)];
		}

		if (Drop)
		{
			FActorSpawnParameters SpawnParams;
			APickUp* PickUpDrop = GetWorld()->SpawnActor<APickUp>(Drop, GetActorTransform(), SpawnParams);
		}
	}
}
