// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AnimationBasedTaskBehaviourInterface.generated.h"


// This class does not need to be modified.
UINTERFACE()
class UAnimationBasedTaskBehaviourInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IVSW_API IAnimationBasedTaskBehaviourInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(UAnimInstance* InitialAnimInstance);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UPARAM(DisplayName="isStarted") bool Start();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Break();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UPARAM(DisplayName="isActionExist")
	bool GetActionTime(FName ActionName, UPARAM(DisplayName="ActionTime", meta =(DisplayPriority="1"))
	                   float& OutActionTime);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UPARAM(DisplayName="TaskTime") float GetTaskEndTime() const;
};
