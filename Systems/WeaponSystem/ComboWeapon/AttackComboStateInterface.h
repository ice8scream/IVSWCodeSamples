// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackComboStateInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAttackComboStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IVSW_API IAttackComboStateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 GetComboState();
	void IncreaseComboState();
	void ResetComboState();
};
