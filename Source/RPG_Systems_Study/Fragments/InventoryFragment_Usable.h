// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemFragment.h"
#include "InventoryFragment_Usable.generated.h"

class UItemAction;
/**
 * 
 */
UCLASS()
class RPG_SYSTEMS_STUDY_API UInventoryFragment_Usable : public UInventoryItemFragment
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	bool Use(AActor* ItemOwner);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options")
	bool bConsumeOnUse = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "Actions") //"Instanced" is necessary to be able to create instances of these actions within blueprints
	TArray<TObjectPtr<UItemAction>> OnUseActions;
};
