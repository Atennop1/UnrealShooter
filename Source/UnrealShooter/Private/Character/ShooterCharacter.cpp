// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/ShooterCharacter.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (MovingComponent == nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 999, FColor::Red, "MovingComponent is not set up!");

	if (RotatingComponent == nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 999, FColor::Red, "CrouchingComponent is not set up!");

	if (CrouchingComponent == nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 999, FColor::Red, "MovingComponent is not set up!");
}
