// Fill out your copyright notice in the Description page of Project Settings.

#include "AmmoPickUp.h"


AAmmoPickUp::AAmmoPickUp()
{
	AmountValue = 6;
}


void AAmmoPickUp::OnPlayerEnterPickUpBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnPlayerEnterPickUpBox(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (PlayerCharacter)
	{
		PlayerCharacter->AddAmmo(AmountValue);
		Destroy();
	}

}

void AAmmoPickUp::ChooseRandomAmmoType()
{
	AmmoType = static_cast<AmmoTypes>(rand() % AmmoTypes::Rocket);
}

