// Fill out your copyright notice in the Description page of Project Settings.

#include "UsablePickUp.h"


void AUsablePickUp::UseItem()
{
	IsUsed = true;
}

void AUsablePickUp::OnPlayerEnterPickUpBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerEnterPickUpBox(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (PlayerCharacter && !IsPendingKill())
	{
		SetLifeSpan(0);
		PlayerCharacter->AddUsableItem(this);
		// clear despawn timer
		// disable components
		//PickUpRoot->Deactivate();
		//PickUpBox->Deactivate();
		//PickUpSprite->SetVisibility(false);
		//PickUpSprite->Deactivate();
		Destroy();
	}
}

