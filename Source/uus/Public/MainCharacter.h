// OLD VERSION of main character (new -> "MyMainCharacter")

#pragma once

#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class AUsablePickUp;

UCLASS()
class UUS_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AUsablePickUp* UsableItem;

	UPROPERTY(EditAnywhere)
	int32 Ammo;
	UPROPERTY(EditAnywhere)
	int32 Health;
	int32 MaxHealth;
	UPROPERTY(EditAnywhere)
	int32 Armor;
	
	float Damage;

	/** reduced damage taken*/
	float DamageMitigation;
	/** increases damage dealt*/
	float DamageMultiplier;

	UFUNCTION(BlueprintCallable)
	void UseItem();

public:

	// Sets default values for this character's properties
	AMainCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool DoubleDamageActive;
	bool BarrierActive;

	void AddAmmo(int32 Amount);
	void AddHealth(int32 Amount);
	void AddArmor(int32 Amount);
	void AddDamageMitigation(float Amount);
	void AddDamageMultiplier(float Amount);
	void AddUsableItem(AUsablePickUp* Item);


	UFUNCTION(BlueprintCallable)
	void DamagePlayer(int32 DamageAmount);

	void PlayerDeath();

	UFUNCTION(BlueprintCallable)
	float GetDamageMitigation() { return DamageMitigation; }


	UFUNCTION(BlueprintCallable)
	int32 GetHealth() { return Health; }
	UFUNCTION(BlueprintCallable)
	int32 GetMaxHealth() { return MaxHealth; }
	
};
