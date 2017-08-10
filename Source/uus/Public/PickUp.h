// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "uus.h"
#include "GameFramework/Actor.h"
#include "MyMainCharacter.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "PickUp.generated.h"


UCLASS()
class UUS_API APickUp : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickUp();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* PickUpBox;

protected:

	/** The amount of ammo/health/etc the pickup gives*/
	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "PickUp")
	int32 AmountValue;

	float RunningTime;

	FVector FloatingLocation;

	AMyMainCharacter* PlayerCharacter;

	UFUNCTION()
	virtual void OnPlayerEnterPickUpBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};

