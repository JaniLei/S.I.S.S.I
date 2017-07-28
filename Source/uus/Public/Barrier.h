// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Barrier.generated.h"

UCLASS()
class UUS_API ABarrier : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarrier();


	UFUNCTION(BlueprintCallable)
	void DamageBarrier(int32 DamageAmount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USceneComponent* BarrierRoot;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BarrierBox;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite)
	int32 Health;

	
};
