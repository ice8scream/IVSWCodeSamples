// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimationBasedTaskBehaviourBase.h"
#include "AnimationBasedTaskBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class IVSW_API UAnimationBasedTaskBehaviour : public UAnimationBasedTaskBehaviourBase
{
	GENERATED_BODY()

	UAnimationBasedTaskBehaviour();

public:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AttackAnimation;

	virtual void Init_Implementation(UAnimInstance* InitialAnimInstance) override;
	virtual bool Start_Implementation() override;
	virtual void Break_Implementation() override;
};
