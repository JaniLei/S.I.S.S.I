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
		if (PlayerFound && LineTraceToPlayer())
		{
			Movement();
		}
	}
}

void AHomingEnemy::CheckDirectionToPlayer()
{
	if (EnemyLocation.X >= PlayerLocation.X)
	{
		SetActorRotation(FRotator(0, 0, 0));
	}
	else
	{
		SetActorRotation(FRotator(0, 180, 0));
	}
}

void AHomingEnemy::Movement()
{
	CheckDirectionToPlayer();
	FVector Direction = PlayerLocation - EnemyLocation;
	Direction.Normalize();
	Direction.X *= Speed;
	Direction.Z *= Speed;
	SetActorLocation(EnemyLocation + Direction);
}
