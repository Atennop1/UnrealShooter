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
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::CallRotate);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::CallJump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AShooterPlayerController::CallStopJumping);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::CallStartCrouch);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AShooterPlayerController::CallStopCrouch);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallMove(const FInputActionValue& Value) { PossessedCharacter->Move(Value.Get<FVector2D>()); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallRotate(const FInputActionValue& Value) { PossessedCharacter->Rotate(Value.Get<FVector2D>()); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallJump(const FInputActionValue& Value) { PossessedCharacter->Jump(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallStopJumping(const FInputActionValue& Value) { PossessedCharacter->StopJumping(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallStartCrouch(const FInputActionValue& Value) { PossessedCharacter->StartCrouch(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallStopCrouch(const FInputActionValue& Value) { PossessedCharacter->StopCrouch(); }
