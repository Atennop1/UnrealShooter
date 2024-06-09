// Copyright Atennop and Krypton. All Rights Reserved.

#include "Player/PlayerCharacterJumpingComponent.h"
#include "Character/ShooterCharacter.h"

UPlayerCharacterJumpingComponent::UPlayerCharacterJumpingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerCharacterJumpingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr);
}

void UPlayerCharacterJumpingComponent::StartJumping()
{
	if (!Character->IsDead())
		Character->Jump();
}

void UPlayerCharacterJumpingComponent::StopJumping()
{
	if (!Character->IsDead())
		Character->StopJumping();
}

