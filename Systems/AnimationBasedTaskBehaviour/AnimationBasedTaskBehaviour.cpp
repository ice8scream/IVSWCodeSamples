// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationBasedTaskBehaviour.h"

UAnimationBasedTaskBehaviour::UAnimationBasedTaskBehaviour()
{
	ActionTimes =
	{
		{"Rotation", .0f},
		{"Attack", .0f},
		{"Cooldown", .0f}
	};
}

void UAnimationBasedTaskBehaviour::Init_Implementation(UAnimInstance* InitialAnimInstance)
{
	Super::Init_Implementation(InitialAnimInstance);
}

bool UAnimationBasedTaskBehaviour::Start_Implementation()
{
	if (Super::Start_Implementation())
	{
		AnimInstance->Montage_Play(AttackAnimation);
		return true;
	}
	return false;
}

void UAnimationBasedTaskBehaviour::Break_Implementation()
{
	Super::Break_Implementation();
	AnimInstance->Montage_Stop(AttackAnimation->BlendOut.GetBlendTime(), AttackAnimation);
}
