// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/ShooterPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void AShooterPlayerController::OnPossess(APawn *PossessingPawn)
{
	Super::OnPossess(PossessingPawn);
	PossessedCharacter = Cast<AShooterCharacter>(PossessingPawn);

	if (!PossessedCharacter)
		return;

	if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
	
	const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::CallMove);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::CallLook);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::CallStartJumping);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AShooterPlayerController::CallStopJumping);
}
