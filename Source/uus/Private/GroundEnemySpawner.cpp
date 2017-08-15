// Fill out your copyright notice in the Description page of Project Settings.

#include "GroundEnemySpawner.h"
#include "EngineUtils.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGroundEnemySpawner::AGroundEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AGroundEnemySpawner::CheckEnemiesOnScreen(int32 EnemyAmount)
{
	int32 EnemyCount = 0;

	for (TActorIterator<AEnemy> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		AEnemy *Enemy = *ActorItr;

		const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		FVector EnemyPos = ActorItr->GetActorLocation();
		FVector2D EnemyOnScreen;

		UGameplayStatics::ProjectWorldToScreen(UGameplayStatics::GetPlayerController(GetWorld(), 0), EnemyPos, EnemyOnScreen);

		if (EnemyOnScreen.X > 0 && EnemyOnScreen.X < ViewportSize.X &&
			EnemyOnScreen.Y > 0 && EnemyOnScreen.Y < ViewportSize.Y)
		{
			EnemyCount++;
		}
	}

	if (EnemyCount < EnemyAmount && LookForPlayer())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool AGroundEnemySpawner::LookForPlayer()
{
	PlayerCharacter = Cast<AMyMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	FVector DistanceVector = PlayerCharacter->GetActorLocation() - GetActorLocation();

	// if player is within "sight" range(500)
	if (DistanceVector.X < 500 && DistanceVector.X > -500 &&
		DistanceVector.Z < 500 && DistanceVector.Z > -500)
	{
		return true;
	}
	else
	{
		return false;
	}
}
