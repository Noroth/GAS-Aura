// Copyright Noroth

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = PC->GetHUD<AAuraHUD>())
		{
			return AuraHUD->GetOverlayWidgetController(BuildWidgetControllerParams(PC));
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = WorldContextObject->GetWorld()->GetFirstPlayerController())
	{
		if (AAuraHUD* AuraHUD = PC->GetHUD<AAuraHUD>())
		{
			return AuraHUD->GetAttributeMenuWidgetController(BuildWidgetControllerParams(PC));
		}
	}

	return nullptr;
}

FWidgetControllerParams UAuraAbilitySystemLibrary::BuildWidgetControllerParams(APlayerController* PC)
{
	AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	UAttributeSet* AS = PS->GetAttributeSet();
	
	return  FWidgetControllerParams(PC, PS, ASC, AS);
}
