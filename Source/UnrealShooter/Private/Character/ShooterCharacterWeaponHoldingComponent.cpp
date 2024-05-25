// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/ShooterCharacterWeaponHoldingComponent.h"
#include "Character/ShooterCharacter.h"

UShooterCharacterWeaponHoldingComponent::UShooterCharacterWeaponHoldingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShooterCharacterWeaponHoldingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr)
}

void UShooterCharacterWeaponHoldingComponent::Hold(const TScriptInterface<IWeapon> Weapon)
{
	IsHoldingWeapon = true;
	
	if (Weapon != nullptr)
		HoldingWeapon = Weapon;
}

void UShooterCharacterWeaponHoldingComponent::Unhold()
{
	Character->GetAimingComponent()->StopAim();
	IsHoldingWeapon = false;
	HoldingWeapon = nullptr;
}
