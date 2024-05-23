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
	
	UPROPERTY(EditDefaultsOnly)
	UInputAction *CrouchAction;

	void CallMove(const FInputActionValue &Value);
	void CallRotate(const FInputActionValue &Value);

	void CallJump(const FInputActionValue &Value);
	void CallStopJumping(const FInputActionValue &Value);

	void CallStartCrouch(const FInputActionValue &Value);
	void CallStopCrouch(const FInputActionValue &Value);

protected:
	virtual void OnPossess(APawn *PossessingPawn) override;
};
