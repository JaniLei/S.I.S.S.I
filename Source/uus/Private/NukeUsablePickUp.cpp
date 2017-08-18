// Fill out your copyright notice in the Description page of Project Settings.

#include "NukeUsablePickUp.h"
#include "EngineUtils.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"


ANukeUsablePickUp::ANukeUsablePickUp()
{
	PickUpName = "Nuke";
}

void ANukeUsablePickUp::UseItem()
{
	Super::UseItem();

	ScreenFlash();

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
			if (!ActorItr->IsPendingKill())
			{
				ActorItr->EnemyDeath();
			}
		}
	}
}

void ANukeUsablePickUp::ScreenFlash_Implementation() { }

