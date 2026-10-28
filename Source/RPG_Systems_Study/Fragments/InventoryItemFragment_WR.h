// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemFragment.h"
#include "InventoryItemFragment_WR.generated.h"

/**
 * 
 */
UCLASS()
class RPG_SYSTEMS_STUDY_API UInventoryItemFragment_WR : public UInventoryItemFragment
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<UStaticMesh> ItemMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options")
	bool bCanBeDropped = true;
	
};
