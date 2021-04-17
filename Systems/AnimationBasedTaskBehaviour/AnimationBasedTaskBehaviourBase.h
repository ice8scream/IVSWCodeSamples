// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AnimationBasedTaskBehaviourInterface.h"
#include "UObject/Object.h"
#include "AnimationBasedTaskBehaviourBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTaskFlushed);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTaskActionFlushed, const FName&, ActionName);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract, DefaultToInstanced, EditInlineNew, CollapseCategories)
class IVSW_API UAnimationBasedTaskBehaviourBase : public UObject, public IAnimationBasedTaskBehaviourInterface,
                                                  public FTickableGameObject
{
	GENERATED_BODY()

protected:

	//TODO Refactor to timers
	
	bool bIsTickable = false;
	bool bIsTickableWhenPaused = false;
	bool bIsTickableInEditor = false;

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual bool IsTickableWhenPaused() const override;

	virtual UWorld* GetTickableGameObjectWorld() const override;

	virtual TStatId GetStatId() const override;

	virtual void EndTask();

	bool bIsBreak = false;

	UPROPERTY()
	UAnimInstance* AnimInstance;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin="0"))
	TMap<FName, float> ActionTimes;

	TArray<TTuple<FName, float>> ActionsTimeBasedQueue;
	uint8 NextActionIndex = 0;

	float TaskTime = .0f;

public:


	UPROPERTY(BlueprintAssignable)
	FOnTaskFlushed OnStart;
	UPROPERTY(BlueprintAssignable)
	FOnTaskFlushed OnFinish;
	UPROPERTY(BlueprintAssignable)
	FOnTaskActionFlushed OnAction;

	virtual void Init_Implementation(UAnimInstance* InitialAnimInstance) override;
	virtual bool Start_Implementation() override;
	virtual void Break_Implementation() override;
	virtual bool GetActionTime_Implementation(FName ActionName, float& OutActionTime) override;
	virtual float GetTaskEndTime_Implementation() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnActionDispatch(const FName& ActionName);
};
