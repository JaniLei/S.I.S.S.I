// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "PaperFlipbookComponent.h"
#include "Explosion.generated.h"

UCLASS()
class UUS_API AExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosion();


	UPROPERTY(EditAnywhere)
	USceneComponent* ExplosionRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* ExplosionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprite")
	UPaperFlipbookComponent* ExplosionSprite;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** can only damage once*/
	bool Once;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPlayerEnterExplosionBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
