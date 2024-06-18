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
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::CallStartJumping);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AShooterPlayerController::CallStopJumping);
	EnhancedInputComponent->BindAction(StartCrouchAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::CallStartCrouch);
	EnhancedInputComponent->BindAction(StopCrouchAction, ETriggerEvent::Completed, this, &AShooterPlayerController::CallStopCrouch);
	EnhancedInputComponent->BindAction(StartAimAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::CallStartAim);
	EnhancedInputComponent->BindAction(StopAimAction, ETriggerEvent::Completed, this, &AShooterPlayerController::CallStopAim);
	EnhancedInputComponent->BindAction(StartShootAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::CallStartShoot);
	EnhancedInputComponent->BindAction(StopShootAction, ETriggerEvent::Completed, this, &AShooterPlayerController::CallStopShoot);
	EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::CallReload);
	EnhancedInputComponent->BindAction(ThrowWeaponAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::CallThrowWeapon);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallMove(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetMovingComponent()->Move(Value.Get<FVector2D>()); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallRotate(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetRotatingComponent()->Rotate(Value.Get<FVector2D>()); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallStartJumping(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetJumpingComponent()->StartJumping(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallStopJumping(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetJumpingComponent()->StopJumping(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallStartCrouch(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetCrouchingComponent()->StartCrouching(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallStopCrouch(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetCrouchingComponent()->StopCrouching(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallStartAim(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetAimingComponent()->StartAim(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallStopAim(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetAimingComponent()->StopAim(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallStartShoot(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetShootingComponent()->StartShooting(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallStopShoot(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetShootingComponent()->StopShooting(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallReload(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetReloadingComponent()->Reload(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterPlayerController::CallThrowWeapon(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetWeaponThrowingComponent()->Throw(); }
