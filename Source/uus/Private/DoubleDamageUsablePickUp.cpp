// Fill out your copyright notice in the Description page of Project Settings.

#include "DoubleDamageUsablePickUp.h"


ADoubleDamageUsablePickUp::ADoubleDamageUsablePickUp()
{
	PickUpName = "Double Damage";
}

void ADoubleDamageUsablePickUp::UseItem()
{
	Super::UseItem();

	PlayerCharacter->ActivateDoubleDamage();
}
