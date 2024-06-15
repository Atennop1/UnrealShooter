// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Movement/CharacterMovingComponent.h"
#include "Character/ShooterCharacter.h"

UCharacterMovingComponent::UCharacterMovingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterMovingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check (Character != nullptr)
}

void UCharacterMovingComponent::Move(const FVector2D Value)
{
	if (Character->IsDead())
		return;
	
	 Character->AddMovementInput(Character->GetActorRightVector(), Value.X);
	 Character->AddMovementInput(Character->GetActorForwardVector(), Value.Y);
}
