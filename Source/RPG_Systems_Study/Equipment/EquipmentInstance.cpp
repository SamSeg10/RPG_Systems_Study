// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentInstance.h"

#include "EquipmentDefinition.h"
#include "GameFramework/Character.h"
#include "RPG_Systems_Study/Fragments/InventoryFragment_Equippable.h"
#include "RPG_Systems_Study/Items/ItemInstance.h"

void UEquipmentInstance::Initialize(UItemInstance* ItemInstance, ACharacter* Character)
{
	if (!ItemInstance) return;
	
	SourceItemInstance = ItemInstance;
	
	const UInventoryFragment_Equippable* EquippableFragment = Cast<UInventoryFragment_Equippable>(
		ItemInstance->FindFragmentByClass(UInventoryFragment_Equippable::StaticClass())
	);
	
	if (!EquippableFragment) return;
	
	EquipmentDefinition = EquippableFragment->EquipmentDefinition;
	HandleEquipItem(Character); // This is assuming we always want to equip the item on initialize, but it doesn't have to work that way
}

void UEquipmentInstance::HandleEquipItem(ACharacter* Character)
{
	UEquipmentDefinition* DefinitionCDO = EquipmentDefinition.GetDefaultObject(); // CDO = "Class Default Object"
	
	if (!DefinitionCDO) return;
	
	SpawnedEquipmentActor = GetWorld()->SpawnActor(DefinitionCDO->EquipmentActorClass);
	
	if (!SpawnedEquipmentActor) return;
	
	SpawnedEquipmentActor->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, DefinitionCDO->AttachSocketName);
}

void UEquipmentInstance::HandleUnequipItem(ACharacter* Character)
{
	if (SpawnedEquipmentActor)
	{
		SpawnedEquipmentActor->Destroy();
		SpawnedEquipmentActor = nullptr; // Make sure nothing points to the variable so garbage collector can delete it (simply destroying it is not enough)
	}
}
