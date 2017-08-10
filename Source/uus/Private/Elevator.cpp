// Fill out your copyright notice in the Description page of Project Settings.

#include "Elevator.h"
#include "Components/BoxComponent.h"


AElevator::AElevator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 100;
	Distance = 400;
}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();

	TArray<UPaperSpriteComponent*> SpriteComps;
	GetComponents<UPaperSpriteComponent>(SpriteComps);

	for (int i = 0; i < SpriteComps.Num(); i++) 
	{
		if (SpriteComps[i]->GetName() == "PlatformSprite")
		{
			PlatformSprite = SpriteComps[i];
		}
	}

	LowPosition = PlatformSprite->GetComponentLocation();

	HighPosition = LowPosition;
	HighPosition.Z += Distance;

	NewPosition = LowPosition;

	IsDown = true;

}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsActivated)
	{
		MoveElevator(DeltaTime);
	}

}

void AElevator::ActivateElevator()
{
	IsActivated = true;
}

void AElevator::MoveElevator(float DeltaTime)
{
	if (IsDown)
	{
		if (NewPosition.Z < HighPosition.Z)
		{
			NewPosition.Z += (Speed * DeltaTime);
			//SetActorLocation(newPosition);
			PlatformSprite->SetWorldLocation(NewPosition);
		}
		else
		{
			IsActivated = false;
			IsDown = false;
		}
	}
	else
	{
		if (NewPosition.Z > LowPosition.Z)
		{
			NewPosition.Z -= (Speed * DeltaTime);
			//SetActorLocation(newPosition);
			PlatformSprite->SetWorldLocation(NewPosition);
		}
		else
		{
			IsActivated = false;
			IsDown = true;
		}
	}
}

