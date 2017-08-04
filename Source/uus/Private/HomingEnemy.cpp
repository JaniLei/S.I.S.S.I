// Fill out your copyright notice in the Description page of Project Settings.

#include "HomingEnemy.h"


AHomingEnemy::AHomingEnemy()
{
	Speed = 2;
}

void AHomingEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!IsExploding)
	{
		if (PlayerCharacter)
		{
			PlayerFound = LookForPlayer();
		}
		if (PlayerFound)
		{
			Movement();
		}
	}
}

void AHomingEnemy::Movement()
{
	FVector Direction = PlayerLocation - EnemyLocation;
	Direction.Normalize();
	Direction.X *= Speed;
	Direction.Z *= Speed;
	SetActorLocation(EnemyLocation + Direction);
}
