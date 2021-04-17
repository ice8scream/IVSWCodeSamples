// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InTimeRotationBehaviourInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInTimeRotationBehaviourInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IVSW_API IInTimeRotationBehaviourInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:

	virtual void EndRotation() = 0;
public:
	virtual void InitRotationActor(AActor* InitialActorToRotation) = 0;
	virtual void StartRotation(FVector LocationRotateTo, float RotationTimeLength) = 0;
	virtual void BreakRotation() = 0;
};
