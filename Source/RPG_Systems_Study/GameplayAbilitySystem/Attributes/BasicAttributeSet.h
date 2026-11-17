

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "RPG_Systems_Study/Characters/BaseCharacters.h"
#include "BasicAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class RPG_SYSTEMS_STUDY_API UBasicAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
	UBasicAttributeSet();
	
public:
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Armor);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Strength);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData MovementSpeedMultiplier;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MovementSpeedMultiplier);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData CarryingCapacity;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, CarryingCapacity);
};