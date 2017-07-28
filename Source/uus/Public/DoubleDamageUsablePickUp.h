// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsablePickUp.h"
#include "DoubleDamageUsablePickUp.generated.h"

/**
 * 
 */
UCLASS()
class UUS_API ADoubleDamageUsablePickUp : public AUsablePickUp
{
	GENERATED_BODY()

	ADoubleDamageUsablePickUp();

public:

	virtual void UseItem() override;
	
};
