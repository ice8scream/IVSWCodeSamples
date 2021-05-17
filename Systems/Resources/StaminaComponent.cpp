// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaComponent.h"


// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ComponentTags.AddUnique("Stamina");
	// ...
}


// Called when the game starts
void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsRecentlyConsumed)
	{
		RefillResource(RefillSpeed * DeltaTime);
	}
	// ...
}

bool UStaminaComponent::ConsumeResource_Implementation(float Value)
{
	if (Value - GetCurrentValue() > 0)
	{
		UpdateStaminaCredit(Value - GetCurrentValue());
	}

	bool isConsumed = Super::ConsumeResource_Implementation(Value);
	if (isConsumed)
	{
		bIsRecentlyConsumed = true;
		GetWorld()->GetTimerManager().SetTimer(UnBlockRefillHandle, this, &UStaminaComponent::StartRefillStamina,
		                                       RefillDelay);
	}
	return isConsumed;
}

void UStaminaComponent::RefillResource_Implementation(float Value)
{
	Super::RefillResource_Implementation(Value - StaminaCredit);
	if (StaminaCredit)
	{
		UpdateStaminaCredit(StaminaCredit - Value);
	}
}

void UStaminaComponent::StartRefillStamina()
{
	UpdateStaminaCredit();
	bIsRecentlyConsumed = false;
}

void UStaminaComponent::UpdateStaminaCredit(float NewCredit)
{
	StaminaCredit = NewCredit < 0 ? 0 : NewCredit;
}
