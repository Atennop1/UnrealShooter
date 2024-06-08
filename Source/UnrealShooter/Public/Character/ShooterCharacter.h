// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Movement/CharacterCrouchingComponent.h"
#include "Movement/CharacterMovingComponent.h"
#include "Movement/CharacterRotatingComponent.h"
#include "Weapon/CharacterWeaponHoldingComponent.h"
#include "Weapon/CharacterWeaponThrowingComponent.h"
#include "Weapon/CharacterAimingComponent.h"
#include "GameFramework/Character.h"
#include "Health/CharacterHealthComponent.h"
#include "Movement/CharacterJumpingComponent.h"
#include "Weapon/CharacterReloadingComponent.h"
#include "Weapon/CharacterShootingComponent.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class UNREALSHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterMovingComponent *MovingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterRotatingComponent *RotatingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterJumpingComponent *JumpingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterCrouchingComponent *CrouchingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterAimingComponent *AimingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterShootingComponent *ShootingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterReloadingComponent *ReloadingComponent = nullptr;
	
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterWeaponHoldingComponent *WeaponHoldingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterWeaponThrowingComponent *WeaponThrowingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterHealthComponent *HealthComponent = nullptr;

protected:
	virtual void BeginPlay() override;
	
public:
	AShooterCharacter();
	bool IsDead() const { return HealthComponent->IsDead(); } 

	UCharacterMovingComponent *GetMovingComponent() const { return MovingComponent; }
	UCharacterRotatingComponent *GetRotatingComponent() const { return RotatingComponent; }
	UCharacterCrouchingComponent *GetCrouchingComponent() const { return CrouchingComponent; }
	UCharacterJumpingComponent *GetJumpingComponent() const { return JumpingComponent; }
	
	UCharacterAimingComponent *GetAimingComponent() const { return AimingComponent; }
	UCharacterShootingComponent *GetShootingComponent() const { return ShootingComponent; }
	UCharacterReloadingComponent *GetReloadingComponent() const { return ReloadingComponent; }
	UCharacterWeaponHoldingComponent *GetWeaponHoldingComponent() const { return WeaponHoldingComponent; }
	UCharacterWeaponThrowingComponent *GetWeaponThrowingComponent() const { return WeaponThrowingComponent; }
};
