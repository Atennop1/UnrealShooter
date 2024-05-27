// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Weapon/CharacterAimingComponent.h"
#include "Character/ShooterCharacter.h"
#include "Character/Weapon/CharacterWeaponHoldingComponent.h"

UCharacterAimingComponent::UCharacterAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr)
}

void UCharacterAimingComponent::StartAim()
{
	if (Character->GetWeaponHoldingComponent()->GetHoldingWeapon() != nullptr && Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()->ImplementsInterface(UFirearm::StaticClass()))
		IsAiming = true;
}

void UCharacterAimingComponent::StopAim()
{
	if (Character->GetWeaponHoldingComponent()->GetHoldingWeapon() != nullptr && Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()->ImplementsInterface(UFirearm::StaticClass()))
		IsAiming = false;
}