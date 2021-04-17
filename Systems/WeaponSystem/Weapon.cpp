// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "WeaponInitInterface.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWeapon::InitWeapon_Implementation(AActor* WeaponOwner)
{
	if (WeaponOwner->GetClass()->ImplementsInterface(UWeaponInitInterface::StaticClass()))
	{
		OwnerActor = WeaponOwner;

		TArray<UPrimitiveComponent*> Shapes;
		IWeaponInitInterface::Execute_GetWeaponShapes(WeaponOwner, Shapes);
		ShapeBehaviour->Execute_InitShape(ShapeBehaviour, Shapes);

		AbtBehaviour->Execute_Init(AbtBehaviour, IWeaponInitInterface::Execute_GetAnimationInstance(WeaponOwner));
		if (!RotationBehaviour)
			RotationBehaviour = NewObject<UInTimeRotationBehaviour>(GetOuter(),TEXT("RotationBehaviour"));
		RotationBehaviour->InitRotationActor(WeaponOwner);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't implements WeaponInitInterface"), *WeaponOwner->GetName());
	}


	AbtBehaviour->OnAction.AddDynamic(this, &UWeapon::OnAbtBehaviourTaskFlushed);
}

void UWeapon::PerformAttack_Implementation(FVector AttackLocation)
{
	float RotationTime;
	AbtBehaviour->Execute_GetActionTime(AbtBehaviour, FName("Rotation"), RotationTime);
	if (AbtBehaviour->Execute_Start(AbtBehaviour))
	{
		RotationBehaviour->StartRotation(AttackLocation, RotationTime);

		ACharacter* CharacterActor = Cast<ACharacter>(OwnerActor);
		if (CharacterActor)
		{
			bSavedCharacterOrientation = CharacterActor->GetCharacterMovement()->bOrientRotationToMovement;
			CharacterActor->GetCharacterMovement()->bOrientRotationToMovement = false;
		}
	}
}

void UWeapon::GetAttackedActors_Implementation(TArray<AActor*>& Actors)
{
	ShapeBehaviour->Execute_GetOverlappedActors(ShapeBehaviour, Actors);
}

void UWeapon::BreakAttack_Implementation()
{
	AbtBehaviour->Execute_Break(AbtBehaviour);
	RotationBehaviour->BreakRotation();

	ACharacter* CharacterActor = Cast<ACharacter>(OwnerActor);
	if (CharacterActor)
	{
		CharacterActor->GetCharacterMovement()->bOrientRotationToMovement = bSavedCharacterOrientation;
	}
}

void UWeapon::OnAbtBehaviourTaskFlushed(const FName& ActionName)
{
	if (ActionName == TEXT("Attack"))
	{
		TArray<AActor*> Actors;
		Execute_GetAttackedActors(this, Actors);
		ACharacter* CharacterActor = Cast<ACharacter>(OwnerActor);
		if (CharacterActor)
		{
			CharacterActor->GetCharacterMovement()->bOrientRotationToMovement = bSavedCharacterOrientation;
		}

		if (Actors.Num())
		{
			for (auto AttackBehaviour : AttackBehaviours)
			{
				AttackBehaviour->Execute_Attack(AttackBehaviour, Actors);
			}
		}
	}
}

UShapeBehaviour* UWeapon::GetShapeBehaviour() const
{
	return ShapeBehaviour;
}

UAnimationBasedTaskBehaviourBase* UWeapon::GetAbtBehaviour() const
{
	return AbtBehaviour;
}
