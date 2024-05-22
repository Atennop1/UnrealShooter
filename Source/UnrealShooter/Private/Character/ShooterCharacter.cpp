// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/ShooterCharacter.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (MovementComponent == nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 999, FColor::Red, "Movement component is not set up!");
}
