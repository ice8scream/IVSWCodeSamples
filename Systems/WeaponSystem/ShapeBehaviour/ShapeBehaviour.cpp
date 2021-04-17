// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeBehaviour.h"

UWorld* UShapeBehaviour::GetWorld() const
{
	if (GIsEditor && !GIsPlayInEditorWorld)
	{
		return nullptr;
	}
	if (GetOuter())
	{
		return GetOuter()->GetWorld();
	}
	return nullptr;
}

void UShapeBehaviour::InitShape_Implementation(const TArray<UPrimitiveComponent*>& Shapes)
{
	if (!Shapes.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("ShapeBehaviour: %s initialisation has no shapes"), *this->GetName());
		return;
	}
	Shape = Shapes[0];
}

void UShapeBehaviour::GetOverlappedActors_Implementation(TArray<AActor*>& OutOverlappedActors) const
{
	if (!IsValid(Shape))
	{
		UE_LOG(LogTemp, Error, TEXT("%s shape is invalid"), *this->GetName());
		return;
	}

	TArray<FOverlapResult> Overlaps;
	GetWorld()->ComponentOverlapMulti(Overlaps, Shape, Shape->GetComponentLocation(), Shape->GetComponentQuat());

	for (auto Overlap : Overlaps)
	{
		if (Overlap.GetComponent()->GetGenerateOverlapEvents())
		{
			OutOverlappedActors.AddUnique(Overlap.GetActor());
		}
	}
}
