// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "UObject/Object.h"
#include "EquipmentInstance.generated.h"

class UGameplayEffect;
class UItemInstance;
class UEquipmentDefinition;
/**
 * 
 */
UCLASS(BlueprintType)
class RPG_SYSTEMS_STUDY_API UEquipmentInstance : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<UEquipmentDefinition> EquipmentDefinition;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UItemInstance> SourceItemInstance;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> SpawnedEquipmentActor;
	
	UPROPERTY(BLueprintReadOnly)
	TArray<FActiveGameplayEffectHandle> AppliedEffectHandles;
	
	UFUNCTION(BlueprintCallable)
	void Initialize(UItemInstance* ItemInstance, ACharacter* Character, TSubclassOf<UGameplayEffect> EquipmentGE);
	
	UFUNCTION(BlueprintCallable)
	void HandleEquipItem(ACharacter* Character, TSubclassOf<UGameplayEffect> EquipmentGE);
	
	UFUNCTION(BlueprintCallable)
	void HandleUnequipItem(ACharacter* Character);
};
