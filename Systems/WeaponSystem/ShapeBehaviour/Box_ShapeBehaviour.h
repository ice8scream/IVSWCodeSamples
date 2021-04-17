// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ShapeBehaviour.h"
#include "Components/BoxComponent.h"

#include "Box_ShapeBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class IVSW_API UBox_ShapeBehaviour : public UShapeBehaviour
{
	GENERATED_BODY()

	virtual void InitShape_Implementation(const TArray<UPrimitiveComponent*>& Shapes) override;
	virtual void UpdateShape_Implementation() override;
	virtual float GetDistance_Implementation() const override;

	UPROPERTY()
	UBoxComponent* Box;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin="0"))
	float Distance = .0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin="0"))
	float HalfWidth = .0f;
};
