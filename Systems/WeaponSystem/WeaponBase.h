// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "WeaponBehaviourInterface.h"
#include "UObject/Object.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew, Abstract, CollapseCategories)
class IVSW_API UWeaponBase : public UObject, public IWeaponBehaviourInterface
{
	GENERATED_BODY()
};
