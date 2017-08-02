// Fill out your copyright notice in the Description page of Project Settings.

#include "NukeUsablePickUp.h"
#include "EngineUtils.h"
#include "Enemy.h"


void ANukeUsablePickUp::UseItem()
{
	Super::UseItem();

	for (TActorIterator<AEnemy> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		AEnemy *Enemy = *ActorItr;

		const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		FVector PlayerPos = PlayerCharacter->GetActorLocation();
		FVector ScreenToPlayerMax = FVector(PlayerPos.X + (ViewportSize.X / 2), 0, PlayerPos.Z + (ViewportSize.Y / 2));
		FVector ScreenToPlayerMin = FVector(PlayerPos.X - (ViewportSize.X / 2), 0, PlayerPos.Z - (ViewportSize.Y / 2));
		FVector EnemyPos = ActorItr->GetActorLocation();

		if (EnemyPos.X < ScreenToPlayerMax.X && EnemyPos.X > ScreenToPlayerMin.X &&
			EnemyPos.Z < ScreenToPlayerMax.Z && EnemyPos.Z > ScreenToPlayerMin.Z)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Boom!"));
			if (!ActorItr->IsPendingKill())
			{
				ActorItr->EnemyDeath();
			}
		}
		// Check to see if enemy has been rendered recently (if it is on screen)
		/*if (ActorItr->GetLastRenderTime() > 0.01f)
		{
			if (!ActorItr->IsPendingKill())
			{
				ActorItr->Destroy();
			}
		}*/
	}

}

