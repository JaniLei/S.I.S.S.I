// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsablePickUp.h"
#include "Explosion.h"
#include "NukeUsablePickUp.generated.h"

/**
 * 
 */
UCLASS()
class UUS_API ANukeUsablePickUp : public AUsablePickUp
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintNativeEvent)
	void ShakeScreen();

	virtual void UseItem() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprite")
	UPaperFlipbookComponent* NukeFlash;
	
};
