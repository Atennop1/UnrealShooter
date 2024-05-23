// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/ShooterCharacterRotatingComponent.h"

#include "Character/ShooterCharacter.h"

UShooterCharacterRotatingComponent::UShooterCharacterRotatingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UShooterCharacterRotatingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	
	check(Character != nullptr)
	check(CharacterCamera != nullptr)
}

void UShooterCharacterRotatingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	LocationCameraPointingAt = CharacterCamera->GetComponentLocation() + CharacterCamera->GetForwardVector() * 500;
}

void UShooterCharacterRotatingComponent::Rotate(const FVector2D Input) const
{
	Character->AddControllerYawInput(Input.X);
	Character->AddControllerPitchInput(Input.Y);
}
