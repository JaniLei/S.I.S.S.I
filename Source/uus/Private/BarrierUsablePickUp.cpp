// Fill out your copyright notice in the Description page of Project Settings.

#include "BarrierUsablePickUp.h"
#include "Engine.h"


ABarrierUsablePickUp::ABarrierUsablePickUp()
{
	PickUpName = "Barrier";
}

void ABarrierUsablePickUp::UseItem()
{
	Super::UseItem();

	FActorSpawnParameters SpawnParams;
	FTransform BarrierTransform = PlayerCharacter->GetActorTransform();

	if (PlayerCharacter->GetActorRotation().Yaw < 0)
	{
		OffsetX = -100;
	}
	else
	{
		OffsetX = 100;
	}
	BarrierTransform.SetLocation(FVector(BarrierTransform.GetLocation().X + OffsetX, 0, BarrierTransform.GetLocation().Z /*+ 25*/));
	ABarrier* SpawnedBarrier = GetWorld()->SpawnActor<ABarrier>(BarrierBP, BarrierTransform, SpawnParams);
}