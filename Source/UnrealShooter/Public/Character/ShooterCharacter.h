// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShooterCharacterAimingComponent.h"
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

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UShooterCharacterAimingComponent *AimingComponent = nullptr;

protected:
	virtual void BeginPlay() override;
	
public:
	AShooterCharacter();

	UShooterCharacterMovingComponent *GetMovingComponent() const { return MovingComponent; }
	UShooterCharacterRotatingComponent *GetRotatingComponent() const { return RotatingComponent; }
	UShooterCharacterCrouchingComponent *GetCrouchingComponent() const { return CrouchingComponent; }
	UShooterCharacterWeaponHoldingComponent *GetWeaponHoldingComponent() const { return WeaponHoldingComponent; }
	UShooterCharacterAimingComponent *GetAimingComponent() const { return AimingComponent; }
};
