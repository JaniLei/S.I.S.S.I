// Fill out your copyright notice in the Description page of Project Settings.

#include "GreenBug.h"
#include "Kismet/KismetMathLibrary.h"


AGreenBug::AGreenBug()
{
	AttackBox->SetBoxExtent(FVector(200, 0, 200));

	Health = 20;
	//CanDropItems = *;
	Damage = 20;
	Speed = 3;
	AttackInterval = 1.15f;
	MovementInterval = 5;
}

void AGreenBug::BeginPlay()
{
	Super::BeginPlay();
}

void AGreenBug::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EnemyState != EEnemyState::Dead)
	{
		if (PlayerFound)
		{
			if (!GetWorldTimerManager().IsTimerActive(MovementBehaviourTimerHandle))
			{

				GetWorldTimerManager().SetTimer(MovementBehaviourTimerHandle, this, &AGreenBug::ChangeMovementBehaviour, MovementInterval, false, MovementInterval);
			}
		}
	}
}

void AGreenBug::Attack()
{
	Super::Attack();

	// turn towards player
	if (PlayerLocation.X > EnemyLocation.X)
	{
		//SetActorScale3D(FVector(-1, 1, 1));
		SetActorRotation(FRotator(0, 180, 0));
	}
	else if (PlayerLocation.X < EnemyLocation.X)
	{
		//SetActorScale3D(FVector(1, 1, 1));
		SetActorRotation(FRotator(0, 0, 0));
	}
	// spawn projectile towards player
	if (ProjectileBP)
	{
		FActorSpawnParameters SpawnParams;
		// set spawned projectiles location position and rotation towards player
		FTransform SpawnTransform;
		FRotator NewRot;
		if (IsBat)
		{
			FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerLocation);
			PlayerRot.Pitch = FMath::ClampAngle(PlayerRot.Pitch, 300.f, 340.f);
			NewRot = FRotator(PlayerRot.Pitch, GetActorRotation().Yaw + 180, 0);
		}
		else
		{
			NewRot = FRotator(320, GetActorRotation().Yaw + 180, 0);
		}
		SpawnTransform.SetLocation(GetActorLocation());
		SpawnTransform.SetRotation(NewRot.Quaternion());
		AActor* ProjectileActor = GetWorld()->SpawnActor<AActor>(ProjectileBP, SpawnTransform, SpawnParams);

		//AttackInterval = FMath::FRandRange(1, 2);
	}
}

void AGreenBug::ChangeMovementBehaviour()
{
	if (EnemyState == EEnemyState::Moving)
	{
		EnemyState = EEnemyState::Idle;
	}
	else if (EnemyState == EEnemyState::Idle)
	{
		EnemyState = EEnemyState::Moving;
	}
}
