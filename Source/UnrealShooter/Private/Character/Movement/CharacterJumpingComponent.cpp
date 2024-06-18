// Copyright Atennop. All Rights Reserved.

#include "Character/Movement/CharacterJumpingComponent.h"
#include "Character/ShooterCharacter.h"

UCharacterJumpingComponent::UCharacterJumpingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterJumpingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr);
}

void UCharacterJumpingComponent::StartJumping() const
{
	if (!Character->IsDead())
		Character->Jump();
}

void UCharacterJumpingComponent::StopJumping() const
{
	if (!Character->IsDead())
		Character->StopJumping();
}

