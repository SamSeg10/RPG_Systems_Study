// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentInstance.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EquipmentDefinition.h"
#include "GameplayEffect.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RPG_Systems_Study/Fragments/InventoryFragment_Equippable.h"
#include "RPG_Systems_Study/Items/ItemInstance.h"

void UEquipmentInstance::Initialize(UItemInstance* ItemInstance, ACharacter* Character, TSubclassOf<UGameplayEffect> EquipmentGE)
{
	if (!ItemInstance) return;
	
	SourceItemInstance = ItemInstance;
	
	const UInventoryFragment_Equippable* EquippableFragment = Cast<UInventoryFragment_Equippable>(
		ItemInstance->FindFragmentByClass(UInventoryFragment_Equippable::StaticClass())
	);
	
	if (!EquippableFragment) return;
	
	EquipmentDefinition = EquippableFragment->EquipmentDefinition;
	HandleEquipItem(Character, EquipmentGE); // This is assuming we always want to equip the item on initialize, but it doesn't have to work that way
}

void UEquipmentInstance::HandleEquipItem(ACharacter* Character, TSubclassOf<UGameplayEffect> EquipmentGE)
{
	UEquipmentDefinition* DefinitionCDO = EquipmentDefinition.GetDefaultObject(); // CDO = "Class Default Object"
	
	if (!DefinitionCDO) return;
	
	SpawnedEquipmentActor = GetWorld()->SpawnActor(DefinitionCDO->EquipmentActorClass);
	
	if (!SpawnedEquipmentActor) return;
	
	SpawnedEquipmentActor->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, DefinitionCDO->AttachSocketName);
	
	
	// Logic for GAS
	UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Character);
	if (!OwnerASC) return;
	if (EquipmentGE)
	{
		FGameplayEffectContextHandle EffectContext = OwnerASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		
		FGameplayEffectSpecHandle SpecHandle = OwnerASC->MakeOutgoingSpec(EquipmentGE, 1.0f, EffectContext);
		
		if (SpecHandle.IsValid())
		{
			for (const auto& Pair : SourceItemInstance->StatsMap) // auto& detects the type of the key and value of my Map
			{
				FGameplayTag StatTag = Pair.Key;
				float StatValue = Pair.Value;
				
				SpecHandle.Data->SetSetByCallerMagnitude(StatTag, StatValue);
			}

			const FActiveGameplayEffectHandle EffectHandle = OwnerASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data); // * before variable turns the pointer into a reference
			AppliedEffectHandles.Add(EffectHandle);
		}
	}
	
	if (DefinitionCDO->EffectsToApply.Num() > 0)
	{
		for (TSubclassOf<UGameplayEffect> EffectClass : DefinitionCDO->EffectsToApply)
		{
			FGameplayEffectContextHandle EffectContext = OwnerASC->MakeEffectContext();
			EffectContext.AddSourceObject(this);
			
			const FActiveGameplayEffectHandle EffectHandle = OwnerASC->ApplyGameplayEffectToSelf(EffectClass->GetDefaultObject<UGameplayEffect>(), 1.0f, EffectContext);
			AppliedEffectHandles.Add(EffectHandle);
			
		}
	}
}

void UEquipmentInstance::HandleUnequipItem(ACharacter* Character)
{
	if (SpawnedEquipmentActor)
	{
		SpawnedEquipmentActor->Destroy();
		SpawnedEquipmentActor = nullptr; // Make sure nothing points to the variable so garbage collector can delete it (simply destroying it is not enough)
	}
	
	//Logic for GAS
	UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Character);
	if (OwnerASC)
	{
		for (FActiveGameplayEffectHandle& EffectHandle : AppliedEffectHandles)
		{
			OwnerASC->RemoveActiveGameplayEffect(EffectHandle);
			EffectHandle.Invalidate();
		}
	}
}
