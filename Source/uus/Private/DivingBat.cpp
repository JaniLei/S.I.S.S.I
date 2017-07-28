// Fill out your copyright notice in the Description page of Project Settings.

#include "DivingBat.h"
#include "Kismet/KismetMathLibrary.h"


ADivingBat::ADivingBat()
{
	AttackBox->SetBoxExtent(FVector(200, 0, 200));

	//EnemyBox->bGenerateOverlapEvents = true;
	EnemyBox->OnComponentBeginOverlap.AddDynamic(this, &ADivingBat::OnPlayerEnterBitingBox);

	Health = 10;
	//CanDropItems = *;
	Damage = 50;
	Speed = 3;
	AttackInterval = 3;
	ChangePositionInterval = 3.1f;

	InterpSpeed = 0;
}

void ADivingBat::BeginPlay()
{
	Super::BeginPlay();
}

void ADivingBat::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (EnemyState != EEnemyState::Dead)
	{
		if (IsDiving && !IsBiting)
		{
			DiveAtPlayer(DeltaTime);
		}
	}
}

void ADivingBat::OnPlayerEnterBitingBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (EnemyState != EEnemyState::Dead)
	{
		AMyMainCharacter* const TestPlayer = Cast <AMyMainCharacter>(OtherActor);

		if (TestPlayer && !BiteCooldown)
		{
			IsBiting = true;
			GetWorldTimerManager().SetTimer(BitingTimerHandle, this, &ADivingBat::EndBiting, 1, false);
			PlayerCharacter->IsBeingBitten = true;
		}
	}
}

void ADivingBat::CheckDirection()
{
	if (!IsDiving)
	{
		Super::CheckDirection();
	}
}

void ADivingBat::Movement(float DeltaTime)
{
	if (PlayerFound && !IsDiving)
	{
		if (!GetWorldTimerManager().IsTimerActive(BehaviourTimerHandle))
		{
			GetWorldTimerManager().SetTimer(BehaviourTimerHandle, this, &ADivingBat::ChooseNewRandomPos, ChangePositionInterval, true, 1);
		}

		FVector EnemyDirection = NewDirection - EnemyLocation;
		EnemyDirection.Normalize();
		EnemyDirection.X *= Speed;
		EnemyDirection.Z *= Speed;


		MovementVector = EnemyLocation + EnemyDirection;

		if (EnemyLocation.X < NewDirection.X - 4 || EnemyLocation.X > NewDirection.X + 4)
		{
			SetActorLocation(MovementVector);
		}
	}
}

void ADivingBat::Attack()
{
	float VDistanceToPlayer = EnemyLocation.X - PlayerLocation.X;

	if (VDistanceToPlayer < -60 || VDistanceToPlayer > 60)
	{
		if (!IsDiving)
		{
			GetWorldTimerManager().ClearTimer(BehaviourTimerHandle);

			StartPos = GetActorLocation();
			AttackTarget = PlayerCharacter->GetActorLocation();

			if (AttackTarget.X > EnemyLocation.X)
			{
				ToLeft = true;
				SetActorRotation(FRotator(0, 180, 0));
			}
			else
			{
				ToLeft = false;
				SetActorRotation(FRotator(0, 0, 0));
			}

			StartX = EnemyLocation.X;
			StartZ = EnemyLocation.Z;
			EndX = EnemyLocation.X + ((AttackTarget.X - EnemyLocation.X) * 2);
			//EndZ = (EnemyLocation.Z + ((AttackTarget.Z - EnemyLocation.Z) * 2)) + 50;
			EndZ = EnemyLocation.Z + (AttackTarget.Z - EnemyLocation.Z);
			//MiddleZ = EnemyLocation.Z + ((AttackTarget.Z - EnemyLocation.Z) * 2);
			EndPosition = FVector(EndX, 0, EndZ);

			IsDiving = true;

			TestX = StartX;
		}
	}
}

void ADivingBat::DiveAtPlayer(float DeltaTime)
{
	// reset bite hitbox overlaps
	EnemyBox->bGenerateOverlapEvents = false;

	if (ToLeft)
	{
		if (EnemyLocation.X < EndX)
		{
			float VDistance = EndX - StartX;
			
			//FVector DiveDirection = EndPosition - EnemyLocation;
			//DiveDirection.Normalize();
			//
			//DiveDirection.X *= 2;
			//DiveDirection.Z *= 2;
			//DiveDirection.X *= Speed;
			//DiveDirection.Z *= Speed;
			if (EnemyLocation.X - StartX >= VDistance / 2)
			{
				//EndPosition.Z = StartZ;
				EndPosition.Z += 675 / VDistance;
				EndPosition.Z = FMath::Clamp(EndPosition.Z, EndZ, StartZ);
				EnemyBox->bGenerateOverlapEvents = true;
			}

			if (EnemyLocation.X - StartX > VDistance / 1.01f)
			{
				IsTurning = true;
			}

			EndPosition.X = TestX;
			TestX += 0.008 * VDistance;
			TestX = FMath::Clamp(TestX, StartX, EndX);

			InterpSpeed += 0.03;
			//InterpSpeed = FMath::Clamp(InterpSpeed, 0.001f, 0.999f);
			FVector DiveDirection = FMath::VInterpTo(EnemyLocation, EndPosition, DeltaTime * 5, InterpSpeed);

			MovementVector = /*EnemyLocation +*/ DiveDirection;
		}
		else
		{
			IsDiving = false;
			IsTurning = false;
			InterpSpeed = 0;
		}
	}
	else
	{
		if (EnemyLocation.X > EndX)
		{
			float VDistance = StartX - EndX;

			//FVector DiveDirection = EndPosition - EnemyLocation;
			//DiveDirection.Normalize();
			//
			//DiveDirection.X *= 2;
			//DiveDirection.Z *= 2;
			//DiveDirection.X *= Speed;
			//DiveDirection.Z *= Speed;
			if (StartX - EnemyLocation.X >= VDistance / 2)
			{
				//EndPosition.Z = StartZ;
				EndPosition.Z += 675 / VDistance;
				EndPosition.Z = FMath::Clamp(EndPosition.Z, EndZ, StartZ);
				EnemyBox->bGenerateOverlapEvents = true;
			}

			if (StartX - EnemyLocation.X > VDistance / 1.01f)
			{
				IsTurning = true;
			}

			EndPosition.X = TestX;
			TestX -= 0.008 * VDistance;
			TestX = FMath::Clamp(TestX, EndX, StartX);

			InterpSpeed += 0.03;
			//InterpSpeed = FMath::Clamp(InterpSpeed, 0.001f, 0.999f);
			FVector DiveDirection = FMath::VInterpTo(EnemyLocation, EndPosition, DeltaTime * 5, InterpSpeed);

			MovementVector = /*EnemyLocation +*/ DiveDirection;
		}
		else
		{
			IsDiving = false;
			IsTurning = false;
			InterpSpeed = 0;
		}
	}

	SetActorLocation(MovementVector);
}

void ADivingBat::ChooseNewRandomPos()
{
	FVector NewRandomPos = FVector(FMath::FRandRange(PlayerLocation.X - 225, PlayerLocation.X + 225), 0, FMath::FRandRange(PlayerLocation.Z + 100, PlayerLocation.Z + 180));
	NewDirection = NewRandomPos;
}

void ADivingBat::EndBiting()
{
	BiteCooldown = true;
	GetWorldTimerManager().SetTimer(BiteCooldownTimerHandle, this, &ADivingBat::RefreshBiteCooldown, AttackInterval / 2, false);
	IsBiting = false;
	PlayerCharacter->IsBeingBitten = false;
	PlayerCharacter->DamagePlayer(Damage);
	// test
	IsDiving = false;
	InterpSpeed = 0;
}

void ADivingBat::RefreshBiteCooldown()
{
	BiteCooldown = false;
}
