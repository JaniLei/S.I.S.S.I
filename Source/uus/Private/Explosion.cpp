// Fill out your copyright notice in the Description page of Project Settings.

#include "Explosion.h"
#include "MyMainCharacter.h"
#include "Barrier.h"
#include "uus.h"


// Sets default values
AExplosion::AExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//ExplosionRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ExplosionRoot"));
	//RootComponent = ExplosionRoot;

	//ExplosionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ExplosionBox"));
	//ExplosionBox->SetBoxExtent(FVector(20, 0, 20));
	//ExplosionBox->bGenerateOverlapEvents = true;
	//ExplosionBox->OnComponentBeginOverlap.AddDynamic(this, &AExplosion::OnPlayerEnterExplosionBox);

	//ExplosionSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("ExplosionSprite"));
}

// Called when the game starts or when spawned
void AExplosion::BeginPlay()
{
	Super::BeginPlay();

	TArray<UBoxComponent*> BoxComps;
	GetComponents<UBoxComponent>(BoxComps);
	ExplosionBox = BoxComps[0];

	ExplosionBox->OnComponentBeginOverlap.AddDynamic(this, &AExplosion::OnPlayerEnterExplosionBox);
}

// Called every frame
void AExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosion::OnPlayerEnterExplosionBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AMyMainCharacter* const TestPlayer = Cast <AMyMainCharacter>(OtherActor);
	ABarrier* const TestBarrier = Cast <ABarrier>(OtherActor);

	if (!Once)
	{
		if (TestPlayer && !Once)
		{
			TestPlayer->DamagePlayer(50);
		}
		else if (TestBarrier && !Once)
		{
			TestBarrier->DamageBarrier(50);
		}
		Once = true;
	}
}

