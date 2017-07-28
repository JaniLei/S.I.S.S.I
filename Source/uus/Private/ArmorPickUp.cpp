// Fill out your copyright notice in the Description page of Project Settings.

#include "ArmorPickUp.h"


AArmorPickUp::AArmorPickUp()
{
	AmountValue = 50;
}


void AArmorPickUp::OnPlayerEnterPickUpBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnPlayerEnterPickUpBox(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (PlayerCharacter)
	{
		PlayerCharacter->AddArmor(AmountValue);
		Destroy();
	}
}

