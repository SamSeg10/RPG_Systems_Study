// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract, DefaultToInstanced, EditInlineNew)
class RPG_SYSTEMS_STUDY_API UItemAction : public UObject
{
	GENERATED_BODY()
	
public: 
	UFUNCTION(BlueprintImplementableEvent) //This means that this function can only be implemented in blueprints. To be able to implement it in c++, use BlueprintNativeEvent
	bool Execute(AActor* ItemOwner);
};
