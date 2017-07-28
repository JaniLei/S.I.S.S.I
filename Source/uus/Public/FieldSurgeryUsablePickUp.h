// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsablePickUp.h"
#include "FieldSurgeryUsablePickUp.generated.h"

/**
 * 
 */
UCLASS()
class UUS_API AFieldSurgeryUsablePickUp : public AUsablePickUp
{
	GENERATED_BODY()

	AFieldSurgeryUsablePickUp();
	
public:

	virtual void UseItem() override;
	
	
};
