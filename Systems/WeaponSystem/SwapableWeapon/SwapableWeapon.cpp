// Fill out your copyright notice in the Description page of Project Settings.


#include "SwapableWeapon.h"

void USwapableWeapon::InitWeapon_Implementation(AActor* WeaponOwner)
{
	for (auto It = Weapons.CreateConstIterator(); It; ++It)
	{
		It.Value()->Execute_InitWeapon(It.Value(), WeaponOwner);
	}

	if (InitialWeaponName.GetStringLength() && Weapons.Contains(InitialWeaponName))
	{
		NextWeapon = Weapons[InitialWeaponName];
	}
	else if (Weapons.Num())
	{
		NextWeapon = (*Weapons.begin()).Value;
	}

	ActualizeCurrentWeapon();
}

void USwapableWeapon::PerformAttack_Implementation(FVector AttackLocation)
{
	if (!bIsAttackInProgress)
	{
		bIsAttackInProgress = true;
		Super::PerformAttack_Implementation(AttackLocation);
	}
}

void USwapableWeapon::ActualizeCurrentWeapon()
{
	if (!NextWeapon)
	{
		return;
	}

	if (DecoratedWeapon && GetNearestFinalWeapon())
	{
		GetNearestFinalWeapon()->GetAbtBehaviour()->OnFinish.RemoveDynamic(
			this, &USwapableWeapon::OnEndCurrentAttackProgress);
	}

	DecoratedWeapon = NextWeapon;
	NearestFinalWeapon = nullptr;

	if (GetNearestFinalWeapon())
	{
		auto Shape = GetNearestFinalWeapon()->GetShapeBehaviour();
		Shape->Execute_UpdateShape(Shape);

		GetNearestFinalWeapon()->GetAbtBehaviour()->OnFinish.AddDynamic(
			this, &USwapableWeapon::OnEndCurrentAttackProgress);
	}
}

void USwapableWeapon::OnEndCurrentAttackProgress()
{
	ActualizeCurrentWeapon();
	bIsAttackInProgress = false;
}

void USwapableWeapon::SwapWeapon_Implementation(const FName& WeaponName)
{
	NextWeapon = Weapons[WeaponName];
	if (!bIsAttackInProgress)
	{
		ActualizeCurrentWeapon();
	}
}
