// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtraAmmoPickUp.h"


void AExtraAmmoPickUp::OnPlayerEnterPickUpBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnPlayerEnterPickUpBox(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (PlayerCharacter)
	{
		if (!PlayerCharacter->HasExtraAmmo)
		{
			PlayerCharacter->AddExtraAmmo();
			Destroy();
		}
	}
}

