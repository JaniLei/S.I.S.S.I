// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "uus.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemyBox"));
	EnemyBox->SetBoxExtent(FVector(40, 0, 40));
	EnemyBox->bGenerateOverlapEvents = true;
	EnemyBox->SetupAttachment(RootComponent);

	Health = 1;
	CanDropItems = true;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AMyMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (EnemyState != EEnemyState::Dead)
	{
		EnemyLocation = GetActorLocation();


		if (PlayerCharacter)
		{
			PlayerLocation = PlayerCharacter->GetActorLocation();
		}
	}
}

void AEnemy::DamageEnemy(int32 Amount)
{
	Health -= Amount;
	if (Health <= 0 && !IsPendingKill())
	{
		EnemyDeath();
	}
}

void AEnemy::EnemyDeath()
{
	// item drops / score
	if (CanDropItems && EnemyState != EEnemyState::Dead)
	{
		SpawnDrop();
	}
	EnemyState = EEnemyState::Dead;
	// destroy enemy
	/*if (!IsPendingKill())
	{
		Destroy();
	}*/
}

bool AEnemy::LookForPlayer()
{
	FVector DistanceVector = PlayerLocation - EnemyLocation;

	// if player is within "sight" range(400)
	if (DistanceVector.X < 500 && DistanceVector.X > -500 &&
		DistanceVector.Z < 500 && DistanceVector.Z > -500)
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

void AEnemy::SpawnDrop()
{
	if (DropTable.Num() > 0)
	{
		UClass* Drop = DropTable[0];

		if (DropTable.Num() > 1)
		{
			// randomly choosing index from droptable if more than 1 possible drop
			UClass* Drop = DropTable[FMath::RandRange(0, DropTable.Num() - 1)];
		}

		if (Drop)
		{
			FActorSpawnParameters SpawnParams;
			AActor* PickUpDrop = GetWorld()->SpawnActor<AActor>(Drop, GetActorTransform(), SpawnParams);
		}
	}
}

bool AEnemy::LineTraceToPlayer()
{
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);

	//call GetWorld() from within an actor extending class
	GetWorld()->LineTraceSingleByChannel(RV_Hit, EnemyLocation, PlayerLocation, ECC_Pawn, RV_TraceParams);

	if (RV_Hit.bBlockingHit)
	{
		if (RV_Hit.GetActor()->IsA(AMyMainCharacter::StaticClass()))
		{
			AMyMainCharacter* HitPlayer = Cast<AMyMainCharacter>(RV_Hit.GetActor());
			if (HitPlayer)
			{
				return true;
			}
		}
	}
	return false;
}
