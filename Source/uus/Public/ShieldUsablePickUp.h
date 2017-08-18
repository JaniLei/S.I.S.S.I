// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsablePickUp.h"
#include "PaperSpriteComponent.h"
#include "ShieldUsablePickUp.generated.h"

/**
 * 
 */
UCLASS()
class UUS_API AShieldUsablePickUp : public AUsablePickUp
{
	GENERATED_BODY()

	AShieldUsablePickUp();
	
public:

	virtual void UseItem() override;
	
protected:

	int32 ShieldAmount;

};
