// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/ShooterCharacterMovementComponent.h"
#include "Character/ShooterCharacter.h"

UShooterCharacterMovementComponent::UShooterCharacterMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShooterCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	
	if (!Character)
		GEngine->AddOnScreenDebugMessage(-1, 999, FColor::Red, "ShooterCharacterMovementComponent must be on ShooterCharacter!");
}

void UShooterCharacterMovementComponent::Move(const FVector2D Value) const
{
	Character->AddMovementInput(Character->GetActorForwardVector(), Value.Y);
	Character->AddMovementInput(Character->GetActorRightVector(), Value.X);
}

void UShooterCharacterMovementComponent::Look(const FVector2D Input) const
{
	Character->AddControllerYawInput(Input.X);
	Character->AddControllerPitchInput(Input.Y);
}
