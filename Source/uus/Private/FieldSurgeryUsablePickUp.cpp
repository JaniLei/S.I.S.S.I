// Fill out your copyright notice in the Description page of Project Settings.

#include "FieldSurgeryUsablePickUp.h"


AFieldSurgeryUsablePickUp::AFieldSurgeryUsablePickUp()
{
	PickUpName = "Field Surgery";
}

void AFieldSurgeryUsablePickUp::UseItem()
{
	Super::UseItem();
	//int32 FullHealAmount = PlayerCharacter->GetMaxHealth() - PlayerCharacter->GetHealth();
	//PlayerCharacter->AddHealth(FullHealAmount);
	PlayerCharacter->FullHeal();
}

