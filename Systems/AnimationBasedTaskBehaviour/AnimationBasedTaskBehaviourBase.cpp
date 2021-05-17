// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationBasedTaskBehaviourBase.h"

void UAnimationBasedTaskBehaviourBase::Tick(float DeltaTime)
{
	TaskTime += DeltaTime;
	while (NextActionIndex < ActionsTimeBasedQueue.Num() &&
		ActionsTimeBasedQueue[NextActionIndex].Value <= TaskTime)
	{
		if (!bIsBreak)
		{
			OnAction.Broadcast(ActionsTimeBasedQueue[NextActionIndex].Key);
		}
		++NextActionIndex;
	}

	if (NextActionIndex >= ActionsTimeBasedQueue.Num())
	{
		EndTask();
	}
}

bool UAnimationBasedTaskBehaviourBase::IsTickable() const
{
	return bIsTickable;
}

bool UAnimationBasedTaskBehaviourBase::IsTickableWhenPaused() const
{
	return bIsTickableWhenPaused;
}

UWorld* UAnimationBasedTaskBehaviourBase::GetTickableGameObjectWorld() const
{
	return GetWorld();
}

TStatId UAnimationBasedTaskBehaviourBase::GetStatId() const
{
	return TStatId();
}

void UAnimationBasedTaskBehaviourBase::EndTask()
{
	bIsBreak = false;
	bIsTickable = false;
	OnFinish.Broadcast();
}

void UAnimationBasedTaskBehaviourBase::Init_Implementation(UAnimInstance* InitialAnimInstance)
{
	AnimInstance = InitialAnimInstance;
	OnAction.AddDynamic(this, &UAnimationBasedTaskBehaviourBase::OnActionDispatch);
}

bool UAnimationBasedTaskBehaviourBase::Start_Implementation()
{
	if (bIsTickable)
	{
		return false;
	}

	ActionsTimeBasedQueue.Empty();
	NextActionIndex = 0;

	for (TTuple<FName, float> Action : ActionTimes)
	{
		ActionsTimeBasedQueue.Add(Action);
	}

	ActionsTimeBasedQueue.Sort([](TTuple<FName, float> A, TTuple<FName, float> B)
	{
		return A.Value < B.Value;
	});

	TaskTime = .0f;
	bIsTickable = true;

	OnStart.Broadcast();
	return true;
}

void UAnimationBasedTaskBehaviourBase::Break_Implementation()
{
	bIsBreak = true;
}

bool UAnimationBasedTaskBehaviourBase::GetActionTime_Implementation(FName ActionName, float& OutActionTime)
{
	if (ActionTimes.Contains(ActionName))
	{
		OutActionTime = *ActionTimes.Find(ActionName);
		return true;
	}
	OutActionTime = 0;
	return false;
}

float UAnimationBasedTaskBehaviourBase::GetTaskEndTime_Implementation() const
{
	float TaskEndTime = .0f;
	for (const TTuple<FName, float> Action : ActionTimes)
	{
		TaskEndTime = FMath::Max(TaskTime, Action.Value);
	}
	return TaskEndTime;
}

bool UAnimationBasedTaskBehaviourBase::IsTaskInProgress() const
{
	return bIsTickable;
}

void UAnimationBasedTaskBehaviourBase::OnActionDispatch_Implementation(const FName& ActionName)
{
}
