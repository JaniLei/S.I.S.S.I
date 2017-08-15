// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyMainCharacter.h"
#include "GroundEnemySpawner.generated.h"

UCLASS()
class UUS_API AGroundEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGroundEnemySpawner();

	UFUNCTION(BlueprintCallable)
	bool CheckEnemiesOnScreen(int32 EnemyAmount);
	
	UFUNCTION(BlueprintCallable)
	bool LookForPlayer();

protected:

	AMyMainCharacter* PlayerCharacter;

};
