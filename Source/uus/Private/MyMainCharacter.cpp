// Fill out your copyright notice in the Description page of Project Settings.

#include "MyMainCharacter.h"
#include "uus.h"
#include "UsablePickUp.h"


AMyMainCharacter::AMyMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShieldSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ShieldSprite"));

	MaxHealth = 100;
	Health = MaxHealth;
	Damage = 1;
	DamageMultiplier = 1;
}

// Called when the game starts or when spawned
void AMyMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	ShieldSprite->SetVisibility(false);
}

// Called every frame
void AMyMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("UseItem", IE_Pressed, this, &AMyMainCharacter::UseItem);
}

void AMyMainCharacter::AddAmmo(int32 Amount)
{
	if (HasExtraAmmo)
	{
		Ammo += Amount * 2;
	}
	else
	{
		Ammo += Amount;
	}
}

void AMyMainCharacter::AddHealth(int32 Amount)
{
	while (Amount > 0 && Health < 100)
	{
		Amount--;
		Health++;
	}
}

void AMyMainCharacter::AddArmor(int32 Amount)
{
	while (Amount > 0 && Armor < 200)
	{
		Amount--;
		Armor++;
	}
}

void AMyMainCharacter::AddShield(int32 Amount)
{
	Shield = Amount;
	GetWorldTimerManager().SetTimer(ShieldTimerHandle, this, &AMyMainCharacter::EndShield, 30, false);
	ShieldSprite->SetVisibility(true);
}

void AMyMainCharacter::EndShield()
{
	Shield = 0;
	ShieldSprite->SetVisibility(false);
}

void AMyMainCharacter::ActivateDoubleDamage_Implementation()
{
	DoubleDamageActive = true;
	GetWorldTimerManager().SetTimer(DoubleDamageTimerHandle, this, &AMyMainCharacter::EndDoubleDamage, 10, false);
}

void AMyMainCharacter::EndDoubleDamage_Implementation()
{
	DoubleDamageActive = false;
}

void AMyMainCharacter::FullHeal_Implementation()
{
	Health = MaxHealth;
}

void AMyMainCharacter::AddDamageMitigation(float Amount)
{
	DamageMitigation += Amount;
	if (DamageMitigation > 0.2f)
	{
		DamageMitigation = 0.2f;
	}
}

void AMyMainCharacter::AddDamageMultiplier(float Amount)
{
	DamageMultiplier += Amount;
	if (DamageMultiplier < 2)
	{
		DamageMultiplier = 2;
	}
}

void AMyMainCharacter::AddExtraShot()
{
	HasExtraShot = true;
}

void AMyMainCharacter::AddQuickFire()
{
	HasQuickFire = true;
}

void AMyMainCharacter::AddExtraAmmo()
{
	HasExtraAmmo = true;
}

void AMyMainCharacter::AddUsableItem(AUsablePickUp* Item)
{
	UsableItem = Item;
}

void AMyMainCharacter::UseItem()
{
	if (UsableItem)
	{
		if (!UsableItem->IsUsed)
		{
			UsableItem->UseItem();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ITEM USED"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ITEM ALREADY USED"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NO ITEM"));
	}
}

int32 AMyMainCharacter::DamagePlayer(int32 DamageAmount)
{
	int32 DamageMitigated = FMath::RoundToInt(DamageAmount / (1 - DamageMitigation));
	int32 DamageToPlayer = DamageAmount - DamageMitigated;

	return DamageToPlayer;

	// check & damage shield
	/*while (Shield > 0 || DamageToPlayer > 0)
	{
		DamageToPlayer--;
		Shield--;
	}
	// check & damage armor
	while (Armor > 0 || DamageToPlayer > 0)
	{
		DamageToPlayer--;
		Armor--;
	}
	// damage player health
	if (DamageToPlayer > 0)
	{
		Health -= DamageToPlayer;
	}
	// check for death
	if (Health <= 0)
	{
		PlayerDeath();
	}*/
}

void AMyMainCharacter::PlayerDeath()
{
	if (!IsPendingKill())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PLAYER DEAD!"));
		//Destroy();
	}
}

int32 AMyMainCharacter::GetScaledPlayerDamage()
{
	int32 PlayerDamage = Damage * DamageMultiplier;
	if (DoubleDamageActive)
	{
		PlayerDamage *= 2;
	}
	return PlayerDamage;
}

