// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponInitInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UWeaponInitInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IVSW_API IWeaponInitInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GetWeaponShapes(TArray<UPrimitiveComponent*>& Shapes);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UPARAM(DisplayName="AnimationInstance") UAnimInstance* GetAnimationInstance();
};
