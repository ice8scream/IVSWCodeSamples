// Fill out your copyright notice in the Description page of Project Settings.


#include "Box_ShapeBehaviour.h"

void UBox_ShapeBehaviour::InitShape_Implementation(const TArray<UPrimitiveComponent*>& Shapes)
{
	for (UPrimitiveComponent* PotentialShape : Shapes)
	{
		if (PotentialShape->GetCollisionShape().IsBox())
		{
			Super::InitShape_Implementation({PotentialShape});
			Box = Cast<UBoxComponent>(PotentialShape);
			Execute_UpdateShape(this);
			return;
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Box_ShapeBehaviour: %s can't found any box"), *this->GetName());
}

void UBox_ShapeBehaviour::UpdateShape_Implementation()
{
	if (IsValid(Box))
	{
		Box->SetBoxExtent(FVector(Distance / 2, HalfWidth, Box->GetUnscaledBoxExtent().Z));
		Box->SetRelativeLocation(ShapeRelativeCenter + FVector(Distance / 2, 0, 0));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Box_ShapeBehaviour: %s box is invalid"), *this->GetName());
	}
}

float UBox_ShapeBehaviour::GetDistance_Implementation() const
{
	return Distance;
}
