// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyMainCharacter.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "uus.h"
#include "Enemy.generated.h"


UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle 		UMETA(DisplayName = "Idle"),
	Moving 		UMETA(DisplayName = "Moving"),
	Attacking	UMETA(DisplayName = "Attacking"),
	Dead		UMETA(DisplayName = "Dead"),
};

UCLASS()
class UUS_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/** Damage enemy by the amount. Trigger death if health reaches 0 or below*/
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	virtual void DamageEnemy(int32 Amount);

	virtual void EnemyDeath();

protected:

	//UPROPERTY(EditAnywhere)
	//USceneComponent* EnemyRoot;

	UPROPERTY(EditAnywhere)
	UBoxComponent* EnemyBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EEnemyState EnemyState;


	FVector EnemyLocation;
	FVector PlayerLocation;

	AMyMainCharacter* PlayerCharacter;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite)
	int32 Health;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite)
	int32 Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool PlayerFound;

	UPROPERTY(EditAnywhere, Category = "ItemDrops")
	bool CanDropItems;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "ItemDrops")
	TArray<TSubclassOf <AActor>> DropTable;


	bool LookForPlayer();

	void SpawnDrop();

	UFUNCTION(BlueprintCallable)
	bool LineTraceToPlayer();

};

