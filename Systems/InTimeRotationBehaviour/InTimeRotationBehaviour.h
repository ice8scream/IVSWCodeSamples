// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "InTimeRotationBehaviourInterface.h"
#include "UObject/Object.h"
#include "InTimeRotationBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class IVSW_API UInTimeRotationBehaviour : public UObject, public FTickableGameObject,
                                          public IInTimeRotationBehaviourInterface
{
	GENERATED_BODY()

protected:

	bool bIsTickable = false;
	bool bIsTickableWhenPaused = false;
	bool bIsTickableInEditor = false;

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual bool IsTickableWhenPaused() const override;

	virtual UWorld* GetTickableGameObjectWorld() const override
	{
		return GetWorld();
	}

	virtual TStatId GetStatId() const override;

	virtual void EndRotation() override;

	UPROPERTY()
	AActor* ActorToRotate;

	FRotator StartRotator;
	FRotator EndRotator;
	float RotationTime = .0f;
	float EndRotationTime = .0f;

public:
	virtual void InitRotationActor(AActor* InitialActorToRotation) override;
	virtual void StartRotation(FVector LocationRotateTo, float RotationTimeLength) override;
	virtual void BreakRotation() override;
};
