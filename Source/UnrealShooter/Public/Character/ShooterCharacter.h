// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShooterCharacterCrouchingComponent.h"
#include "ShooterCharacterMovingComponent.h"
#include "ShooterCharacterRotatingComponent.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class UNREALSHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UShooterCharacterMovingComponent *MovingComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UShooterCharacterRotatingComponent *RotatingComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UShooterCharacterCrouchingComponent *CrouchingComponent = nullptr;

protected:
	virtual void BeginPlay() override;
	
public:
	AShooterCharacter();
	void Move(const FVector2D Input) const { MovingComponent->Move(Input); }
	void Rotate(const FVector2D Input) const { RotatingComponent->Rotate(Input); }

	void StartCrouch() const { CrouchingComponent->StartCrouching(); }
	void StopCrouch() const { CrouchingComponent->StopCrouching(); }
};
