// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ResourceComponent.h"
#include "StaminaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Abstract)
class IVSW_API UStaminaComponent : public UResourceComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStaminaComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool ConsumeResource_Implementation(float Value) override;
	virtual void RefillResource_Implementation(float Value) override;
	virtual void StartRefillStamina();

private:

	bool bIsRecentlyConsumed = false;

	FTimerHandle UnBlockRefillHandle;

	UPROPERTY(meta = (ClampMin = "0.0"))
	float StaminaCredit = .0f;

	UPROPERTY(EditAnywhere)
	float RefillDelay = .0f;

	UPROPERTY(EditAnywhere)
	float RefillSpeed = .0f;

	void UpdateStaminaCredit(float NewCredit = 0);
};
