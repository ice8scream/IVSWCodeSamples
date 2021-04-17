// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IVSW/Systems/AnimationBasedTaskBehaviour/AnimationBasedTaskBehaviourBase.h"
#include "AttackBehaviour/AttackBehaviour.h"
#include "IVSW/Systems/InTimeRotationBehaviour/InTimeRotationBehaviour.h"
#include "ShapeBehaviour/ShapeBehaviour.h"
#include "WeaponBase.h"


#include "Weapon.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract, DefaultToInstanced, EditInlineNew)
class IVSW_API UWeapon : public UWeaponBase
{
	GENERATED_BODY()

	UPROPERTY()
	UAnimInstance* AttackAnimationInstance;
protected:
	friend class UWeaponBase;

	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly)
	UShapeBehaviour* ShapeBehaviour;

	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly)
	TArray<UAttackBehaviour*> AttackBehaviours;

	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly)
	UAnimationBasedTaskBehaviourBase* AbtBehaviour;

	UPROPERTY(BlueprintReadOnly)
	AActor* OwnerActor;

	UPROPERTY()
	UInTimeRotationBehaviour* RotationBehaviour;

	virtual void InitWeapon_Implementation(AActor* WeaponOwner) override;
	virtual void PerformAttack_Implementation(FVector AttackLocation) override;
	virtual void GetAttackedActors_Implementation(TArray<AActor*>& Actors) override;
	virtual void BreakAttack_Implementation() override;

	UFUNCTION()
	virtual void OnAbtBehaviourTaskFlushed(const FName& ActionName);

	bool bSavedCharacterOrientation;

public:
	UFUNCTION(BlueprintCallable)
	UShapeBehaviour* GetShapeBehaviour() const;

	UFUNCTION(BlueprintCallable)
	UAnimationBasedTaskBehaviourBase* GetAbtBehaviour() const;
};
