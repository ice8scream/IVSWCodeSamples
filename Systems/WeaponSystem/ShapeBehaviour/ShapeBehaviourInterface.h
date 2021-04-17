// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ShapeBehaviourInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UShapeBehaviourInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IVSW_API IShapeBehaviourInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitShape(const TArray<UPrimitiveComponent*>& Shapes);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateShape();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GetOverlappedActors(UPARAM(DisplayName="OverlappedActors") TArray<AActor*>& OutOverlappedActors) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetDistance() const;
};
