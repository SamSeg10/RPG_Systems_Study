// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInstance.h"

#include "RPG_Systems_Study/Fragments/InventoryItemFragment.h"
#include "RPG_Systems_Study/Items/ItemDefinition.h"

float UItemInstance::GetStatValue(FGameplayTag StatTag)
{
	return StatsMap.FindRef(StatTag);
}

void UItemInstance::SetStatValue(FGameplayTag StatTag, float StatValue)
{
	StatsMap.Add(StatTag, StatValue);
}

void UItemInstance::Initialize(TSubclassOf<UItemDefinition> ItemDef)
{
	if (!ItemDef) return;
	
	ItemDefinition = ItemDef;
	
	UItemDefinition* ItemCDO = ItemDefinition.GetDefaultObject();
	
	for (const TObjectPtr<UInventoryItemFragment>& Fragment : ItemCDO->Fragments)
	{
		Fragment->OnInstanceCreated(this);
	}
}

const UInventoryItemFragment* UItemInstance::FindFragmentByClass(
	const TSubclassOf<UInventoryItemFragment> FragmentClass)
{
	if (!FragmentClass) return nullptr;
	
	UItemDefinition* ItemCDO = ItemDefinition.GetDefaultObject();
	
	return ItemCDO->FindFragmentByClass(ItemDefinition, FragmentClass);
}

// We need to change the owner of the instance because if not, the garbage collector won't get rid of the destroyed pickup game object since it will still be referenced
void UItemInstance::ChangeOwner(UObject* NewOwner)
{
	if (!NewOwner) return;
	
	this->Rename(nullptr, NewOwner);
}
