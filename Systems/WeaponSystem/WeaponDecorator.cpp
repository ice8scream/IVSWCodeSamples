// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponDecorator.h"

void UWeaponDecorator::InitWeapon_Implementation(AActor* WeaponOwner)
{
	DecoratedWeapon->Execute_InitWeapon(DecoratedWeapon, WeaponOwner);
}

void UWeaponDecorator::PerformAttack_Implementation(FVector AttackLocation)
{
	DecoratedWeapon->Execute_PerformAttack(DecoratedWeapon, AttackLocation);
}

void UWeaponDecorator::BreakAttack_Implementation()
{
	DecoratedWeapon->Execute_BreakAttack(DecoratedWeapon);
}

void UWeaponDecorator::GetAttackedActors_Implementation(TArray<AActor*>& Actors)
{
	DecoratedWeapon->Execute_GetAttackedActors(DecoratedWeapon, Actors);
}

UWorld* UWeaponDecorator::GetWorld() const
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && ensureMsgf(
			GetOuter(), TEXT("WeaponDecorator: %s has a null OuterPrivate in UWeaponDecorator::GetWorld()"),
			*GetFullName())
		&& !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		return GetOuter()->GetWorld();
	}
	return nullptr;
}

UWeapon* UWeaponDecorator::GetNearestFinalWeapon()
{
	if (!NearestFinalWeapon)
	{
		if (Cast<UWeapon>(DecoratedWeapon))
		{
			NearestFinalWeapon = Cast<UWeapon>(DecoratedWeapon);
		}
		else if (ensureMsgf(
			Cast<UWeaponDecorator>(DecoratedWeapon),
			TEXT("WeaponDecorator: %s DecoratedWeapon is not Weapon or WeaponDecorator, WeaponDecorator is %s"),
			*GetFullName(), *DecoratedWeapon->GetFullName()))
		{
			NearestFinalWeapon = Cast<UWeaponDecorator>(DecoratedWeapon)->GetNearestFinalWeapon();
		}
		else
		{
			return nullptr;
		}
	}
	return NearestFinalWeapon;
}
