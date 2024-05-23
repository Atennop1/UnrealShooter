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
	
	if (!Character)
		GEngine->AddOnScreenDebugMessage(-1, 999, FColor::Red, "ShooterCharacterMovingComponent must be on ShooterCharacter!");
}

void UShooterCharacterMovingComponent::Move(const FVector2D Value) const
{
	Character->AddMovementInput(Character->GetActorForwardVector(), Value.Y);
	Character->AddMovementInput(Character->GetActorRightVector(), Value.X);
}
