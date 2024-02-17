// Copyright Noroth


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);


	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();

	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FRotationMatrix YawRotationMatrix = FRotationMatrix(YawRotation);

	const FVector ForwardDirection = YawRotationMatrix.GetUnitAxis(EAxis::X);
	const FVector RightDirection = YawRotationMatrix.GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/**
	 * Line trace from cursor. There are several scenarios
	 * A LastActor is null && ThisActor is null
	 *		- Do nothing
	 * B LastActor is null and ThisActor is valid
	 *		- Highlight ThisActor
	 * C LastActor is valid && ThisActor is null
	 *		- Unhighlight LastActor
	 * D Both actors are vaid but LastActor != ThisActor
	 *		- Unhighlight LastActor && Hightlight ThisActor
	 * E Both actors are valid and are the same actor
	 *		- Do nothing
	 */

	// TODO check if those bools can replace the if - else
	bool bShouldHighlight = ThisActor != nullptr && LastActor != ThisActor;
	bool bShouldUnhighlight = (LastActor && ThisActor) && LastActor != ThisActor;

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case B
			ThisActor->HighlightActor();
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			LastActor->UnHighlightActor();
		}
		else if (LastActor != ThisActor)
		{
			// Case D
			LastActor->UnHighlightActor();
			ThisActor->HighlightActor();
		}
	}
}
