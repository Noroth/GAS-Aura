// Copyright Noroth


#include "AuraGameplayTags.h"

#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	REGISTER_NATIVE_PRIMARY_TAG(Strength, "Increases physical damage")
	REGISTER_NATIVE_PRIMARY_TAG(Intelligence, "Increases magical damage")
	REGISTER_NATIVE_PRIMARY_TAG(Resilience, "Increases Armor and Armor Penetration")
	REGISTER_NATIVE_PRIMARY_TAG(Vigor, "Increases Health")

	REGISTER_NATIVE_SECONDARY_TAG(Armor, "Reduces Damage taken, improves Block Chance");
	REGISTER_NATIVE_SECONDARY_TAG(ArmorPenetration, "Ignored Percentage of enemy armor, increases Critical Hit Chance")
	REGISTER_NATIVE_SECONDARY_TAG(BlockChance, "Chance to cut incoming damage in half")
	REGISTER_NATIVE_SECONDARY_TAG(CriticalHitChance, "Chance to double damage plus critical hit bonus")
	REGISTER_NATIVE_SECONDARY_TAG(CriticalHitDamage, "Bonus damage added when critical hit is scored")
	REGISTER_NATIVE_SECONDARY_TAG(CriticalHitResistance, "Reduces Critical Hit Chance of attacking enemies")
	REGISTER_NATIVE_SECONDARY_TAG(HealthRegeneration, "Amount of Health regenerated every 1 second")
	REGISTER_NATIVE_SECONDARY_TAG(ManaRegeneration, "Amount of Mana reginerated every 1 second")
	REGISTER_NATIVE_SECONDARY_TAG(MaxHealth, "Maximum amount of Health obtainable")
	REGISTER_NATIVE_SECONDARY_TAG(MaxMana, "Maximum amount of Mana obtainable")

	// Input Tags
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	GameplayTags.InputTag_LMB = Manager.AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input Tag for the Left Mouse Button")
	);
	
	GameplayTags.InputTag_RMB = Manager.AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input Tag for the Right Mouse Button")
	);
	
	GameplayTags.InputTag_1 = Manager.AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for 1 key")
	);
	
	GameplayTags.InputTag_2 = Manager.AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for 2 key")
	);
	
	GameplayTags.InputTag_3 = Manager.AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for 3 key")
	);
	
	GameplayTags.InputTag_4 = Manager.AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input Tag for 4 key")
	);
}

FName FAuraGameplayTags::SecondaryAttributeName(const FString& AttributeName)
{
	return FName(*FString::Printf(TEXT("Attributes.Secondary.%ls"), *AttributeName));
}

FName FAuraGameplayTags::PrimaryAttributeName(const FString& AttributeName)
{
	return FName(*FString::Printf(TEXT("Attributes.Primary.%ls"), *AttributeName));
}
