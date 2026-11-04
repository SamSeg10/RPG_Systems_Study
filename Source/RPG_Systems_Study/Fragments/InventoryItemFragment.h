// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InventoryItemFragment.generated.h"

class UItemInstance;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract, DefaultToInstanced, EditInlineNew)
class RPG_SYSTEMS_STUDY_API UInventoryItemFragment : public UObject
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintNativeEvent)
	void OnInstanceCreated(UItemInstance* ItemInstance);
};

inline void UInventoryItemFragment::OnInstanceCreated_Implementation(UItemInstance* ItemInstance) {} //Can use "inline" to create implementation of a function without putting it in a cpp file
