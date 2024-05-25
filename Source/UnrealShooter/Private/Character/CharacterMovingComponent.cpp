// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/CharacterMovingComponent.h"
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

void UCharacterMovingComponent::Move(const FVector2D Value) const
{
	 //Character->SetActorRotation(FRotator(0, Character->GetControlRotation().Yaw, 0));
	 Character->AddMovementInput(Character->GetActorRightVector(), Value.X);
	 Character->AddMovementInput(Character->GetActorForwardVector(), Value.Y);
}
