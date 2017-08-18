// Fill out your copyright notice in the Description page of Project Settings.

#include "MyMainCharacter.h"
#include "uus.h"
#include "UsablePickUp.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


AMyMainCharacter::AMyMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxHealth = 100;
	PlayerHealth = MaxHealth;
	Damage = 10;
	DamageMultiplier = 1;
}

// Called when the game starts or when spawned
void AMyMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	TArray<UPaperSpriteComponent*> SpriteComps;
	GetComponents<UPaperSpriteComponent>(SpriteComps);

	for (int i = 0; i < SpriteComps.Num(); i++)
	{
		if (SpriteComps[i]->GetName() == "ShieldPaperSprite")
		{
			ShieldSprite = SpriteComps[i];
		}
	}
	if (ShieldSprite)
	{
		ShieldSprite->SetVisibility(false);
	}
}

// Called every frame
void AMyMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//SetActorRotation(GetAimDirection());
}

// Called to bind functionality to input
void AMyMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("UseItem", IE_Pressed, this, &AMyMainCharacter::UseItem);
}

FRotator AMyMainCharacter::GetAimDirection()
{
	// get mouse position
	float LocationX;
	float LocationY;
	PC->GetMousePosition(LocationX, LocationY);
	FVector MousePosition(LocationX, 0, LocationY);

	FVector PlayerPos = GetActorLocation();
	FVector2D PlayerOnScreen;
	UGameplayStatics::ProjectWorldToScreen(PC, PlayerPos, PlayerOnScreen);

	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	FVector ScreenCenter = FVector(ViewportSize.X / 2, 0, ViewportSize.Y / 2);

	FRotator TestRot;
	float Offset = 64; //ViewportSize.Y / 4;

	if (MousePosition.Z > PlayerOnScreen.Y + Offset)
	{
		AimingState = EAimingState::DownAngle;
		TestRot.Pitch = 315;
	}
	else if (MousePosition.Z < PlayerOnScreen.Y - Offset)
	{
		if (MousePosition.X < PlayerOnScreen.X + Offset && MousePosition.X > PlayerOnScreen.X - Offset)
		{
			AimingState = EAimingState::Up;
			TestRot.Pitch = 90;
		}
		else
		{
			AimingState = EAimingState::UpAngle;
			TestRot.Pitch = 45;
		}
	}
	else
	{
		AimingState = EAimingState::Forward;
		TestRot.Pitch = 0;
	}

	if (MousePosition.X < PlayerOnScreen.X)
	{
		SetActorRotation(FRotator(0, 180, 0));
	}
	else
	{
		SetActorRotation(FRotator(0, 0, 0));
	}

	//FVector Pos;
	//FVector Dir;
	//PC->DeprojectMousePositionToWorld(Pos, Dir);
	//FRotator TargetRotation = Dir.Rotation();
	// get player rotation to mouse

	//FRotator ShootRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetActorLocation() - MousePosition);

	FRotator NewRot(TestRot.Pitch, GetActorRotation().Yaw, GetActorRotation().Roll);

	return NewRot;
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
	while (Amount > 0 && PlayerHealth < 100)
	{
		Amount--;
		PlayerHealth++;
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
	if (ShieldSprite)
	{
		ShieldSprite->SetVisibility(true);
	}
}

void AMyMainCharacter::EndShield()
{
	Shield = 0;
	if (ShieldSprite)
	{
		ShieldSprite->SetVisibility(false);
	}
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
	PlayerHealth = MaxHealth;
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
	if (DamageMultiplier > 2)
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

void AMyMainCharacter::DamagePlayer(int32 DamageAmount)
{
	int32 DamageMitigated = FMath::RoundToInt(DamageAmount * DamageMitigation);
	int32 DamageToPlayer = DamageAmount - DamageMitigated;


	// check & damage shield

	while (Shield > 0 && DamageToPlayer > 0)
	{
		DamageToPlayer--;
		Shield--;
	}
	// check & damage armor
	while (Armor > 0 && DamageToPlayer > 0)
	{
		DamageToPlayer--;
		Armor--;
	}
	// damage player health
	if (DamageToPlayer > 0)
	{
		PlayerHealth -= DamageToPlayer;
	}

	//PlayerHealth -= DamageToPlayer;

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

