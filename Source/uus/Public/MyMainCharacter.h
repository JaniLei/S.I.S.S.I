// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperSpriteComponent.h"
#include "MyMainCharacter.generated.h"

class AUsablePickUp;


UENUM(BlueprintType)
enum class EAimingState : uint8
{
	Forward 	UMETA(DisplayName = "Forward"),
	Up			UMETA(DisplayName = "Up"),
	UpAngle		UMETA(DisplayName = "UpAngle"),
	DownAngle 	UMETA(DisplayName = "DownAngle")
};

/**
 * 
 */
UCLASS()
class UUS_API AMyMainCharacter : public APaperCharacter
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* ShieldSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AUsablePickUp* UsableItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EAimingState AimingState;

	APlayerController* PC;

	FTimerHandle ShieldTimerHandle;
	FTimerHandle DoubleDamageTimerHandle;

	FString PickUpName;

	UPROPERTY(EditAnywhere)
	int32 Ammo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerHealth;
	int32 MaxHealth;
	UPROPERTY(EditAnywhere)
	int32 Armor;
	UPROPERTY(EditAnywhere)
	int32 Shield;
	UPROPERTY(EditAnywhere)
	int32 Damage;

	/** reduced damage taken*/
	float DamageMitigation;
	/** increases damage dealt*/
	float DamageMultiplier;

	UFUNCTION(BlueprintCallable)
	void UseItem();
	/** Get rotation from player towards mouse*/
	UFUNCTION(BlueprintCallable)
	FRotator GetAimDirection();

public:

	// Sets default values for this character's properties
	AMyMainCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool HasExtraAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DoubleDamageActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasExtraShot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasQuickFire;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsBeingBitten;

	void AddAmmo(int32 Amount);
	void AddHealth(int32 Amount);
	void AddArmor(int32 Amount);
	void AddShield(int32 Amount);
	void EndShield();
	UFUNCTION(BlueprintNativeEvent)
	void ActivateDoubleDamage();
	UFUNCTION(BlueprintNativeEvent)
	void EndDoubleDamage();
	UFUNCTION(BlueprintNativeEvent)
	void FullHeal();
	void AddDamageMitigation(float Amount);
	void AddDamageMultiplier(float Amount);
	void AddExtraShot();
	void AddQuickFire();
	void AddExtraAmmo();
	void AddUsableItem(AUsablePickUp* Item);

	UFUNCTION(BlueprintCallable)
	float DamagePlayer(float DamageAmount);

	void PlayerDeath();

	float GetDamageMultiplier() { return DamageMultiplier; }
	float GetDamageMitigation() { return DamageMitigation; }

	/** Returns player's damage with powerups*/
	UFUNCTION(BlueprintCallable)
	int32 GetScaledPlayerDamage();

	UFUNCTION(BlueprintCallable)
	int32 GetMaxHealth() { return MaxHealth; }
	
};
