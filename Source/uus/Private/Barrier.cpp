// Fill out your copyright notice in the Description page of Project Settings.

#include "Barrier.h"
#include "uus.h"


// Sets default values
ABarrier::ABarrier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BarrierRoot = CreateDefaultSubobject<USceneComponent>(TEXT("BarrierRoot"));
	RootComponent = BarrierRoot;

	BarrierBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BarrierBox"));
	BarrierBox->SetBoxExtent(FVector(40, 0, 40));
	BarrierBox->bGenerateOverlapEvents = true;


	Health = 500;
}

// Called when the game starts or when spawned
void ABarrier::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABarrier::DamageBarrier(int32 DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0 && !IsPendingKill())
	{
		Destroy();
	}
}
