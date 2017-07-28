// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Elevator.generated.h"

UCLASS()
class UUS_API AElevator : public AActor
{
	GENERATED_BODY()

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	//class USceneComponent* ElevatorRoot;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	//class UBoxComponent* TriggerBox;


public:
	// Sets default values for this actor's properties
	AElevator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	bool IsActivated;
	bool IsDown;

	/** The distance which the elevator travels vertically*/
	UPROPERTY(EditAnyWhere, Category = "Elevator Variables")
	float Distance;

	/** The travel speed of the elevator*/
	UPROPERTY(EditAnyWhere, Category = "Elevator Variables")
	float Speed;

	FVector LowPosition;
	FVector NewPosition;
	FVector HighPosition;

protected:

	void MoveElevator(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Elevator")
	void ActivateElevator();

	// CHANGE TO PAPER SPRITE COMP (Elevator platform)
	UPaperSpriteComponent* PlatformSprite;
	
};
