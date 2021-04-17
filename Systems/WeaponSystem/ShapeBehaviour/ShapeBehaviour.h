// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "ShapeBehaviourInterface.h"
#include "UObject/Object.h"
#include "ShapeBehaviour.generated.h"

/**
 * ShapeBehaviour is the base class for an Object that provides PrimitiveComponent component overlap behaviour
 */
UCLASS(BlueprintType, Abstract, DefaultToInstanced, EditInlineNew, CollapseCategories)
class IVSW_API UShapeBehaviour : public UObject, public IShapeBehaviourInterface
{
	GENERATED_BODY()

	UPROPERTY()
	UPrimitiveComponent* Shape;
protected:

	virtual UWorld* GetWorld() const override;

	/** Sets Shape as Shapes[0]. */
	virtual void InitShape_Implementation(const TArray<UPrimitiveComponent*>& Shapes) override;

	/** Return an array of AActors that overlapped component witch must generate overlap events. */
	virtual void GetOverlappedActors_Implementation(TArray<AActor*>& OutOverlappedActors) const override;

public:
	UPROPERTY(EditDefaultsOnly)
	FVector ShapeRelativeCenter;
};
