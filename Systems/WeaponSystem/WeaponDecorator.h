// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Weapon.h"
#include "WeaponBase.h"
#include "WeaponDecorator.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract, DefaultToInstanced, EditInlineNew)
class IVSW_API UWeaponDecorator : public UWeaponBase
{
	GENERATED_BODY()

	virtual UWorld* GetWorld() const override;


protected:
	virtual void InitWeapon_Implementation(AActor* WeaponOwner) override;
	virtual void PerformAttack_Implementation(FVector AttackLocation) override;
	virtual void BreakAttack_Implementation() override;
	virtual void GetAttackedActors_Implementation(TArray<AActor*>& Actors) override;

	UPROPERTY()
	UWeapon* NearestFinalWeapon;

	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category="PureDecoratedWeapon")
	UWeaponBase* DecoratedWeapon;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual UWeapon* GetNearestFinalWeapon();
};
