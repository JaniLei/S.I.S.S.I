// Fill out your copyright notice in the Description page of Project Settings.

#include "ShieldUsablePickUp.h"


AShieldUsablePickUp::AShieldUsablePickUp()
{
	PickUpName = "Shield";
}

void AShieldUsablePickUp::UseItem()
{
	Super::UseItem();

	PlayerCharacter->AddShield(ShieldAmount);
}
