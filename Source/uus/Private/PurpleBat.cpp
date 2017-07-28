// Fill out your copyright notice in the Description page of Project Settings.

#include "PurpleBat.h"


APurpleBat::APurpleBat()
{
	ChangePositionInterval = 5;
	AttackInterval = 3;
}

void APurpleBat::Movement(float DeltaTime)
{
	if (PlayerFound)
	{
		if (!GetWorldTimerManager().IsTimerActive(BehaviourTimerHandle))
		{
			GetWorldTimerManager().SetTimer(BehaviourTimerHandle, this, &APurpleBat::ChooseNewRandomPos, ChangePositionInterval, true, 1);
		}

		FVector EnemyDirection = NewDirection - EnemyLocation;
		EnemyDirection.Normalize();
		EnemyDirection.X *= Speed;
		EnemyDirection.Z *= Speed;


		MovementVector = EnemyLocation + EnemyDirection;

		if (EnemyLocation.X < NewDirection.X - 4 || EnemyLocation.X > NewDirection.X + 4)
		{
			SetActorLocation(MovementVector);
		}
	}
}

void APurpleBat::ChooseNewRandomPos()
{
	FVector NewRandomPos = FVector(FMath::FRandRange(PlayerLocation.X - 225, PlayerLocation.X + 225), 0, FMath::FRandRange(PlayerLocation.Z + 100, PlayerLocation.Z + 180));
	NewDirection = NewRandomPos;
}
