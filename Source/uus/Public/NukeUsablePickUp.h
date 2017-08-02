// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsablePickUp.h"
#include "NukeUsablePickUp.generated.h"

/**
 * 
 */
UCLASS()
class UUS_API ANukeUsablePickUp : public AUsablePickUp
{
	GENERATED_BODY()


public:

	virtual void UseItem() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprite")
	UPaperFlipbookComponent* NukeFlash;

protected:

	/** nuke object to spawn when this item is used*/
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> NukeBP;
	
	
};
