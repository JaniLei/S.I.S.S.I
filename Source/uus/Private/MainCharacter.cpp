// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"
#include "uus.h"
#include "UsablePickUp.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 2;
	Damage = 1;
	DamageMultiplier = 1;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("UseItem", IE_Pressed, this, &AMainCharacter::UseItem);
}

void AMainCharacter::AddAmmo(int32 Amount)
{
	Ammo += Amount;
}

void AMainCharacter::AddHealth(int32 Amount)
{
	while (Amount > 0 && Health < 100)
	{
		Amount--;
		Health++;
	}
}

void AMainCharacter::AddArmor(int32 Amount)
{
	while (Amount > 0 && Armor < 100)
	{
		Amount--;
		Armor++;
	}
}

void AMainCharacter::AddDamageMitigation(float Amount)
{
	DamageMitigation += Amount;
	if (DamageMitigation > 0.2f)
	{
		DamageMitigation = 0.2f;
	}
}

void AMainCharacter::AddDamageMultiplier(float Amount)
{
	DamageMultiplier += Amount;
	if (DamageMultiplier < 2)
	{
		DamageMultiplier = 2;
	}
}

void AMainCharacter::AddUsableItem(AUsablePickUp* Item)
{
	UsableItem = Item;
}

void AMainCharacter::UseItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("USING ITEM"));
	if (UsableItem)
	{
		if (!UsableItem->IsUsed)
		{
			UsableItem->UseItem();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ITEM USED"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NO ITEM"));
	}
}

void AMainCharacter::DamagePlayer(int32 DamageAmount)
{
	int32 DamageMitigated = FMath::RoundToInt(DamageAmount * DamageMitigation);

	Health -= (DamageAmount - DamageMitigated);

	if (Health <= 0)
	{
		PlayerDeath();
	}
}

void AMainCharacter::PlayerDeath()
{
	if (!IsPendingKill())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PLAYER DEAD!"));
		//Destroy();
	}
}
