// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AttackBehaviourInterface.h"
#include "UObject/Object.h"
#include "AttackBehaviour.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract, DefaultToInstanced, EditInlineNew, CollapseCategories)
class IVSW_API UAttackBehaviour : public UObject, public IAttackBehaviourInterface
{
	GENERATED_BODY()
};
