﻿// Copyright Noroth

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#define REGISTER_NATIVE_TAG(Prefix, Attribute, Description) \
{ \
	GameplayTags.Attributes_##Prefix##_##Attribute = UGameplayTagsManager::Get().AddNativeGameplayTag( \
		Prefix##AttributeName(FString(#Attribute)), \
		FString(Description) \
	); \
}

#define REGISTER_NATIVE_PRIMARY_TAG(Attribute, Description) REGISTER_NATIVE_TAG(Primary, Attribute, Description)
#define REGISTER_NATIVE_SECONDARY_TAG(Attribute, Description) REGISTER_NATIVE_TAG(Secondary, Attribute, Description)


/**
 * AuraGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */
struct FAuraGameplayTags
{
	static const FAuraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;
	
	
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	
private:
	static FAuraGameplayTags GameplayTags;
	static FName SecondaryAttributeName(const FString& AttributeName);
	static FName PrimaryAttributeName(const FString& AttributeName);
	
};
