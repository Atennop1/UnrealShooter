// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/ShooterCharacter.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent != nullptr)
	check(MovingComponent != nullptr)
	check(RotatingComponent != nullptr)
	check(CrouchingComponent != nullptr)
	check(JumpingComponent != nullptr)
	
	check(AimingComponent != nullptr)
	check(ShootingComponent != nullptr)
	check(ReloadingComponent != nullptr)
	check(WeaponHoldingComponent != nullptr)
	check(WeaponThrowingComponent != nullptr)
}
