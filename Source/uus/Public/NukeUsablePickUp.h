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

	ANukeUsablePickUp();


public:

	UFUNCTION(BlueprintNativeEvent)
	void ScreenFlash();

	virtual void UseItem() override;
	
};
