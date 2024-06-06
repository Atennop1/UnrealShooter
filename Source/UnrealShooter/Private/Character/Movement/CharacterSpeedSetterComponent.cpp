// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Movement/CharacterSpeedSetterComponent.h"
#include "Character/ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UCharacterSpeedSetterComponent::UCharacterSpeedSetterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterSpeedSetterComponent::BeginPlay()
{
	
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr);
}

void UCharacterSpeedSetterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Character->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	if (Character->GetCrouchingComponent()->GetIsCrouching() && Character->GetCharacterMovement()->MaxWalkSpeed > CrouchSpeed)
		Character->GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;

	if (Character->GetAimingComponent()->GetIsAiming() && Character->GetCharacterMovement()->MaxWalkSpeed > AimSpeed)
		Character->GetCharacterMovement()->MaxWalkSpeed = AimSpeed;
}

