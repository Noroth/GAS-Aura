// Copyright Noroth


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server.
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client.
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);

	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
	AttributeSet = AuraPlayerState->GetAttributeSet();
	
	InitHUD();
}

void AAuraCharacter::InitHUD() const
{
	APlayerController* PlayerController = GetController<APlayerController>();
	// We don't have a player controller on a server. Only on Clients with locally controlled Pawns.
	if (!PlayerController) return;
	
	AAuraHUD* AuraHUD = PlayerController->GetHUD<AAuraHUD>();
	checkf(AuraHUD, TEXT("Could not cast to AuraHUD. Check if is correctly set in the BP_Game."))

	AuraHUD->InitOverlay(PlayerController, GetPlayerState<AAuraPlayerState>(), AbilitySystemComponent, AttributeSet);
}

