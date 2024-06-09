// Copyright Atennop and Krypton. All Rights Reserved.

#include "Player/PlayerCharacterMovingComponent.h"
#include "Character/ShooterCharacter.h"

UPlayerCharacterMovingComponent::UPlayerCharacterMovingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerCharacterMovingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check (Character != nullptr)
}

void UPlayerCharacterMovingComponent::Move(const FVector2D Value)
{
	if (Character->IsDead())
		return;
	
	 Character->AddMovementInput(Character->GetActorRightVector(), Value.X);
	 Character->AddMovementInput(Character->GetActorForwardVector(), Value.Y);
}
