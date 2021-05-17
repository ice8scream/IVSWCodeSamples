// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "ResourceComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResourceOnUpdateSignature, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FResourceOnEmptySignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Abstract, Blueprintable, DefaultToInstanced)
class IVSW_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UResourceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void InternalSetCurrentValue(float NewValue);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetCurrentValue(float NewValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetMaxValue(float NewValue);

	UFUNCTION(BlueprintCallable)
	virtual float GetMaxValue() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetCurrentValue() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetPercentage() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool ConsumeResource(float Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RefillResource(float Value);

	UPROPERTY(BlueprintAssignable, Category = "Resource|Changes")
	FResourceOnUpdateSignature OnCurrentResourceChange;

	UPROPERTY(BlueprintAssignable, Category = "Resource|Changes")
	FResourceOnUpdateSignature OnMaxResourceChange;

	UPROPERTY(BlueprintAssignable, Category = "Resource|Changes")
	FResourceOnEmptySignature OnResourceEmpty;

private:
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float CurrentValue = .0f;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float MaxValue = .0f;
};
