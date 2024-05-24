// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShooterCharacterCrouchingComponent.h"
#include "ShooterCharacterMovingComponent.h"
#include "ShooterCharacterRotatingComponent.h"
#include "ShooterCharacterWeaponHoldingComponent.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class UNREALSHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UShooterCharacterMovingComponent *MovingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UShooterCharacterRotatingComponent *RotatingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UShooterCharacterCrouchingComponent *CrouchingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UShooterCharacterWeaponHoldingComponent *WeaponHoldingComponent = nullptr;

protected:
	virtual void BeginPlay() override;
	
public:
	AShooterCharacter();
	void Move(const FVector2D Input) const { MovingComponent->Move(Input); }
	void Rotate(const FVector2D Input) const { RotatingComponent->Rotate(Input); }

	void StartCrouch() const { CrouchingComponent->StartCrouching(); }
	void StopCrouch() const { CrouchingComponent->StopCrouching(); }

	void StartAim() const { WeaponHoldingComponent->StartAim(); }
	void StopAim() const { WeaponHoldingComponent->StopAim(); }
};
