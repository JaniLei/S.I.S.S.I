// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUp.h"
#include "uus.h"


// Sets default values
APickUp::APickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//PickUpRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickUpRoot"));
	//RootComponent = PickUpRoot;

	//PickUpBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PickUpBox"));
	//PickUpBox->SetBoxExtent(FVector(30, 0, 30));
	//PickUpBox->bGenerateOverlapEvents = true;
	//PickUpBox->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnPlayerEnterPickUpBox);
	//PickUpBox->SetupAttachment(RootComponent);

	//PickUpSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PickUpSprite"));

	AmountValue = 1;
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();

	TArray<UBoxComponent*> BoxComps;
	GetComponents<UBoxComponent>(BoxComps);
	PickUpBox = BoxComps[0];

	PickUpBox->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnPlayerEnterPickUpBox);

	// pickup will despawn after 10 seconds if not picked up
	SetLifeSpan(10);
	// set location behind objects
	FVector Location = GetActorLocation();
	Location.Y--;
	SetActorLocation(Location);
}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// floating height
	float DeltaHeight = (FMath::Sin((RunningTime + DeltaTime) * 2) - FMath::Sin(RunningTime * 2));
	FloatingLocation.Z += DeltaHeight * 0.2f;
	RunningTime += DeltaTime;

	SetActorLocation(GetActorLocation() + FloatingLocation);
}

void APickUp::OnPlayerEnterPickUpBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AMyMainCharacter* const TestPlayer = Cast <AMyMainCharacter>(OtherActor);
	
	if (TestPlayer)
	{
		PlayerCharacter = TestPlayer;
	}
}
