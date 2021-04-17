// Fill out your copyright notice in the Description page of Project Settings.


#include "InTimeRotationBehaviour.h"


void UInTimeRotationBehaviour::Tick(float DeltaTime)
{
	RotationTime += DeltaTime;
	if (RotationTime >= EndRotationTime)
	{
		EndRotation();
		return;
	}
	ActorToRotate->SetActorRotation(
		FMath::Lerp(StartRotator, EndRotator, RotationTime / EndRotationTime));
}

bool UInTimeRotationBehaviour::IsTickable() const
{
	return bIsTickable;
}

bool UInTimeRotationBehaviour::IsTickableWhenPaused() const
{
	return bIsTickableWhenPaused;
}

TStatId UInTimeRotationBehaviour::GetStatId() const
{
	return TStatId();
}

void UInTimeRotationBehaviour::EndRotation()
{
	ActorToRotate->SetActorRotation(EndRotator);
	BreakRotation();
}

void UInTimeRotationBehaviour::InitRotationActor(AActor* InitialActorToRotation)
{
	ActorToRotate = InitialActorToRotation;
}

void UInTimeRotationBehaviour::StartRotation(FVector LocationRotateTo, float RotationTimeLength)
{
	if (!IsValid(ActorToRotate))
	{
		UE_LOG(LogTemp, Error, TEXT("%s Actor to rotations is invalid"), *this->GetName());
		return;
	}

	RotationTime = .0f;
	EndRotationTime = RotationTimeLength;

	StartRotator = ActorToRotate->GetActorRotation();
	EndRotator = (LocationRotateTo - ActorToRotate->GetActorLocation())
	             .GetSafeNormal2D().ToOrientationRotator();

	bIsTickable = true;
}

void UInTimeRotationBehaviour::BreakRotation()
{
	bIsTickable = false;
}
