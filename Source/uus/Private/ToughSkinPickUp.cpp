// Fill out your copyright notice in the Description page of Project Settings.

#include "ToughSkinPickUp.h"


void AToughSkinPickUp::OnPlayerEnterPickUpBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnPlayerEnterPickUpBox(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (PlayerCharacter)
	{
		// if damage mitigation is not over the maximum (20%)
		if (PlayerCharacter->GetDamageMitigation() < 0.2f)
		{
			PlayerCharacter->AddDamageMitigation(0.05f);
			Destroy();
		}
	}
}

