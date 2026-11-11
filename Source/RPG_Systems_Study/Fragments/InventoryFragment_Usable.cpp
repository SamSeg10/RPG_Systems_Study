// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryFragment_Usable.h"

#include "RPG_Systems_Study/ItemActions/ItemAction.h"

bool UInventoryFragment_Usable::Use(AActor* ItemOwner, UItemInstance* ItemInstance)
{
	bool bAnySucceeded = false;
	
	for (const TObjectPtr<UItemAction>& Action : OnUseActions)
	{
		if (Action && Action->Execute(ItemOwner, ItemInstance))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString(*Action->GetName()));
			bAnySucceeded = true;
		}
	}
		
	return bAnySucceeded;
}
