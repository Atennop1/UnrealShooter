// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/ShooterCharacterMovingComponent.h"
#include "Character/ShooterCharacter.h"

UShooterCharacterMovingComponent::UShooterCharacterMovingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShooterCharacterMovingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check (Character != nullptr)
}

void UShooterCharacterMovingComponent::Move(const FVector2D Value) const
{
	 //Character->SetActorRotation(FRotator(0, Character->GetControlRotation().Yaw, 0));
	 Character->AddMovementInput(Character->GetActorRightVector(), Value.X);
	 Character->AddMovementInput(Character->GetActorForwardVector(), Value.Y);
}
