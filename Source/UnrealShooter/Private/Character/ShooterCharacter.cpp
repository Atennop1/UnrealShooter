// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/ShooterCharacter.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(MovingComponent != nullptr)
	check(RotatingComponent != nullptr)
	check(CrouchingComponent != nullptr)
}
