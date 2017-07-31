// Fill out your copyright notice in the Description page of Project Settings.

#include "FlyingEnemy.h"
#include "uus.h"
#include "Kismet/KismetMathLibrary.h"


AFlyingEnemy::AFlyingEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackBox"));
	AttackBox->bGenerateOverlapEvents = true;
	AttackBox->OnComponentBeginOverlap.AddDynamic(this, &AFlyingEnemy::OnPlayerEnterAttackBox);
	AttackBox->OnComponentEndOverlap.AddDynamic(this, &AFlyingEnemy::OnPlayerExitAttackBox);
	AttackBox->SetupAttachment(RootComponent);

	// Set values in children
	//Health = *;
	//CanDropItems = *;
	Damage = 1;
	AttackInterval = 1;

}

// Called when the game starts or when spawned
void AFlyingEnemy::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AFlyingEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EnemyState != EEnemyState::Dead)
	{

		CheckDirection();

		if (PlayerCharacter)
		{

			if (!IsHit)
			{
				PlayerFound = LookForPlayer();
			}
		}

		Movement(DeltaTime);

		if (EnemyState == EEnemyState::Attacking)
		{
			if (!GetWorldTimerManager().IsTimerActive(AttackTimerHandle))
			{
				IsShooting = true;
				GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AFlyingEnemy::Attack, AttackInterval, false, AttackInterval);
			}
		}
	}
}

void AFlyingEnemy::Movement(float DeltaTime)
{
	if (EnemyState == EEnemyState::Moving && PlayerFound && LineTraceToPlayer())
	{
		FVector PlayerDirection = FVector(PlayerLocation.X, 0, PlayerLocation.Z + 180) - EnemyLocation;
		PlayerDirection.Normalize();
		PlayerDirection.X *= Speed;
		PlayerDirection.Z *= Speed;

		MovementVector = EnemyLocation + PlayerDirection;

		//MovementVector = FMath::Lerp(EnemyLocation, FVector(PlayerLocation.X, 0, PlayerLocation.Z + 150), 0.015f);

		SetActorLocation(MovementVector);

		// floating height
		float DeltaHeight = (FMath::Sin((RunningTime + DeltaTime) * 3) - FMath::Sin((RunningTime) * 3));
		FloatingLocation.Z += DeltaHeight * 0.4f;
		RunningTime += DeltaTime;
		
		SetActorLocation(GetActorLocation() + FloatingLocation);
	}
}

void AFlyingEnemy::CheckDirection()
{
	// Check the moving direction based on last frame position and current position and rotate object accordingly
	
	if (EnemyLocation.X > LastLocation.X)
	{
		//SetActorScale3D(FVector(-1, 1, 1));
		SetActorRotation(FRotator(0, 180, 0));
	}
	else if (EnemyLocation.X < LastLocation.X)
	{
		//SetActorScale3D(FVector(1, 1, 1));
		SetActorRotation(FRotator(0, 0, 0));
	}
	LastLocation = EnemyLocation;
}

bool AFlyingEnemy::LookForPlayer()
{
	FVector DistanceVector = PlayerLocation - EnemyLocation;

	// if player is within "sight" range(400)
	if (DistanceVector.X < 400 && DistanceVector.X > -400 &&
		DistanceVector.Z < 400 && DistanceVector.Z > -400)
	{
		if (EnemyState == EEnemyState::Idle)
		{
			EnemyState = EEnemyState::Moving;
		}
		return true;
	}
	else
	{
		EnemyState = EEnemyState::Idle;
		return false;
	}
}

void AFlyingEnemy::OnPlayerEnterAttackBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (EnemyState != EEnemyState::Dead)
	{
		AMyMainCharacter* const TestPlayer = Cast <AMyMainCharacter>(OtherActor);

		if (TestPlayer)
		{
			EnemyState = EEnemyState::Attacking;
		}
	}
}

void AFlyingEnemy::OnPlayerExitAttackBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (EnemyState != EEnemyState::Dead)
	{
		AMyMainCharacter* const TestPlayer = Cast <AMyMainCharacter>(OtherActor);

		if (TestPlayer)
		{
			IsShooting = false;
			EnemyState = EEnemyState::Moving;
			GetWorldTimerManager().ClearTimer(AttackTimerHandle);
		}
	}
}

void AFlyingEnemy::Attack()
{
	//if (IsShooting)
	//{
	//	IsShooting = false;
	//}
	//IsShooting = true;
}

void AFlyingEnemy::DamageEnemy(int32 Damage)
{
	IsHit = true;
	PlayerFound = true;
	Super::DamageEnemy(Damage);
}
