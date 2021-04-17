// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponBehaviourInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UWeaponBehaviourInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IVSW_API IWeaponBehaviourInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GetAttackedActors(TArray<AActor*>& Actors);
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitWeapon(AActor* WeaponOwner);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PerformAttack(FVector AttackLocation);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BreakAttack();
};
