// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShooterCharacter.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

UCLASS()
class UNREALSHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY()
	AShooterCharacter *PossessedCharacter;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext *InputMappingContext;
	
	UPROPERTY(EditDefaultsOnly)
	UInputAction *MoveAction;
	
	UPROPERTY(EditDefaultsOnly)
	UInputAction *LookAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction *JumpAction;

	// ReSharper disable once CppMemberFunctionMayBeConst
	void CallMove(const FInputActionValue &Value) { PossessedCharacter->Move(Value.Get<FVector2D>()); }
	
	// ReSharper disable once CppMemberFunctionMayBeConst
	void CallLook(const FInputActionValue &Value) { PossessedCharacter->Look(Value.Get<FVector2D>()); }

	// ReSharper disable once CppMemberFunctionMayBeConst
	void CallStartJumping(const FInputActionValue &Value) { PossessedCharacter->Jump(); }

	// ReSharper disable once CppMemberFunctionMayBeConst
	void CallStopJumping(const FInputActionValue &Value) { PossessedCharacter->StopJumping(); }
	
protected:
	virtual void OnPossess(APawn *PossessingPawn) override;
};
