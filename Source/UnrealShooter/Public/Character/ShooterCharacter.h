// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/CharacterWeaponHoldingComponent.h"
#include "Weapon/CharacterWeaponThrowingComponent.h"
#include "Weapon/CharacterAimingComponent.h"
#include "GameFramework/Character.h"
#include "Health/CharacterHealthComponent.h"
#include "Movement/ICharacterCrouchingComponent.h"
#include "Movement/ICharacterJumpingComponent.h"
#include "Movement/ICharacterMovingComponent.h"
#include "Movement/ICharacterRotatingComponent.h"
#include "Weapon/CharacterReloadingComponent.h"
#include "Weapon/CharacterShootingComponent.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class UNREALSHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TScriptInterface<IHealth> Health = nullptr;
	
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TScriptInterface<ICharacterMovingComponent> MovingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TScriptInterface<ICharacterRotatingComponent> RotatingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TScriptInterface<ICharacterCrouchingComponent> CrouchingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TScriptInterface<ICharacterJumpingComponent> JumpingComponent = nullptr;
	
	
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

protected:
	virtual void BeginPlay() override;
	
public:
	AShooterCharacter();
	bool IsDead() const { return Health->IsDead(); } 

	ICharacterMovingComponent *GetMovingComponent() const { return MovingComponent.GetInterface(); }
	ICharacterRotatingComponent *GetRotatingComponent() const { return RotatingComponent.GetInterface(); }
	ICharacterCrouchingComponent *GetCrouchingComponent() const { return CrouchingComponent.GetInterface(); }
	ICharacterJumpingComponent *GetJumpingComponent() const { return JumpingComponent.GetInterface(); }
	IHealth *GetHealthComponent() const { return Health.GetInterface(); }
	
	UCharacterAimingComponent *GetAimingComponent() const { return AimingComponent; }
	UCharacterShootingComponent *GetShootingComponent() const { return ShootingComponent; }
	UCharacterReloadingComponent *GetReloadingComponent() const { return ReloadingComponent; }
	UCharacterWeaponHoldingComponent *GetWeaponHoldingComponent() const { return WeaponHoldingComponent; }
	UCharacterWeaponThrowingComponent *GetWeaponThrowingComponent() const { return WeaponThrowingComponent; }
};
