// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerUpPickUp.h"


void APowerUpPickUp::OnPlayerEnterPickUpBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnPlayerEnterPickUpBox(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (PlayerCharacter)
	{
		// if multiplier is not at max (x2)
		if (PlayerCharacter->GetDamageMultiplier() < 2)
		{
			// add 0.1 to multiplier and destroy self
			PlayerCharacter->AddDamageMultiplier(0.1f);
			Destroy();
		}
	}
}

