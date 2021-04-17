// Fill out your copyright notice in the Description page of Project Settings.


#include "Sphere_ShapeBehaviour.h"

#include "Kismet/KismetMathLibrary.h"

void USphere_ShapeBehaviour::InitShape_Implementation(const TArray<UPrimitiveComponent*>& Shapes)
{
	for (UPrimitiveComponent* PotentialShape : Shapes)
	{
		if (PotentialShape->GetCollisionShape().IsSphere())
		{
			Super::InitShape_Implementation({PotentialShape});
			Sphere = Cast<USphereComponent>(PotentialShape);
			Execute_UpdateShape(this);
			return;
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Sphere_ShapeBehaviour: %s can't found any sphere"), *this->GetName());
}

void USphere_ShapeBehaviour::UpdateShape_Implementation()
{
	if (IsValid(Sphere))
	{
		Sphere->SetSphereRadius(Radius);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Sphere_ShapeBehaviour: %s sphere is invalid"), *this->GetName());
	}
}

void USphere_ShapeBehaviour::GetOverlappedActors_Implementation(TArray<AActor*>& Out_OverlappedActors) const
{
	if (!IsValid(Sphere))
	{
		UE_LOG(LogTemp, Error, TEXT("Sphere_ShapeBehaviour: %s sphere is invalid"), *this->GetName());
		return;
	}
	Super::GetOverlappedActors_Implementation(Out_OverlappedActors);

	if (HalfAngle != 180)
	{
		Out_OverlappedActors = Out_OverlappedActors.FilterByPredicate([&](AActor* Actor)
		{
			return HalfAngle >= UKismetMathLibrary::DegAcos(FVector::DotProduct(
				Sphere->GetForwardVector().GetSafeNormal2D(),
				(Actor->GetActorLocation() - Sphere->GetComponentLocation()).GetSafeNormal2D()));
		});


		for (int8 AngleSign = -1; AngleSign < 2; AngleSign += 2)
		{
			FVector ShapeBorderEnd = Sphere->GetComponentLocation() +
				Sphere->GetForwardVector().RotateAngleAxis(HalfAngle * AngleSign, FVector(0, 0, 1)) * Radius;

			TArray<FHitResult> BorderOverlaps;
			GetWorld()->LineTraceMultiByObjectType(BorderOverlaps, Sphere->GetComponentLocation(), ShapeBorderEnd,
			                                       FCollisionObjectQueryParams::AllObjects);
			for (auto Overlap : BorderOverlaps)
			{
				if (Overlap.GetComponent()->GetGenerateOverlapEvents())
				{
					Out_OverlappedActors.AddUnique(Overlap.GetActor());
				}
			}
		}
	}
}

float USphere_ShapeBehaviour::GetDistance_Implementation() const
{
	return Radius;
}
