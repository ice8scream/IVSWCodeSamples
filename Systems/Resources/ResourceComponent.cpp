// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceComponent.h"


// Sets default values for this component's properties
UResourceComponent::UResourceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	InternalSetCurrentValue(CurrentValue);
	// ...
}


// Called when the game starts
void UResourceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UResourceComponent::InternalSetCurrentValue_Implementation(float NewValue)
{
	CurrentValue = NewValue;
	CurrentValue = FMath::Clamp(CurrentValue, .0f, MaxValue);
}


// Called every frame
void UResourceComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UResourceComponent::GetMaxValue() const
{
	return MaxValue;
}

float UResourceComponent::GetCurrentValue() const
{
	return CurrentValue;
}

float UResourceComponent::GetPercentage() const
{
	return CurrentValue / MaxValue;
}

void UResourceComponent::RefillResource_Implementation(float Value)
{
	if (Value <= .0f)
	{
		return;
	}
	SetCurrentValue(CurrentValue + Value);
}

bool UResourceComponent::ConsumeResource_Implementation(float Value)
{
	if (!CurrentValue || Value <= .0f)
	{
		return false;
	}
	SetCurrentValue(CurrentValue - Value);
	if (CurrentValue <= .0f)
	{
		OnResourceEmpty.Broadcast();
	}
	return true;
}

void UResourceComponent::SetMaxValue_Implementation(float NewValue)
{
	float OldValue = MaxValue;
	MaxValue = FMath::Clamp(NewValue, .0f, NewValue);
	InternalSetCurrentValue(CurrentValue);
	OnMaxResourceChange.Broadcast(NewValue - OldValue);
}

void UResourceComponent::SetCurrentValue_Implementation(float NewValue)
{
	float OldValue = CurrentValue;
	InternalSetCurrentValue(NewValue);
	OnCurrentResourceChange.Broadcast(NewValue - OldValue);
}
