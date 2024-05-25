// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/CharacterWeaponHoldingComponent.h"
#include "Character/ShooterCharacter.h"

UCharacterWeaponHoldingComponent::UCharacterWeaponHoldingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterWeaponHoldingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr)
}

void UCharacterWeaponHoldingComponent::Hold(const TScriptInterface<IWeapon> Weapon)
{
	IsHoldingWeapon = true;
	
	if (Weapon != nullptr)
		HoldingWeapon = Weapon;
}

void UCharacterWeaponHoldingComponent::Unhold()
{
	Character->GetAimingComponent()->StopAim();
	IsHoldingWeapon = false;
	HoldingWeapon = nullptr;
}
