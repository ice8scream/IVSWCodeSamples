// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ShapeBehaviour.h"
#include "Components/SphereComponent.h"

#include "Sphere_ShapeBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class IVSW_API USphere_ShapeBehaviour : public UShapeBehaviour
{
	GENERATED_BODY()

	virtual void InitShape_Implementation(const TArray<UPrimitiveComponent*>& Shapes) override;
	virtual void UpdateShape_Implementation() override;
	virtual void GetOverlappedActors_Implementation(TArray<AActor*>& Out_OverlappedActors) const override;
	virtual float GetDistance_Implementation() const override;

	UPROPERTY()
	USphereComponent* Sphere;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin="0"))
	float Radius = .0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin="0", ClampMax="180"))
	float HalfAngle = .0f;
};
