// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Chaos/AABBTree.h"
#include "IVSW/Systems/WeaponSystem/WeaponDecorator.h"


#include "SwapableWeapon.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract, DefaultToInstanced, EditInlineNew, HideCategories="PureDecoratedWeapon")
class IVSW_API USwapableWeapon : public UWeaponDecorator
{
	GENERATED_BODY()

	virtual void InitWeapon_Implementation(AActor* WeaponOwner) override;
	virtual void PerformAttack_Implementation(FVector AttackLocation) override;
	// virtual void BreakAttack_Implementation() override;
	// virtual void GetAttackedActors_Implementation(TArray<AActor*>& Actors) override;

protected:
	UFUNCTION()
	void ActualizeCurrentWeapon();

	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly)
	TMap<FName, UWeaponBase*> Weapons;

	UPROPERTY()
	FName InitialWeaponName = "InitialWeapon";

	UPROPERTY()
	UWeaponBase* NextWeapon = nullptr;

	UPROPERTY(BlueprintReadOnly)
	bool bIsAttackInProgress = false;

	UFUNCTION()
	void OnEndCurrentAttackProgress();

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SwapWeapon(const FName& WeaponName);
};
